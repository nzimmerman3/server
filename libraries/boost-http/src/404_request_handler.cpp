#include "../include/404_request_handler.hpp"
#include "../include/response.hpp"

#include "../../../include/response_generator.h"
#include "logger.h"

namespace http {
namespace server {

not_found_request_handler::not_found_request_handler()
{

}

not_found_request_handler* not_found_request_handler::Init(const std::string& location_path, const NginxConfig& config)
{
    not_found_request_handler *handler = new not_found_request_handler();
    return handler;
}

http::server::response not_found_request_handler::handle_request(const http::server::request& request)
{
    src::severity_logger_mt<logging::trivial::severity_level> slg;
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Could not find path requested. Sending 404 response. Reponse Metrics: 404, " << request.uri_ << ", 404Handler";
    return http::server::response_generator::stock_response(http::server::response::not_found);
}

} // namespace server
} // namespace http
