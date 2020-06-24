#ifndef HR_REQUEST_ROUTER_H
#define HR_REQUEST_ROUTER_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <list>

#include "../libraries/boost-http/include/request.hpp"
#include "../libraries/boost-http/include/response.hpp"
#include "../libraries/boost-http/include/echo_request_handler.hpp"
#include "../libraries/boost-http/include/static_request_handler.hpp"

#include "../include/logger.h"
#include "config_parser.h"

using boost::asio::ip::tcp;

class request_router {
    public:
        request_router(NginxConfig& config_);
        bool route(http::server::request& request, http::server::response& response, std::string ip);
        void populateMap();    
    private:
        NginxConfig& config_;   
        src::severity_logger_mt<logging::trivial::severity_level> slg_;
        std::map<std::string, std::shared_ptr<http::server::request_handler>> handlerMap_;
};


#endif // HR_REQUEST_ROUTER_H