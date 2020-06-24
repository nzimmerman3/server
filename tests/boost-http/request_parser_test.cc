#include "gtest/gtest.h"
#include "../../libraries/boost-http/include/request_parser.hpp"
#include "../../libraries/boost-http/include/request.hpp"
#include "../../libraries/boost-http/include/header.hpp"

class RequestParserTests : public ::testing::Test {
    protected:
        http::server::request_parser reqParser;
};

TEST_F(RequestParserTests, ParseValidRequest) {
    std::string rawRequest = "GET / HTTP/1.1\r\nConnection: keep-alive\r\n\r\n";
    http::server::request goldenRequest;
    goldenRequest.method = "GET";
    goldenRequest.uri = "/";
    goldenRequest.http_version_major = 1;
    goldenRequest.http_version_minor = 1;
    http::server::header header;
    header.name = "Connection";
    header.value = "keep-alive";
    goldenRequest.headers.push_back(header);
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::good);
    // TODO: Overload = operator to make comparison of request easier
    EXPECT_EQ(request.method, goldenRequest.method);
    EXPECT_EQ(request.uri, goldenRequest.uri);
    EXPECT_EQ(request.http_version_major, goldenRequest.http_version_major);
    EXPECT_EQ(request.http_version_minor, goldenRequest.http_version_minor);
    // EXPECT_EQ(request.headers, goldenRequest.headers);
}

TEST_F(RequestParserTests, MissingMethodRequest) {
    std::string rawRequest = "/ HTTP/1.1\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, MissingURIRequest) {
    std::string rawRequest = "GET HTTP/1.1\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, MissingVersionRequest) {
    std::string rawRequest = "GET /\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, VersionMissingSlashRequest) {
    std::string rawRequest = "GET / HTTP1.1\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, VersionMissingDotRequest) {
    std::string rawRequest = "GET / HTTP/11\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, VersionMissingMajorRequest) {
    std::string rawRequest = "GET / HTTP/.1\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, VersionMissingMinorRequest) {
    std::string rawRequest = "GET / HTTP/1\r\nConnection: keep-alive\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, MissingHeaderValueRequest) {
    std::string rawRequest = "GET / HTTP/1.1\r\nConnection:\r\n\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::bad);
}

TEST_F(RequestParserTests, ParseIncompleteRequest) {
    std::string rawRequest = "GET / HTTP/1.1\r\nConnection: keep-alive\r\n";
    http::server::request request;

    http::server::request_parser::result_type rc = std::get<0>(reqParser.parse(request, rawRequest.begin(), rawRequest.end()));
    EXPECT_EQ(rc, http::server::request_parser::indeterminate);
}