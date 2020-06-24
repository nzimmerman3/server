#include <string>
#include <boost/asio.hpp>
#include <stdexcept>
#include "../include/proxy_request_handler.hpp"
#include "../include/request.hpp"
#include "../include/response.hpp"
#include "logger.h"
#include "response_generator.h"
using boost::asio::ip::tcp;

namespace http {
namespace server {

std::string remove_quotes(std::string str);

proxy_request_handler::proxy_request_handler(const std::string proxy_dest, const std::string prefix, const int port)
    : proxy_dest_(proxy_dest), prefix_(prefix), port_(port) {

}

proxy_request_handler* proxy_request_handler::Init(const std::string& location_path, const NginxConfig& config) {
    std::string proxy_dest = "http://www.ucla.edu";
    int port = 80;
    auto host = config.getStatementsFor("host");
    if (host.size() > 0 && host[0]->tokens_.size() > 1)
        proxy_dest = remove_quotes(host[0]->tokens_[1]);
    auto cport = config.getStatementsFor("port");
    if (cport.size() > 0 && cport[0]->tokens_.size() > 1)
        port = stoi(cport[0]->tokens_[1]);

    // Remove http, for passing into resolver in handleRequest
    size_t httpPos = proxy_dest.find("http://");
    if (httpPos == 0) {
        proxy_dest = proxy_dest.erase(0, 7);
    }
    // Remove ending slash
    if (proxy_dest[proxy_dest.size()-1] == '/') {
        proxy_dest.erase(proxy_dest.size() - 1, 1);
    }

    proxy_request_handler *handler = new proxy_request_handler(proxy_dest, "/ucla", port);
    return handler;
}

std::string remove_quotes(std::string str) {
    std::string ret;
    for (char c : str) {
        if (c != '"') {
            ret += c;
        }
    }
    return ret;
}

// This function essentially replaces references to static items by prepending the prefix.

void replace_refs(std::string& body, std::string prefix) {
    int idx = 0;

    // Replace all absolute references
    while (1) {
        idx = body.find("=\"/", idx);
        if (idx == std::string::npos) {
            break;
        }

        body.replace(idx, 3, "=\"" + prefix + "/");
        idx += prefix.size() + 3;
    }

    idx = 0;

    // ABsolute references using single quote
    while (1) {
        idx = body.find("='/", idx);
        if (idx == std::string::npos) break;

        body.replace(idx, 3, "='" + prefix + "/");
        idx += prefix.size() + 3;
    }

    idx = 0;

    // Url indicators
    while (1) {
        idx = body.find("url(/", idx);
        if (idx == std::string::npos) break;

        body.replace(idx, 5, "url(" + prefix + "/");
        idx += prefix.size() + 5;
    }
}

response proxy_request_handler::handle_request(const request& req) {
    src::severity_logger_mt<logging::trivial::severity_level> slg;
    try {
        std::string uri_to_request = req.uri_;
        size_t pos = uri_to_request.find(prefix_); 
        if (pos != std::string::npos) {
          uri_to_request.erase(pos, prefix_.length());
        }


        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(proxy_dest_, std::to_string(port_), boost::asio::ip::resolver_query_base::numeric_service);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        boost::asio::streambuf boost_request;
        std::ostream request_stream(&boost_request);
        request_stream << "GET " << uri_to_request << " HTTP/1.0\r\n";
        request_stream << "Host: " << proxy_dest_ << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";
        boost::asio::write(socket, boost_request);


        boost::asio::streambuf boost_response;
        boost::asio::read_until(socket, boost_response, "\r\n");
        std::istream response_stream(&boost_response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
          BOOST_LOG_SEV(slg, logging::trivial::error) << "Identified as malformed proxy request. Sending 400 response. Reponse Metrics: 400, " << req.uri_ << ", ProxyHandler";
          return response_generator::stock_response(response::bad_request);
        }


        http::server::response rep;
        rep.code_ = static_cast<http::server::response::status_type>(status_code);
        rep.body_ = "";
        boost::asio::read_until(socket, boost_response, "\r\n\r\n");
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            if(header.find(":") != std::string::npos) {
                std::string header_type = header.substr(0, header.find(":"));
                try {
                    std::string header_data = header.substr(header.find(":") + 2);
                    rep.headers_[header_type] = header_data;

                } catch (const std::out_of_range& err) {
                    rep.headers_[header_type] = "";
                }
            } else {
                rep.headers_[header] = "";
            }
        }
        if (boost_response.size() > 0) {
            std::string item((std::istreambuf_iterator<char>(&boost_response)), std::istreambuf_iterator<char>());
            rep.body_ += item + "\n";
        }

        boost::system::error_code error;
        while (boost::asio::read(socket, boost_response, boost::asio::transfer_at_least(1), error)) {
            std::string item((std::istreambuf_iterator<char>(&boost_response)), std::istreambuf_iterator<char>());
            rep.body_ += item + "\n";
        }
        if (error != boost::asio::error::eof)
             throw boost::system::system_error(error);
        
        replace_refs(rep.body_, prefix_);
        BOOST_LOG_SEV(slg, logging::trivial::error) << "Proxy request processed. Sending " << status_code << " response. Reponse Metrics: " << status_code << ", " << req.uri_ << ", ProxyHandler";
        return rep;

    } catch (std::exception &e) {
        BOOST_LOG_SEV(slg, logging::trivial::error) << "Identified as malformed proxy request. Sending 400 response. Reponse Metrics: 400, " << req.uri_ << ", ProxyHandler";
        return response_generator::stock_response(response::bad_request);
    }
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Identified as malformed proxy request. Sending 400 response. Reponse Metrics: 400, " << req.uri_ << ", ProxyHandler";
    return response_generator::stock_response(response::bad_request);
}

} // namespace server
} // namespace http