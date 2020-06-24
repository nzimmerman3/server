cmake_minimum_required(VERSION 3.10.0)
project(hr-web-server)

# Make sure developers do not run cmake in the main project directory, to keep
# build artifacts from becoming clutter
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed.
    Please make a new directory (called a build directory) and run CMake from there.
    You may need to remove CMakeCache.txt." )
endif()

# Turn on debug builds if we are building in a devel shell
if (CMAKE_BUILD_TYPE STREQUAL "" AND "$ENV{DEVEL_SHELL}" STREQUAL "1")
    message(STATUS "Setting debug build type by default in devel shell")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Output binaries to a sub directory "bin"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable cmake testing
include(CTest)
enable_testing()

# Enable GoogleTest
include(GoogleTest)
add_subdirectory(/usr/src/googletest googletest)

# Enable Boost
# Use static libraries so binaries can be deployed without a full boost install
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.50 REQUIRED COMPONENTS system log)
message(STATUS "Boost version: ${Boost_VERSION}")

include_directories(include libraries/sqlite3/include)

# Add necessary libraries

# Boost HTTP Library
#add_library(bhttp_resp libraries/boost-http/src/response.cpp)
add_library(bhttp_req_parser libraries/boost-http/src/request_parser.cpp)
add_library(bhttp_ereq_handler libraries/boost-http/src/echo_request_handler.cpp)
add_library(bhttp_sreq_handler libraries/boost-http/src/static_request_handler.cpp)
add_library(bhttp_404req_handler libraries/boost-http/src/404_request_handler.cpp)
add_library(bhttp_healthreq_handler libraries/boost-http/src/health_request_handler.cpp)
add_library(bhttp_statusreq_handler libraries/boost-http/src/status_request_handler.cpp)
add_library(bhttp_proxy_handler libraries/boost-http/src/proxy_request_handler.cpp)
add_library(bhttp_meme_gen_handler libraries/boost-http/src/meme_gen_request_handler.cpp)
add_library(bhttp_mime libraries/boost-http/src/mime_types.cpp)

add_library(sqlite3_lib libraries/sqlite3/src/sqlite3.c)

add_library(response_generator_lib src/response_generator.cc)
add_library(server_status_lib src/server_status_singleton.cc)
add_library(meme_gen_backend_lib src/meme_gen_backend.cc)
add_library(meme_gen_frontend_lib src/meme_gen_frontend.cc)
add_library(meme_gen_database_lib src/meme_gen_database.cc)
#target_link_libraries(response_generator_lib bhttp_resp)
target_link_libraries(response_generator_lib)
target_link_libraries(bhttp_statusreq_handler server_status_lib)
target_link_libraries(meme_gen_database_lib sqlite3_lib ${CMAKE_DL_LIBS})
target_link_libraries(bhttp_meme_gen_handler response_generator_lib meme_gen_backend_lib meme_gen_frontend_lib meme_gen_database_lib)

add_library(request_router_lib src/request_router.cc)
target_link_libraries(request_router_lib bhttp_ereq_handler bhttp_sreq_handler bhttp_404req_handler bhttp_healthreq_handler bhttp_statusreq_handler bhttp_proxy_handler bhttp_meme_gen_handler bhttp_mime server_status_lib)

add_library(session_lib src/session.cc)
target_link_libraries(session_lib bhttp_req_parser server_status_lib)

add_library(server_lib src/server.cc)
add_library(config_parser_lib src/config_parser.cc)
add_library(logger_lib src/logger.cc)
target_link_libraries(logger_lib Boost::log)

# Update executable name, srcs, and deps
add_executable(server src/server_main.cc)
target_link_libraries(server Boost::system server_lib session_lib config_parser_lib logger_lib request_router_lib response_generator_lib Boost::log_setup Boost::log)

# Update test executable name, srcs, and deps
add_executable(config_parser_lib_test tests/config_parser/config_parser_test.cc)
add_executable(server_lib_test tests/server/server_test.cc)
add_executable(session_lib_test tests/session/session_test.cc)
add_executable(404_request_handler_test tests/handlers/404_request_handler_test.cc)
#add_executable(bhttp_req_parser_test tests/boost-http/request_parser_test.cc)
add_executable(request_router_lib_test tests/request_router/request_router_test.cc)
target_link_libraries(config_parser_lib_test config_parser_lib gtest_main)
target_link_libraries(server_lib_test server_lib gtest_main Boost::system)
target_link_libraries(session_lib_test session_lib gtest_main Boost::system)
target_link_libraries(404_request_handler_test bhttp_404req_handler response_generator_lib gtest_main Boost::system Boost::log_setup Boost::log)
#target_link_libraries(bhttp_req_parser_test bhttp_req_parser gtest_main)
target_link_libraries(request_router_lib_test request_router_lib response_generator_lib config_parser_lib gtest_main Boost::system Boost::log_setup Boost::log)

add_test(NAME echo_integration_test COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration_tests/echo_integration_test.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_test(NAME static_file_integration_test COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration_tests/static_file_integration_test.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_test(NAME multithread_integration_test COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/integration_tests/multithread_integration_test.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Update with test binary
gtest_discover_tests(config_parser_lib_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/config_parser)
gtest_discover_tests(server_lib_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/server)
gtest_discover_tests(session_lib_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/session)
gtest_discover_tests(404_request_handler_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/handlers)
#gtest_discover_tests(bhttp_req_parser_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/boost-http)
gtest_discover_tests(request_router_lib_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/request_router)


# Update with target/test targets
include(cmake/CodeCoverageReportConfig.cmake)
#generate_coverage_report(TARGETS server server_lib session_lib config_parser_lib bhttp_req_parser TESTS config_parser_lib_test server_lib_test session_lib_test bhttp_req_parser_test request_router_lib_test)
generate_coverage_report(TARGETS server server_lib session_lib config_parser_lib bhttp_req_parser bhttp_404req_handler request_router_lib TESTS config_parser_lib_test server_lib_test session_lib_test 404_request_handler_test request_router_lib_test)
