//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// See for details: https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/http/server/request.hpp

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include <map>
// #include "../include/header.hpp"

namespace http {
namespace server {

/// A request received from a client.
struct request
{
  //std::string method;
  enum method_enum {
    GET = 1,
    HEAD = 2,
    POST = 3,
    PUT = 4,
    PATCH = 5,
    DELETE = 6,
    OPTIONS = 7,
    TRACE = 8
  }  method_;

  std::string uri_;

  std::string version_;

  //name -> value
  std::map<std::string, std::string> headers_;

  //content of request
  std::string body_;
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HPP