# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ljr/Desktop/SKT/dfcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ljr/Desktop/SKT/dfcpp/build

# Include any dependencies generated for this target.
include benchmark/CMakeFiles/matdot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include benchmark/CMakeFiles/matdot.dir/compiler_depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/matdot.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/matdot.dir/flags.make

benchmark/CMakeFiles/matdot.dir/matdot.cpp.o: benchmark/CMakeFiles/matdot.dir/flags.make
benchmark/CMakeFiles/matdot.dir/matdot.cpp.o: ../benchmark/matdot.cpp
benchmark/CMakeFiles/matdot.dir/matdot.cpp.o: benchmark/CMakeFiles/matdot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljr/Desktop/SKT/dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/matdot.dir/matdot.cpp.o"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT benchmark/CMakeFiles/matdot.dir/matdot.cpp.o -MF CMakeFiles/matdot.dir/matdot.cpp.o.d -o CMakeFiles/matdot.dir/matdot.cpp.o -c /home/ljr/Desktop/SKT/dfcpp/benchmark/matdot.cpp

benchmark/CMakeFiles/matdot.dir/matdot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matdot.dir/matdot.cpp.i"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljr/Desktop/SKT/dfcpp/benchmark/matdot.cpp > CMakeFiles/matdot.dir/matdot.cpp.i

benchmark/CMakeFiles/matdot.dir/matdot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matdot.dir/matdot.cpp.s"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljr/Desktop/SKT/dfcpp/benchmark/matdot.cpp -o CMakeFiles/matdot.dir/matdot.cpp.s

# Object files for target matdot
matdot_OBJECTS = \
"CMakeFiles/matdot.dir/matdot.cpp.o"

# External object files for target matdot
matdot_EXTERNAL_OBJECTS =

benchmark/matdot: benchmark/CMakeFiles/matdot.dir/matdot.cpp.o
benchmark/matdot: benchmark/CMakeFiles/matdot.dir/build.make
benchmark/matdot: benchmark/CMakeFiles/matdot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ljr/Desktop/SKT/dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matdot"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matdot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/matdot.dir/build: benchmark/matdot
.PHONY : benchmark/CMakeFiles/matdot.dir/build

benchmark/CMakeFiles/matdot.dir/clean:
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/matdot.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/matdot.dir/clean

benchmark/CMakeFiles/matdot.dir/depend:
	cd /home/ljr/Desktop/SKT/dfcpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ljr/Desktop/SKT/dfcpp /home/ljr/Desktop/SKT/dfcpp/benchmark /home/ljr/Desktop/SKT/dfcpp/build /home/ljr/Desktop/SKT/dfcpp/build/benchmark /home/ljr/Desktop/SKT/dfcpp/build/benchmark/CMakeFiles/matdot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark/CMakeFiles/matdot.dir/depend

