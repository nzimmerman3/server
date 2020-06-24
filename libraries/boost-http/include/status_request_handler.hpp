#ifndef STATUS_REQUEST_HANDLER_H
#define STATUS_REQUEST_HANDLER_H

#include <string>
#include "../../../include/config_parser.h"
#include "request_handler.hpp"
#include "request.hpp"
#include "response.hpp"

namespace http {
namespace server {

class status_request_handler : public http::server::request_handler {
    public:
        static status_request_handler* Init(const std::string& location_path, const NginxConfig& config);
        http::server::response handle_request(const http::server::request& request);

    private:
        status_request_handler();
};

} // namespace server
} // namespace http

#endif // STATUS_REQUEST_HANDLER_H