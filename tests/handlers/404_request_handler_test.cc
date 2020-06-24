#include "gtest/gtest.h"
#include "../../include/config_parser.h"
#include "../../libraries/boost-http/include/request.hpp"
#include "../../libraries/boost-http/include/response.hpp"
#include "../../libraries/boost-http/include/404_request_handler.hpp"


class NotFoundRequestHandlerTests : public ::testing::Test {
    public:
        http::server::request req;

        http::server::not_found_request_handler *handler;

        void setup() {
            req.method_ = http::server::request::GET;
            req.uri_ = "/random/path";
            req.version_ = "HTTP/1.1";

            NginxConfig config;

            handler = http::server::not_found_request_handler::Init("/", config);
        }
};

TEST_F(NotFoundRequestHandlerTests, CorrectResponseTest) {
    NotFoundRequestHandlerTests::setup();
    http::server::response resp = handler->handle_request(req);
    EXPECT_EQ(resp.code_, http::server::response::not_found);
}