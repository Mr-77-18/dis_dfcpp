# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/lsh/dfcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lsh/dfcpp/build_liu

# Include any dependencies generated for this target.
include benchmark/CMakeFiles/graph.dir/depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/graph.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/graph.dir/flags.make

benchmark/CMakeFiles/graph.dir/graph.cpp.o: benchmark/CMakeFiles/graph.dir/flags.make
benchmark/CMakeFiles/graph.dir/graph.cpp.o: ../benchmark/graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/build_liu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/graph.dir/graph.cpp.o"
	cd /home/lsh/dfcpp/build_liu/benchmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graph.dir/graph.cpp.o -c /home/lsh/dfcpp/benchmark/graph.cpp

benchmark/CMakeFiles/graph.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph.dir/graph.cpp.i"
	cd /home/lsh/dfcpp/build_liu/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/benchmark/graph.cpp > CMakeFiles/graph.dir/graph.cpp.i

benchmark/CMakeFiles/graph.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph.dir/graph.cpp.s"
	cd /home/lsh/dfcpp/build_liu/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/benchmark/graph.cpp -o CMakeFiles/graph.dir/graph.cpp.s

# Object files for target graph
graph_OBJECTS = \
"CMakeFiles/graph.dir/graph.cpp.o"

# External object files for target graph
graph_EXTERNAL_OBJECTS =

benchmark/graph: benchmark/CMakeFiles/graph.dir/graph.cpp.o
benchmark/graph: benchmark/CMakeFiles/graph.dir/build.make
benchmark/graph: benchmark/CMakeFiles/graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/build_liu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable graph"
	cd /home/lsh/dfcpp/build_liu/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/graph.dir/build: benchmark/graph

.PHONY : benchmark/CMakeFiles/graph.dir/build

benchmark/CMakeFiles/graph.dir/clean:
	cd /home/lsh/dfcpp/build_liu/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/graph.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/graph.dir/clean

benchmark/CMakeFiles/graph.dir/depend:
	cd /home/lsh/dfcpp/build_liu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp /home/lsh/dfcpp/benchmark /home/lsh/dfcpp/build_liu /home/lsh/dfcpp/build_liu/benchmark /home/lsh/dfcpp/build_liu/benchmark/CMakeFiles/graph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark/CMakeFiles/graph.dir/depend

