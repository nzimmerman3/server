// Created based off of https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/http/server/request_handler.cpp
//
// static_request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef HTTP_STATIC_REQUEST_HANDLER_HPP
#define HTTP_STATIC_REQUEST_HANDLER_HPP

#include <string>
#include "request_handler.hpp"

namespace http {
namespace server {

struct response;
struct request;

/// The common handler for all incoming requests.
class static_request_handler : public http::server::request_handler
{
public:
  /// Construct with a directory containing files to be served.
  explicit static_request_handler(const std::string& doc_root);

  // static std::shared_ptr<request_handler> Init(const std::string& location_path, const NginxConfig& config);
  static request_handler* Init(const std::string& location_path, const NginxConfig& config);

  /// Handle a request and produce a response.
  response handle_request(const request& req);

  // Set doc root to handle various locations
  void set_doc_root(const std::string& doc_root);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace server
} // namespace http

#endif // HTTP_STATIC_REQUEST_HANDLER_HPP