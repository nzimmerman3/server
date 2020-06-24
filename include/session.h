#ifndef HR_SESSION_H
#define HR_SESSION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "../libraries/boost-http/include/request_parser.hpp"
#include "../libraries/boost-http/include/request.hpp"
#include "../libraries/boost-http/include/response.hpp"

#include "config_parser.h"
#include "request_router.h"

using boost::asio::ip::tcp;

class session {
    public:
        session(boost::asio::io_service&, std::shared_ptr<request_router> req_router);
        tcp::socket& socket();
        void start();

    private:
        void handleRequest();

        tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];
        std::string rootDir;

		http::server::request_parser reqParser;
        std::shared_ptr<request_router> request_router_;

};

#endif // HR_SESSION_H