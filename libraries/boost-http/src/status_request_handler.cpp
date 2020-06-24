#include "../include/status_request_handler.hpp"
#include "../../../include/server_status_singleton.h"
#include "logger.h"

namespace http {
namespace server {

status_request_handler::status_request_handler()
{

}

status_request_handler* status_request_handler::Init(const std::string& location_path, const NginxConfig& config)
{
    status_request_handler *handler = new status_request_handler();
    return handler;
}

http::server::response status_request_handler::handle_request(const http::server::request& request)
{
    src::severity_logger_mt<logging::trivial::severity_level> slg;
    http::server::response resp;
    std::map<std::string, std::vector<std::string>>* handlerConfigs = server_status_singleton::getInstance()->getHandlerConfigs();
    std::map<http::server::response::status_type, int>* statusCounters = server_status_singleton::getInstance()->getRespStatusCounters();
    std::map<std::string, std::map<http::server::response::status_type, int>>* reqStatuses = server_status_singleton::getInstance()->getReqStatuses();

    resp.code_ = http::server::response::ok;
    resp.body_.append(std::string("<html>") + "<head><title>Status Page</title></head>" + "<body>");

    resp.body_.append("<h1>Handlers To URI Mappings</h1><p>");
    for (std::map<std::string, std::vector<std::string>>::iterator it = handlerConfigs->begin(); it != handlerConfigs->end(); it++)
    {
        resp.body_.append("Handler Type: " + it->first + " |");
        for (auto &&uri : it->second)
        {
            resp.body_.append(" " + uri);
        }
        resp.body_.append("<br>");
    }
    resp.body_.append("</p><h1>Requests Received & Status Codes Sent</h1><p>");

    for (std::map<std::string, std::map<http::server::response::status_type, int>>::iterator it = reqStatuses->begin(); it != reqStatuses->end(); it++)
    {
        resp.body_.append("URI: " + it->first + " |");
        for (std::map<http::server::response::status_type, int>::iterator it_status = it->second.begin(); it_status != it->second.end(); it_status++)
        {
            resp.body_.append(" Status Code: " + std::to_string(it_status->first) + " Count: " + std::to_string(it_status->second) + ",");
        }
        resp.body_.append("<br>");
    }
    resp.body_.append("</p>");

    resp.body_.append(std::string("</body>") + "</html>");

    resp.headers_["Content-Length"] = std::to_string(resp.body_.size());
    resp.headers_["Content-Type"] = "text/html";

    BOOST_LOG_SEV(slg, logging::trivial::error) << "Status request received. Sending 200 response. Reponse Metrics: 200, " << request.uri_ << ", StatusHandler";
    return resp;
}

} // namespace server
} // namespace http