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
include CMakeFiles/request_router_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/request_router_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/request_router_lib.dir/flags.make

CMakeFiles/request_router_lib.dir/src/request_router.cc.o: CMakeFiles/request_router_lib.dir/flags.make
CMakeFiles/request_router_lib.dir/src/request_router.cc.o: ../src/request_router.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/request_router_lib.dir/src/request_router.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/request_router_lib.dir/src/request_router.cc.o -c /c/Users/Nick/cs130/hr-web-server/src/request_router.cc

CMakeFiles/request_router_lib.dir/src/request_router.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/request_router_lib.dir/src/request_router.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /c/Users/Nick/cs130/hr-web-server/src/request_router.cc > CMakeFiles/request_router_lib.dir/src/request_router.cc.i

CMakeFiles/request_router_lib.dir/src/request_router.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/request_router_lib.dir/src/request_router.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /c/Users/Nick/cs130/hr-web-server/src/request_router.cc -o CMakeFiles/request_router_lib.dir/src/request_router.cc.s

CMakeFiles/request_router_lib.dir/src/request_router.cc.o.requires:

.PHONY : CMakeFiles/request_router_lib.dir/src/request_router.cc.o.requires

CMakeFiles/request_router_lib.dir/src/request_router.cc.o.provides: CMakeFiles/request_router_lib.dir/src/request_router.cc.o.requires
	$(MAKE) -f CMakeFiles/request_router_lib.dir/build.make CMakeFiles/request_router_lib.dir/src/request_router.cc.o.provides.build
.PHONY : CMakeFiles/request_router_lib.dir/src/request_router.cc.o.provides

CMakeFiles/request_router_lib.dir/src/request_router.cc.o.provides.build: CMakeFiles/request_router_lib.dir/src/request_router.cc.o


# Object files for target request_router_lib
request_router_lib_OBJECTS = \
"CMakeFiles/request_router_lib.dir/src/request_router.cc.o"

# External object files for target request_router_lib
request_router_lib_EXTERNAL_OBJECTS =

librequest_router_lib.a: CMakeFiles/request_router_lib.dir/src/request_router.cc.o
librequest_router_lib.a: CMakeFiles/request_router_lib.dir/build.make
librequest_router_lib.a: CMakeFiles/request_router_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librequest_router_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/request_router_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/request_router_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/request_router_lib.dir/build: librequest_router_lib.a

.PHONY : CMakeFiles/request_router_lib.dir/build

CMakeFiles/request_router_lib.dir/requires: CMakeFiles/request_router_lib.dir/src/request_router.cc.o.requires

.PHONY : CMakeFiles/request_router_lib.dir/requires

CMakeFiles/request_router_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/request_router_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/request_router_lib.dir/clean

CMakeFiles/request_router_lib.dir/depend:
	cd /c/Users/Nick/cs130/hr-web-server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build/CMakeFiles/request_router_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/request_router_lib.dir/depend

