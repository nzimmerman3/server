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
include CMakeFiles/bhttp_404req_handler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bhttp_404req_handler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bhttp_404req_handler.dir/flags.make

CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o: CMakeFiles/bhttp_404req_handler.dir/flags.make
CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o: ../libraries/boost-http/src/404_request_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o -c /c/Users/Nick/cs130/hr-web-server/libraries/boost-http/src/404_request_handler.cpp

CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /c/Users/Nick/cs130/hr-web-server/libraries/boost-http/src/404_request_handler.cpp > CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.i

CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /c/Users/Nick/cs130/hr-web-server/libraries/boost-http/src/404_request_handler.cpp -o CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.s

CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.requires:

.PHONY : CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.requires

CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.provides: CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.requires
	$(MAKE) -f CMakeFiles/bhttp_404req_handler.dir/build.make CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.provides.build
.PHONY : CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.provides

CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.provides.build: CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o


# Object files for target bhttp_404req_handler
bhttp_404req_handler_OBJECTS = \
"CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o"

# External object files for target bhttp_404req_handler
bhttp_404req_handler_EXTERNAL_OBJECTS =

libbhttp_404req_handler.a: CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o
libbhttp_404req_handler.a: CMakeFiles/bhttp_404req_handler.dir/build.make
libbhttp_404req_handler.a: CMakeFiles/bhttp_404req_handler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbhttp_404req_handler.a"
	$(CMAKE_COMMAND) -P CMakeFiles/bhttp_404req_handler.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bhttp_404req_handler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bhttp_404req_handler.dir/build: libbhttp_404req_handler.a

.PHONY : CMakeFiles/bhttp_404req_handler.dir/build

CMakeFiles/bhttp_404req_handler.dir/requires: CMakeFiles/bhttp_404req_handler.dir/libraries/boost-http/src/404_request_handler.cpp.o.requires

.PHONY : CMakeFiles/bhttp_404req_handler.dir/requires

CMakeFiles/bhttp_404req_handler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bhttp_404req_handler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bhttp_404req_handler.dir/clean

CMakeFiles/bhttp_404req_handler.dir/depend:
	cd /c/Users/Nick/cs130/hr-web-server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build/CMakeFiles/bhttp_404req_handler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bhttp_404req_handler.dir/depend

