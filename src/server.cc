#include <string>
#include "../include/server.h"
#include "logger.h"

server::server(boost::asio::io_service &io_service, short port, NginxConfig& config) : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), req_router(std::make_shared<request_router>(config)) {
    startAccept();
}

void server::startAccept() {
	session* new_session = new session(io_service_, req_router);
	acceptor_.async_accept(new_session->socket(), boost::bind(&server::handleAccept, this, new_session, boost::asio::placeholders::error));
}

void server::handleAccept(session* new_session, const boost::system::error_code& error) {
	src::severity_logger_mt<logging::trivial::severity_level> slg; //= myLogger::get()
	slg.add_attribute("IPAddress", attrs::constant< std::string >(new_session->socket().remote_endpoint().address().to_string()));

	BOOST_LOG_SEV(slg, logging::trivial::info) << "Opening new connection.";

	if (!error) {
		new_session->start();
    		BOOST_LOG_SEV(slg, logging::trivial::info) << "Starting up a new session.";
	}
    else {
      BOOST_LOG_SEV(slg, logging::trivial::error) << "Session error. Starting new session.";
      delete new_session;
    }

    startAccept();
}
