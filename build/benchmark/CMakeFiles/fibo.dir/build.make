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
include benchmark/CMakeFiles/fibo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include benchmark/CMakeFiles/fibo.dir/compiler_depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/fibo.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/fibo.dir/flags.make

benchmark/CMakeFiles/fibo.dir/fibo.cpp.o: benchmark/CMakeFiles/fibo.dir/flags.make
benchmark/CMakeFiles/fibo.dir/fibo.cpp.o: ../benchmark/fibo.cpp
benchmark/CMakeFiles/fibo.dir/fibo.cpp.o: benchmark/CMakeFiles/fibo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljr/Desktop/SKT/dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/fibo.dir/fibo.cpp.o"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT benchmark/CMakeFiles/fibo.dir/fibo.cpp.o -MF CMakeFiles/fibo.dir/fibo.cpp.o.d -o CMakeFiles/fibo.dir/fibo.cpp.o -c /home/ljr/Desktop/SKT/dfcpp/benchmark/fibo.cpp

benchmark/CMakeFiles/fibo.dir/fibo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fibo.dir/fibo.cpp.i"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljr/Desktop/SKT/dfcpp/benchmark/fibo.cpp > CMakeFiles/fibo.dir/fibo.cpp.i

benchmark/CMakeFiles/fibo.dir/fibo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fibo.dir/fibo.cpp.s"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && /usr/bin/g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljr/Desktop/SKT/dfcpp/benchmark/fibo.cpp -o CMakeFiles/fibo.dir/fibo.cpp.s

# Object files for target fibo
fibo_OBJECTS = \
"CMakeFiles/fibo.dir/fibo.cpp.o"

# External object files for target fibo
fibo_EXTERNAL_OBJECTS =

benchmark/fibo: benchmark/CMakeFiles/fibo.dir/fibo.cpp.o
benchmark/fibo: benchmark/CMakeFiles/fibo.dir/build.make
benchmark/fibo: benchmark/CMakeFiles/fibo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ljr/Desktop/SKT/dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fibo"
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fibo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/fibo.dir/build: benchmark/fibo
.PHONY : benchmark/CMakeFiles/fibo.dir/build

benchmark/CMakeFiles/fibo.dir/clean:
	cd /home/ljr/Desktop/SKT/dfcpp/build/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/fibo.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/fibo.dir/clean

benchmark/CMakeFiles/fibo.dir/depend:
	cd /home/ljr/Desktop/SKT/dfcpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ljr/Desktop/SKT/dfcpp /home/ljr/Desktop/SKT/dfcpp/benchmark /home/ljr/Desktop/SKT/dfcpp/build /home/ljr/Desktop/SKT/dfcpp/build/benchmark /home/ljr/Desktop/SKT/dfcpp/build/benchmark/CMakeFiles/fibo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark/CMakeFiles/fibo.dir/depend

