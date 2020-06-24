# CMake generated Testfile for 
# Source directory: /c/Users/Nick/cs130/hr-web-server
# Build directory: /c/Users/Nick/cs130/hr-web-server/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/c/Users/Nick/cs130/hr-web-server/build/config_parser_lib_test[1]_include.cmake")
include("/c/Users/Nick/cs130/hr-web-server/build/server_lib_test[1]_include.cmake")
include("/c/Users/Nick/cs130/hr-web-server/build/session_lib_test[1]_include.cmake")
include("/c/Users/Nick/cs130/hr-web-server/build/404_request_handler_test[1]_include.cmake")
include("/c/Users/Nick/cs130/hr-web-server/build/request_router_lib_test[1]_include.cmake")
add_test(echo_integration_test "/c/Users/Nick/cs130/hr-web-server/tests/integration_tests/echo_integration_test.sh")
set_tests_properties(echo_integration_test PROPERTIES  WORKING_DIRECTORY "/c/Users/Nick/cs130/hr-web-server/build/bin")
add_test(static_file_integration_test "/c/Users/Nick/cs130/hr-web-server/tests/integration_tests/static_file_integration_test.sh")
set_tests_properties(static_file_integration_test PROPERTIES  WORKING_DIRECTORY "/c/Users/Nick/cs130/hr-web-server/build/bin")
add_test(multithread_integration_test "/c/Users/Nick/cs130/hr-web-server/tests/integration_tests/multithread_integration_test.sh")
set_tests_properties(multithread_integration_test PROPERTIES  WORKING_DIRECTORY "/c/Users/Nick/cs130/hr-web-server/build/bin")
subdirs("googletest")
