#ifndef RESPONSE_GENERATOR_H
#define RESPONSE_GENERATOR_H

#include <boost/asio.hpp>
#include <string>
#include "../libraries/boost-http/include/response.hpp"

namespace http {
namespace server {

class response_generator {
    public:

        /// Convert the response into a vector of buffers. The buffers do not own the
        /// underlying memory blocks, therefore the response object must remain valid and
        /// not be changed until the write operation has completed.
        static std::vector<boost::asio::const_buffer> to_buffers(http::server::response rep);

        static http::server::response stock_response(http::server::response::status_type code);

};

} // namespace server
} //namespace http

#endif // RESPONSE_GENERATOR_H