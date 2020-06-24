#ifndef HTTP_HEALTH_REQUEST_HANDLER_HPP
#define HTTP_HEALTH_REQUEST_HANDLER_HPP

#include <string>
#include "request_handler.hpp"

#include "../../../include/config_parser.h"
#include "request.hpp"
#include "response.hpp"

namespace http {
namespace server {

class health_request_handler : public http::server::request_handler {
    public:
        static health_request_handler* Init(const std::string& location_path, const NginxConfig& config);
        http::server::response handle_request(const http::server::request& request);

    private:
        health_request_handler();
};

} // namespace server
} // namespace http

#endif // HTTP_HEALTH_REQUEST_HANDLER_HPP