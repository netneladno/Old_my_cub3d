# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jjacquel/School/cub3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jjacquel/School/cub3d/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cub3d.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cub3d.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cub3d.dir/flags.make

CMakeFiles/cub3d.dir/main.c.o: CMakeFiles/cub3d.dir/flags.make
CMakeFiles/cub3d.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjacquel/School/cub3d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cub3d.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cub3d.dir/main.c.o   -c /Users/jjacquel/School/cub3d/main.c

CMakeFiles/cub3d.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cub3d.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jjacquel/School/cub3d/main.c > CMakeFiles/cub3d.dir/main.c.i

CMakeFiles/cub3d.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cub3d.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jjacquel/School/cub3d/main.c -o CMakeFiles/cub3d.dir/main.c.s

CMakeFiles/cub3d.dir/get_next_line.c.o: CMakeFiles/cub3d.dir/flags.make
CMakeFiles/cub3d.dir/get_next_line.c.o: ../get_next_line.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjacquel/School/cub3d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cub3d.dir/get_next_line.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cub3d.dir/get_next_line.c.o   -c /Users/jjacquel/School/cub3d/get_next_line.c

CMakeFiles/cub3d.dir/get_next_line.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cub3d.dir/get_next_line.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jjacquel/School/cub3d/get_next_line.c > CMakeFiles/cub3d.dir/get_next_line.c.i

CMakeFiles/cub3d.dir/get_next_line.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cub3d.dir/get_next_line.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jjacquel/School/cub3d/get_next_line.c -o CMakeFiles/cub3d.dir/get_next_line.c.s

CMakeFiles/cub3d.dir/get_next_line_utils.c.o: CMakeFiles/cub3d.dir/flags.make
CMakeFiles/cub3d.dir/get_next_line_utils.c.o: ../get_next_line_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjacquel/School/cub3d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/cub3d.dir/get_next_line_utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cub3d.dir/get_next_line_utils.c.o   -c /Users/jjacquel/School/cub3d/get_next_line_utils.c

CMakeFiles/cub3d.dir/get_next_line_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cub3d.dir/get_next_line_utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jjacquel/School/cub3d/get_next_line_utils.c > CMakeFiles/cub3d.dir/get_next_line_utils.c.i

CMakeFiles/cub3d.dir/get_next_line_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cub3d.dir/get_next_line_utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jjacquel/School/cub3d/get_next_line_utils.c -o CMakeFiles/cub3d.dir/get_next_line_utils.c.s

# Object files for target cub3d
cub3d_OBJECTS = \
"CMakeFiles/cub3d.dir/main.c.o" \
"CMakeFiles/cub3d.dir/get_next_line.c.o" \
"CMakeFiles/cub3d.dir/get_next_line_utils.c.o"

# External object files for target cub3d
cub3d_EXTERNAL_OBJECTS =

cub3d: CMakeFiles/cub3d.dir/main.c.o
cub3d: CMakeFiles/cub3d.dir/get_next_line.c.o
cub3d: CMakeFiles/cub3d.dir/get_next_line_utils.c.o
cub3d: CMakeFiles/cub3d.dir/build.make
cub3d: /usr/local/lib/libmlx.a
cub3d: CMakeFiles/cub3d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jjacquel/School/cub3d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable cub3d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cub3d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cub3d.dir/build: cub3d

.PHONY : CMakeFiles/cub3d.dir/build

CMakeFiles/cub3d.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cub3d.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cub3d.dir/clean

CMakeFiles/cub3d.dir/depend:
	cd /Users/jjacquel/School/cub3d/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jjacquel/School/cub3d /Users/jjacquel/School/cub3d /Users/jjacquel/School/cub3d/cmake-build-debug /Users/jjacquel/School/cub3d/cmake-build-debug /Users/jjacquel/School/cub3d/cmake-build-debug/CMakeFiles/cub3d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cub3d.dir/depend

