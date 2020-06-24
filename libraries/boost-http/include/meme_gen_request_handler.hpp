#ifndef MEME_GEN_HANDLER_HPP
#define MEME_GEN_HANDLER_HPP

#include <string>
#include "request_handler.hpp"

#include "../../../include/config_parser.h"
#include "request.hpp"
#include "response.hpp"
#include "../../../include/meme_gen_database.h"
#include "../../../include/meme_gen_frontend.h"
#include "../../../include/meme_gen_backend.h"

namespace http {
namespace server {

class meme_gen_request_handler : public http::server::request_handler {
    public:
        static meme_gen_request_handler* Init(const std::string& location_path, const NginxConfig& config);
        http::server::response handle_request(const http::server::request& request);

    private:
        meme_gen_request_handler();
        std::shared_ptr<meme_gen_frontend> frontend_;
        std::shared_ptr<meme_gen_backend> backend_;
};

} // namespace server
} // namespace http

#endif // MEME_GEN_HANDLER_HPP