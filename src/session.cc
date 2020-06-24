#include <iostream>
#include <string>
#include <thread>

#include "session.h"
#include "logger.h"
#include "response_generator.h"
#include "../include/server_status_singleton.h"

namespace server = http::server;

 session::session(boost::asio::io_service& io_service, std::shared_ptr<request_router> req_router) : socket_(io_service), request_router_(req_router) {

 }

tcp::socket& session::socket() {
	return socket_;
}

void session::start() {
	std::thread(&session::handleRequest, this).detach();
}

void session::handleRequest() {
	src::severity_logger_mt<logging::trivial::severity_level> slg;
	slg.add_attribute("IPAddress", attrs::constant< std::string >(socket_.remote_endpoint().address().to_string()));

	while (true) {
		server::request_parser::result_type parseResult = server::request_parser::indeterminate;
		server::request request;
		server::response response;
		size_t bytes_transferred;

		while (parseResult == server::request_parser::indeterminate) { // While buffer has incomplete data (incomplete HTTP request), need to read more data from socket and repeat
			// TODO: Set timeout in case read takes too long and send 408 instead
			try {
				// Block and read whatever is send by the client so far, handle exceptions if they arise
				BOOST_LOG_SEV(slg, logging::trivial::debug) << "Beginning to read from client";
				bytes_transferred = socket_.read_some(boost::asio::buffer(data_, max_length));
			}
			catch(const std::exception& e) {
				if (std::string("read_some: End of file").compare(e.what()) != 0) {
					BOOST_LOG_SEV(slg, logging::trivial::error) << "Expected error reading from client socket: " << e.what();
				}
				BOOST_LOG_SEV(slg, logging::trivial::info) << "Closing connection.";
				delete this;
				return;
			}
			// Give received data to HTTP parser for parsing
			BOOST_LOG_SEV(slg, logging::trivial::debug) << "Parsing received client request";
			parseResult = std::get<0>(reqParser.parse(request, std::begin(data_), std::begin(data_) + bytes_transferred));
		}

		// Received full request, handle accordingly based on parsing result
		BOOST_LOG_SEV(slg, logging::trivial::debug) << "Fully received and parsed client request";
		if (parseResult == server::request_parser::good) { // Parsed request successfully, create response accordingly
			BOOST_LOG_SEV(slg, logging::trivial::debug) << "Sending client request to be routed";
			request_router_->route(request, response, socket().remote_endpoint().address().to_string());
		}
		else if (parseResult == server::request_parser::bad) { // Attempted parsing request but failed b/c of client-side error, send 400
			BOOST_LOG_SEV(slg, logging::trivial::error) << "Malformed request received. Sending 400 response. Response Metrics: 400";
			response = http::server::response_generator::stock_response(server::response::bad_request);
		}

		reqParser.reset();
		// Log request/response pair statistics for use by status handler
		BOOST_LOG_SEV(slg, logging::trivial::debug) << "Storing statistics of request/response pair";
		server_status_singleton::getInstance()->logReqResp(request, response);

		try {
			// Write generated response to client, handle exceptions if they arise
			BOOST_LOG_SEV(slg, logging::trivial::debug) << "Sending response to client";
			socket_.write_some(http::server::response_generator::to_buffers(response));
		}
		catch(const std::exception& e) {
			if (std::string("write_some: Broken pipe").compare(e.what()) != 0) {
				BOOST_LOG_SEV(slg, logging::trivial::error) << "Error writing to client socket: " << e.what();
			}
			BOOST_LOG_SEV(slg, logging::trivial::info) << "Closing connection.";
			delete this;
			return;
		}
	}
}
