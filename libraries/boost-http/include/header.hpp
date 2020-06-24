//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// See for details: https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/http/server/header.hpp

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <string>

namespace http {
namespace server {

struct header
{
  std::string name;
  std::string value;
};

} // namespace server
} // namespace http

#endif // HTTP_HEADER_HPP