// Created based off of https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio/example/cpp11/http/server/request_handler.cpp
//
// echo_request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~


#ifndef HTTP_ECHO_REQUEST_HANDLER_HPP
#define HTTP_ECHO_REQUEST_HANDLER_HPP

#include "request_handler.hpp"

struct response;
struct request;

namespace http {
namespace server {
/// The common handler interface for all incoming requests.
class echo_request_handler : public http::server::request_handler
{
public:
  explicit echo_request_handler() {}

  //static std::shared_ptr<request_handler> Init(const std::string& location_path, const NginxConfig& config);
  static request_handler* Init(const std::string& location_path, const NginxConfig& config);

  /// Interface for handling a request and produce a response.
  response handle_request(const request& req);
};

} // namespace server
} // namespace http

#endif // HTTP_ECHO_REQUEST_HANDLER_HPP
