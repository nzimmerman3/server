#ifndef PROXY_REQUEST_HANDLER_HPP
#define PROXY_REQUEST_HANDLER_HPP

#include "request_handler.hpp"

struct response;
struct request;

namespace http {
namespace server {
/// The common handler interface for all incoming requests.
class proxy_request_handler : public http::server::request_handler {
public:
  static proxy_request_handler* Init(const std::string& location_path, const NginxConfig& config);
  /// Interface for handling a request and produce a response.
  response handle_request(const request& req);

private:
	proxy_request_handler(const std::string proxy_dest, const std::string prefix, const int port);
	std::string prefix_;
  	std::string proxy_dest_;
  	int port_;
};

} // namespace server
} // namespace http

#endif // PROXY_REQUEST_HANDLER_HPP