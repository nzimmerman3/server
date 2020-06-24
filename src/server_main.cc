//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "../include/server.h"
#include "../include/session.h"
#include "../include/config_parser.h"
#include "logger.h"

using boost::asio::ip::tcp;

void signalHandler(int signum) {
	src::severity_logger_mt<logging::trivial::severity_level>& slg = myLogger::get();
	BOOST_LOG_SEV(slg, logging::trivial::info) << "Interrupt signal (" <<  signum << ") received.";

	exit(signum);
}

int main(int argc, char* argv[]) {
  Logger logger;

  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);
  logger.startLogging();
  src::severity_logger_mt<logging::trivial::severity_level>& slg = myLogger::get();

  try {
    if (argc != 2) {
      // std::cerr << "Usage: async_tcp_echo_server <config file>\n";
      BOOST_LOG_SEV(slg, logging::trivial::info) << "Usage: ./server <config file>";
      return 1;
    }

    NginxConfig config;
    NginxConfigParser parser;
    //char* raw = argv[1];

    //std::cerr << "Starting Parsing\n";
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Starting Config File Parsing";

    if(!parser.Parse(argv[1], &config)) {
      //std::cerr << "Error: Parsing Config\n";
      BOOST_LOG_SEV(slg, logging::trivial::error) << "Error: Parsing Config";
      return 1;
    }

    //std::cerr << "Finished Parsing\n";
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Finished Config File Parsing";

    int port = -1;

    auto ports = config.getStatementsFor("port");
    if (ports.size() > 0 && ports[0]->tokens_.size() > 1) {
      port = std::stoi(ports[0]->tokens_[1]);
      BOOST_LOG_SEV(slg, logging::trivial::info) << "PORT: " << ports[0]->tokens_[1];
    } else {
      BOOST_LOG_SEV(slg, logging::trivial::error) << "Error: Missing port";
      return 1;
    }

    if (port <= 0 || port >= 65535) {
      BOOST_LOG_SEV(slg, logging::trivial::error) << "Error: Invalid port - " << std::to_string(port);
      return 1;
    }

    boost::asio::io_service io_service;

    server s(io_service, (short)port, config);

    BOOST_LOG_SEV(slg, logging::trivial::info) << "Server starting up";
    io_service.run();
  } catch (std::exception& e) {
    //std::cerr << "Exception: " << e.what() << "\n";
    BOOST_LOG_SEV(slg, logging::trivial::fatal) << "Exception: " << e.what();
  }

  return 0;
}
