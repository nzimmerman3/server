#include "../include/health_request_handler.hpp"
#include "../include/response.hpp"

#include "../../../include/response_generator.h"
#include "logger.h"

namespace http {
namespace server {

health_request_handler::health_request_handler() {

}

health_request_handler* health_request_handler::Init(const std::string& location_path, const NginxConfig& config) {
    health_request_handler *handler = new health_request_handler();
    return handler;
}

http::server::response health_request_handler::handle_request(const http::server::request& request) {
    src::severity_logger_mt<logging::trivial::severity_level> slg;
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Sending 200 response. Reponse Metrics: 200, " << request.uri_ << ", HealthHandler";
    return http::server::response_generator::stock_response(http::server::response::ok);
}

} // namespace server
} // namespace http
