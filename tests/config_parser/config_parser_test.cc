#include "gtest/gtest.h"
#include "config_parser.h"

#include <string>
#include <vector>

class NginxConfigParserTest : public ::testing::Test {
  protected:
    NginxConfigParser parser;
    NginxConfig out_config;
};

TEST_F(NginxConfigParserTest, GetStatementsForTest) {
	parser.Parse("common_format_config", &out_config);

  // PORTS
  auto ports = out_config.getStatementsFor("port");

  // port 8080;
  auto port = ports[0];
  EXPECT_EQ(port->tokens_[0], "port");
  EXPECT_EQ(port->tokens_[1], "8080");
  EXPECT_EQ(port->child_block_, nullptr);

  /* Example Usage
    int port = -1;
    auto ports = config.getStatementsFor("port");
    if (ports.size() > 0 && ports[0]->tokens_.size() > 1) {
      port = std::stoi(ports[0]->tokens_[1]);
    }
  */

  // LOCATIONS
  auto locations = out_config.getStatementsFor("location");

  // location "/echo" EchoHandler {}
  auto echo = locations[0];
  EXPECT_EQ(echo->tokens_[0], "location");
  EXPECT_EQ(echo->tokens_[1], "\"/echo\"");
  EXPECT_EQ(echo->tokens_[2], "EchoHandler");

  // location "/images" StaticHandler {
  //   root "./img";
  // }
  auto images = locations[1];
  EXPECT_EQ(images->tokens_[0], "location");
  EXPECT_EQ(images->tokens_[1], "\"/images\"");
  EXPECT_EQ(images->tokens_[2], "StaticHandler");

  auto imagesRoot = images->child_block_->getStatementsFor("root")[0];
  EXPECT_EQ(imagesRoot->tokens_[0], "root");
  EXPECT_EQ(imagesRoot->tokens_[1], "\"./img\"");
  EXPECT_EQ(imagesRoot->child_block_, nullptr);

  // location "/documents" StaticHandler {
  //     root "./docs";
  // }
  auto documents = locations[2];
  EXPECT_EQ(documents->tokens_[0], "location");
  EXPECT_EQ(documents->tokens_[1], "\"/documents\"");
  EXPECT_EQ(documents->tokens_[2], "StaticHandler");

  auto documentsRoot = documents->child_block_->getStatementsFor("root")[0];
  EXPECT_EQ(documentsRoot->tokens_[0], "root");
  EXPECT_EQ(documentsRoot->tokens_[1], "\"./docs\"");
  EXPECT_EQ(documentsRoot->child_block_, nullptr);

  /* Example Usage
    auto locations = config.getStatementFor("location");
    std::vector<
      std::tuple< std::vector<std::string>, NginxConfig> > handlers;

    for (auto const& location: locations) {
      // Note: can std::unique_ptr<NginxConfig> be dereferenced to get NginxConfig?
      if (location->child_block_ != nullptr) {
        handlers.push_back(location->tokens_, *location->child_block_);
      }
    }

    for (auto const& handler: handlers) {
      auto handlerUri = std::get<0>(handler)[1];
      auto handlerName = std::get<0>(handler)[2];
      auto handlerConfig = std::get<1>(handler);
      if (handlerName == "EchoHandler") {
        ...
      } ...
    }
  */
}

// Valid Configs
TEST_F(NginxConfigParserTest, ExampleConfig) {
  EXPECT_TRUE(parser.Parse("example_config", &out_config));
}

TEST_F(NginxConfigParserTest, WhitespaceConfig) {
  EXPECT_TRUE(parser.Parse("whitespace_config", &out_config));
}

TEST_F(NginxConfigParserTest, EmptyConfig) {
  EXPECT_TRUE(parser.Parse("empty_config", &out_config));
}

TEST_F(NginxConfigParserTest, NestedBlocksConfig) {
  EXPECT_TRUE(parser.Parse("nested_blocks_config", &out_config));
}

TEST_F(NginxConfigParserTest, EmptyBlocksConfig) {
  EXPECT_TRUE(parser.Parse("empty_blocks_config", &out_config));
}

TEST_F(NginxConfigParserTest, CommentsConfig) {
  EXPECT_TRUE(parser.Parse("comments_config", &out_config));
}

TEST_F(NginxConfigParserTest, SingleQuotesConfig) {
  EXPECT_TRUE(parser.Parse("single_quotes_config", &out_config));
}

// Invalid Configs
TEST_F(NginxConfigParserTest, NoConfig) {
  EXPECT_FALSE(parser.Parse("", &out_config));
}

TEST_F(NginxConfigParserTest, ExtraSemicolonConfig) {
  EXPECT_FALSE(parser.Parse("extra_semicolon_config", &out_config));
}

TEST_F(NginxConfigParserTest, MissingSemicolonConfig) {
  EXPECT_FALSE(parser.Parse("missing_semicolon_config", &out_config));
}

TEST_F(NginxConfigParserTest, BrokenSingleQuotesConfig) {
  EXPECT_FALSE(parser.Parse("broken_single_quotes_config", &out_config));
}

TEST_F(NginxConfigParserTest, ToStringTest) {
	parser.Parse("test_config", &out_config);
	const auto& statement = out_config.statements_.front();
	EXPECT_EQ(statement->ToString(1), "  server {\n    listen 8080 server_name foo.com;\n  }\n");
}