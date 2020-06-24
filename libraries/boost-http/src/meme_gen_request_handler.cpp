#include "../include/meme_gen_request_handler.hpp"
#include "../include/response.hpp"

#include "../../../include/response_generator.h"
#include "logger.h"

namespace http {
namespace server {

meme_gen_request_handler::meme_gen_request_handler() : backend_(new meme_gen_backend), frontend_(new meme_gen_frontend)
{
    frontend_->init(backend_);
}

meme_gen_request_handler* meme_gen_request_handler::Init(const std::string& location_path, const NginxConfig& config)
{
    meme_gen_request_handler *handler = new meme_gen_request_handler();
    return handler;
}

http::server::response meme_gen_request_handler::handle_request(const http::server::request& request)
{
    response rep;
    std::string body = "";

    src::severity_logger_mt<logging::trivial::severity_level> slg;

    if (request.uri_ == "/create")
    {
        BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme create request received";
        body = frontend_->generate_create_page();
    }
    else if (request.uri_.size() >= 6 && request.uri_.substr(0, 6) == "/view-")
    {
      int id;
       try {
           id = std::stoi(request.uri_.substr(6));
       }
       catch(std::exception& e) {
           BOOST_LOG_SEV(slg, logging::trivial::info) << "Invalid meme view id";
           return http::server::response_generator::stock_response(http::server::response::not_found);
       }
        BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme view request received with id:" << id;
        //will most likely want to add id to params
        body = frontend_->generate_single_meme_page(id);

        //meme with id requested does not exist, send 404
        if(body == "") {
            return http::server::response_generator::stock_response(http::server::response::not_found);
        }
    }
    else if (request.uri_ == "/vote")
    {
        BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme vote request received";
        body = frontend_->generate_vote_page();
    }
    else if (request.uri_ == "/leaderboard")
    {
        BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme leaderboard request received";
        body = frontend_->generate_leaderboard_page();
    }
    // else if (request.uri_.size() >= 20 && request.uri_.substr(0, 18) == "/create-submission")
    else if (request.uri_.size() >= 16 && request.uri_.substr(0, 16) == "/?memetemplates=")
    {
        BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme create-submission request received";
        meme m = backend_->parse_create_submission(request.uri_.substr(2));
        backend_->create_meme(m);
        body = frontend_->generate_link_page(m.id_);
    }
    else if (request.uri_.size() >= 5 && request.uri_.substr(0,5) == "/?id=")
    {
        BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme vote-submission request received";
        int id = backend_->parse_vote_submission(request.uri_.substr(2));
        backend_->vote_meme(id);
        // body = frontend_->generate_vote_page();
        body = frontend_->generate_vote_counted_page();
    }
    else // User request prefixed by "/meme" (ie: "/meme/bad-path") not found so return 404
    {
        return http::server::response_generator::stock_response(http::server::response::not_found);
    }

    rep.headers_["Content-Length"] = std::to_string(body.size());
    rep.headers_["Content-Type"] = "text/html";
    rep.code_ = http::server::response::ok;
    rep.body_ = body;
    return rep;
}

} // namespace server
} // namespace http
