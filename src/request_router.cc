#include <string>
#include <iostream>
#include <tuple>
#include <typeinfo>

#include "request_router.h"
#include "response_generator.h"

#include "../libraries/boost-http/include/404_request_handler.hpp"
#include "../libraries/boost-http/include/health_request_handler.hpp"
#include "../libraries/boost-http/include/status_request_handler.hpp"
#include "../libraries/boost-http/include/proxy_request_handler.hpp"
#include "../libraries/boost-http/include/meme_gen_request_handler.hpp"
#include "../include/server_status_singleton.h"

request_router::request_router(NginxConfig& config) : config_(config) {
    populateMap();
}

void request_router::populateMap() {
    std::vector<std::tuple< std::vector<std::string>, NginxConfig> > handlers;

    auto locations = config_.getStatementsFor("location");
    for (auto const& location: locations) {
      if (location->child_block_ != nullptr) {
        handlers.push_back(std::make_tuple(location->tokens_, *location->child_block_));
      }
    }

    for (auto const& handler: handlers) {

      if (std::get<0>(handler).size() >= 3) {
        auto handlerUri = std::get<0>(handler)[1];
        handlerUri.erase(std::remove(handlerUri.begin(), handlerUri.end(), '\"'), handlerUri.end());
        auto handlerName = std::get<0>(handler)[2];
        auto handlerConfig = std::get<1>(handler);

        std::cerr << "Handler" << std::endl;
        std::cerr << "handlerUri: " << handlerUri << std::endl;
        std::cerr << "handlerName: " << handlerName << std::endl;

        server_status_singleton::getInstance()->addHandlerConfig(handlerName, handlerUri);

        auto roots = handlerConfig.getStatementsFor("root");
        std::string handlerRoot = "";
        if (roots.size() > 0 && roots[0]->tokens_.size() > 1) {
            handlerRoot = roots[0]->tokens_[1];
            handlerRoot.erase(std::remove(handlerRoot.begin(), handlerRoot.end(), '\"'), handlerRoot.end());
            std::cerr << "handlerRoot: " << handlerRoot << std::endl;
        }

        if (handlerName == "EchoHandler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::echo_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else if (handlerName == "StaticHandler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::static_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else if (handlerName == "HealthHandler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::health_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else if (handlerName == "404Handler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::not_found_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else if (handlerName == "StatusHandler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::status_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else if (handlerName == "ProxyHandler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::proxy_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else if (handlerName == "MemeGenHandler") {
            auto smart = std::shared_ptr<http::server::request_handler>(http::server::meme_gen_request_handler::Init(handlerRoot, handlerConfig));
            handlerMap_[handlerUri] = smart;
        } else {
            BOOST_LOG_SEV(slg_, logging::trivial::error) << "Unknown handler type.";
        }
      } else {
            BOOST_LOG_SEV(slg_, logging::trivial::error) << "Handler missing arguments.";
      }
    }
}

bool request_router::route(http::server::request& request, http::server::response& response, std::string ip) {
    slg_.add_attribute("IPAddress", attrs::constant< std::string >(ip));

    std::cerr << "Request Uri Initial: " << request.uri_ << std::endl;

    std::string requestUri = request.uri_;
    bool match = false;
    while (match == false && requestUri.size() > 0) {
        // try to find match
        std::cerr << "looking for: " << requestUri << std::endl;
        for (auto it = handlerMap_.begin(); it != handlerMap_.end(); ++it) {
            std::string handlerUri = it->first;
            std::cerr << "handlerUri: " << handlerUri << std::endl;
            if (requestUri == handlerUri) {
                std::cerr << "MATCH FOUND: " << requestUri << std::endl;
                match = true;
                break;
            }
        }

        if (match == false) {
            // if last char is '/' strip it
            if (requestUri.back() == '/') {
                requestUri.pop_back();
            // else strip up to slash
            } else {
                while (requestUri.size() > 0 && requestUri.back() != '/') {
                    requestUri.pop_back();
                }
            }
        }
    }

    std::cerr << "Request Uri Match: " << requestUri << std::endl;

    std::string filename = "";
    auto it = handlerMap_.find(requestUri);
    if (it != handlerMap_.end()) {
        // Manually checking to see if handler type is reverse proxy. This is because
        // filename parsing is different for reverse proxy, which needs fully qualified uri.
        //
        // This code essentially finds the index of the second slash
        // in an absolute path, so that when finding the uri, we can
        // simple add everything past the index. It gets the entire
        // uri, not just everything past the last slash
        //
        // E.g. /static/img/photos/hello.jpg -> /img/photos/hello.jpg
        //
        // Optimally, this code should be factored out of request router.
        if (typeid(*it->second) == typeid(http::server::proxy_request_handler)) {
            int idx;
            for (idx = 1; idx < request.uri_.size(); idx++)
                if (request.uri_[idx] == '/')
                    break;

            for (int i = request.uri_.size() - 1; i >= idx; i--) {
                filename = request.uri_[i] + filename;
            }
        } else {
            // All other handlers, use only filename
            for (int i = request.uri_.size() - 1; i >= 0; i--) {
                filename = request.uri_[i] + filename;
                if (request.uri_[i] == '/') break;
            }
        }

        std::cerr << "Filename: " << filename << std::endl;

        request.uri_ = filename;

        response = it->second->handle_request(request);
    } else {
        BOOST_LOG_SEV(slg_, logging::trivial::error) << "Could not find path requested. Sending 404 response. Reponse Metrics: 404, " << request.uri_;
        response = http::server::response_generator::stock_response(http::server::response::not_found);
    }
}
