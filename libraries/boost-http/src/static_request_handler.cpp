// Created based off of https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/http/server/request_handler.cpp
//
// static_request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include "../include/static_request_handler.hpp"
#include <fstream>
#include <sstream>
#include "../include/mime_types.hpp"
#include "../include/request.hpp"
#include "../include/response.hpp"
#include "logger.h"
#include "response_generator.h"

#include <iostream>

namespace http {
namespace server {

static_request_handler::static_request_handler(const std::string& doc_root)
  : doc_root_(doc_root)
{
}

// std::shared_ptr<request_handler> static_request_handler::Init(const std::string& location_path, const NginxConfig& config) {
request_handler* static_request_handler::Init(const std::string& location_path, const NginxConfig& config) {
  // std::shared_ptr<static_request_handler> static_req_handler(new static_request_handler(location_path));
  static_request_handler* static_req_handler = new static_request_handler(location_path);
  return static_req_handler;
}



void static_request_handler::set_doc_root(const std::string& doc_root) {
  doc_root_ = doc_root;
}

response static_request_handler::handle_request(const request& req) {
  //TODO update to new response format
  //TODO fix logging to not use ip var
  src::severity_logger_mt<logging::trivial::severity_level> slg;
  // slg.add_attribute("IPAddress", attrs::constant< std::string >(ip));
  response rep;

  std::string filename = "";
  for (int i = req.uri_.size() - 1; i >= 0; i--) {
      filename = req.uri_[i] + filename;
      if (req.uri_[i] == '/') break;
  }
  std::cerr << "Filename: " << filename << std::endl;

  // Decode url to path.
  std::string request_path;
  if (!url_decode(filename, request_path))
  {
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Identified as malformed static file request. Sending 400 response. Response Metrics: 400, " << req.uri_ << ", StaticHandler";
    rep = response_generator::stock_response(response::bad_request);
    return rep;
  }

  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/'
      || request_path.find("..") != std::string::npos)
  {
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Identified as malformed static file request. Sending 400 response. Response Metrics: 400, " << req.uri_ << ", StaticHandler";
    rep = response_generator::stock_response(response::bad_request);
    return rep;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/')
  {
    request_path += "index.html";
  }

  // Determine the file extension.
  std::size_t last_slash_pos = request_path.find_last_of("/");
  std::size_t last_dot_pos = request_path.find_last_of(".");
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
  {
    extension = request_path.substr(last_dot_pos + 1);
  }

  // Open the file to send back.
  std::string full_path = doc_root_ + request_path;
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Unable to find " << full_path.c_str() << ". Sending 404 response. Response Metrics: 404, " << req.uri_ << ", StaticHandler";
    rep = response_generator::stock_response(response::not_found);
    return rep;
  }

  // Fill out the response to be sent to the client.
  rep.code_ = response::ok;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    rep.body_.append(buf, is.gcount());

  rep.headers_["Content-Length"] = std::to_string(rep.body_.size());
  rep.headers_["Content-Type"] = mime_types::extension_to_type(extension);

  BOOST_LOG_SEV(slg, logging::trivial::info) << "Requested file found. Sending 200 response. Response Metrics:: 200, " << req.uri_ << ", StaticHandler";
  return rep;
}

bool static_request_handler::url_decode(const std::string& in, std::string& out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

} // namespace server
} // namespace http
