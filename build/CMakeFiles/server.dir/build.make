# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /c/Users/Nick/cs130/hr-web-server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /c/Users/Nick/cs130/hr-web-server/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/src/server_main.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/server_main.cc.o: ../src/server_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/src/server_main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/server_main.cc.o -c /c/Users/Nick/cs130/hr-web-server/src/server_main.cc

CMakeFiles/server.dir/src/server_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/server_main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /c/Users/Nick/cs130/hr-web-server/src/server_main.cc > CMakeFiles/server.dir/src/server_main.cc.i

CMakeFiles/server.dir/src/server_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/server_main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /c/Users/Nick/cs130/hr-web-server/src/server_main.cc -o CMakeFiles/server.dir/src/server_main.cc.s

CMakeFiles/server.dir/src/server_main.cc.o.requires:

.PHONY : CMakeFiles/server.dir/src/server_main.cc.o.requires

CMakeFiles/server.dir/src/server_main.cc.o.provides: CMakeFiles/server.dir/src/server_main.cc.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/src/server_main.cc.o.provides.build
.PHONY : CMakeFiles/server.dir/src/server_main.cc.o.provides

CMakeFiles/server.dir/src/server_main.cc.o.provides.build: CMakeFiles/server.dir/src/server_main.cc.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/src/server_main.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

bin/server: CMakeFiles/server.dir/src/server_main.cc.o
bin/server: CMakeFiles/server.dir/build.make
bin/server: /usr/lib/x86_64-linux-gnu/libboost_system.a
bin/server: libserver_lib.a
bin/server: libsession_lib.a
bin/server: libconfig_parser_lib.a
bin/server: liblogger_lib.a
bin/server: librequest_router_lib.a
bin/server: libresponse_generator_lib.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_log_setup.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_log.a
bin/server: libbhttp_req_parser.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_log_setup.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_thread.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_date_time.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_regex.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_chrono.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_system.a
bin/server: /usr/lib/x86_64-linux-gnu/libboost_atomic.a
bin/server: libbhttp_ereq_handler.a
bin/server: libbhttp_sreq_handler.a
bin/server: libbhttp_404req_handler.a
bin/server: libbhttp_healthreq_handler.a
bin/server: libbhttp_statusreq_handler.a
bin/server: libserver_status_lib.a
bin/server: libbhttp_proxy_handler.a
bin/server: libbhttp_meme_gen_handler.a
bin/server: libresponse_generator_lib.a
bin/server: libmeme_gen_backend_lib.a
bin/server: libmeme_gen_frontend_lib.a
bin/server: libmeme_gen_database_lib.a
bin/server: libsqlite3_lib.a
bin/server: libbhttp_mime.a
bin/server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: bin/server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/requires: CMakeFiles/server.dir/src/server_main.cc.o.requires

.PHONY : CMakeFiles/server.dir/requires

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /c/Users/Nick/cs130/hr-web-server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

