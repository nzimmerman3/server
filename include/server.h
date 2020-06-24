#ifndef HR_SERVER_H
#define HR_SERVER_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "session.h"
#include "request_router.h"
#include "config_parser.h"

using boost::asio::ip::tcp;

class server {
    public:
        server(boost::asio::io_service &io_service, short port, NginxConfig& config);
    
    private:
        void startAccept();
        void handleAccept(session *new_sesion, const boost::system::error_code &error);
        
        boost::asio::io_service& io_service_;
        tcp::acceptor acceptor_;
        std::shared_ptr<request_router> req_router;
};

#endif // HR_SERVER_H