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
include CMakeFiles/sqlite3_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sqlite3_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sqlite3_lib.dir/flags.make

CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o: CMakeFiles/sqlite3_lib.dir/flags.make
CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o: ../libraries/sqlite3/src/sqlite3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o   -c /c/Users/Nick/cs130/hr-web-server/libraries/sqlite3/src/sqlite3.c

CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /c/Users/Nick/cs130/hr-web-server/libraries/sqlite3/src/sqlite3.c > CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.i

CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /c/Users/Nick/cs130/hr-web-server/libraries/sqlite3/src/sqlite3.c -o CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.s

CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.requires:

.PHONY : CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.requires

CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.provides: CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.requires
	$(MAKE) -f CMakeFiles/sqlite3_lib.dir/build.make CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.provides.build
.PHONY : CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.provides

CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.provides.build: CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o


# Object files for target sqlite3_lib
sqlite3_lib_OBJECTS = \
"CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o"

# External object files for target sqlite3_lib
sqlite3_lib_EXTERNAL_OBJECTS =

libsqlite3_lib.a: CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o
libsqlite3_lib.a: CMakeFiles/sqlite3_lib.dir/build.make
libsqlite3_lib.a: CMakeFiles/sqlite3_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/c/Users/Nick/cs130/hr-web-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libsqlite3_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/sqlite3_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sqlite3_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sqlite3_lib.dir/build: libsqlite3_lib.a

.PHONY : CMakeFiles/sqlite3_lib.dir/build

CMakeFiles/sqlite3_lib.dir/requires: CMakeFiles/sqlite3_lib.dir/libraries/sqlite3/src/sqlite3.c.o.requires

.PHONY : CMakeFiles/sqlite3_lib.dir/requires

CMakeFiles/sqlite3_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sqlite3_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sqlite3_lib.dir/clean

CMakeFiles/sqlite3_lib.dir/depend:
	cd /c/Users/Nick/cs130/hr-web-server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build /c/Users/Nick/cs130/hr-web-server/build/CMakeFiles/sqlite3_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sqlite3_lib.dir/depend

