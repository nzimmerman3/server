if(EXISTS "/c/Users/Nick/cs130/hr-web-server/build/server_lib_test[1]_tests.cmake")
  include("/c/Users/Nick/cs130/hr-web-server/build/server_lib_test[1]_tests.cmake")
else()
  add_test(server_lib_test_NOT_BUILT server_lib_test_NOT_BUILT)
endif()
