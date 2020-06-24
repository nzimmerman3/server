#include "gtest/gtest.h"
#include "../../include/request_router.h"
#include "../../include/response_generator.h"
#include "../../include/config_parser.h"

#include <string>
#include <vector>

class requestRouterTest : public ::testing::Test{
  public:
    NginxConfig config;
    NginxConfigParser parser;
    http::server::request req;
    http::server::response res;
    std::string con;

    void initEcho() {
        req.method_= http::server::request::GET;
        req.uri_ = "/echo";
        req.version_ = "HTTP/1.1";
        req.headers_["Host"] = "localhost:8080";
        con.append("GET /echo HTTP/1.1\r\n");
        con.append("Host: localhost:8080\r\n");
        con.append("\r\n");
    }

    void initStatic() {
        req.uri_ = "/static1/file.txt";
    }
};

TEST_F(requestRouterTest, EchoTest) {
    parser.Parse("config", &config);
    requestRouterTest::initEcho();
    request_router router(config);
    router.route(req, res, "5.5.5.5");
    EXPECT_EQ(res.body_, con);
}

TEST_F(requestRouterTest, StaticTest) {
    parser.Parse("config", &config);
    requestRouterTest::initStatic();
    request_router router(config);
    router.route(req, res, "5.5.5.5");
    EXPECT_EQ(res.code_, http::server::response::not_found); //static handler was correctly called
}