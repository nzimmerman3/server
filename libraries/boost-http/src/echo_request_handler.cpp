// Created based off of https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/http/server/request_handler.cpp
//
// echo_request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~


#include <string>
#include "../include/echo_request_handler.hpp"
#include "../include/request.hpp"
#include "../include/response.hpp"
#include "logger.h"
#include "response_generator.h"

namespace http {
namespace server {

//std::shared_ptr<request_handler> echo_request_handler::Init(const std::string& location_path, const NginxConfig& config) {
request_handler* echo_request_handler::Init(const std::string& location_path, const NginxConfig& config) {
    //std::shared_ptr<echo_request_handler> echo_req_handler(new echo_request_handler());
    echo_request_handler* echo_req_handler = new echo_request_handler();
    return echo_req_handler;
}

response echo_request_handler::handle_request(const request& req) {
    //TODO fix logging to not use ip var
    http::server::response rep;
    src::severity_logger_mt<logging::trivial::severity_level> slg;
    // slg.add_attribute("IPAddress", attrs::constant< std::string >(ip));

    rep.code_ = http::server::response::ok;
    std::string method;
    BOOST_LOG_SEV(slg, logging::trivial::info) << req.method_;

    switch(req.method_) {
        case request::GET:
            method = "GET";
            break;
        case request::HEAD:
            method = "HEAD";
            break;
        case request::POST:
            method = "POST";
            break;
        case request::PUT:
            method = "PUT";
            break;
        case request::PATCH:
            method = "PATCH";
            break;
        case request::DELETE:
            method = "DELETE";
            break;
        case request::OPTIONS:
            method = "OPTIONS";
            break;
        case request::TRACE:
            method = "TRACE";
            break;
    }
    std::string requestLine = std::string(method + " " 
                                        + req.uri_ 
                                        + " "
                                        + req.version_
                                        + "\r\n");
    rep.body_.append(requestLine);

    for (auto const& pair : req.headers_)
    {
        //Not sure if this is needed
        // rep.headers_[pair.first] = pair.second;
        rep.body_.append(pair.first + ": " + pair.second + "\r\n");
    }
    rep.body_.append(req.body_);
    rep.body_.append("\r\n");

    rep.headers_["Content-Length"] = std::to_string(rep.body_.size());
    rep.headers_["Content-Type"] = "text/plain";


    BOOST_LOG_SEV(slg, logging::trivial::info) << "Echo response formed. Sending 200 response. Response Metrics: 200, " << req.uri_ << ", EchoHandler";
    return rep;
}

} // namespace server
} // namespace http
