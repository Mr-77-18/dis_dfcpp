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
CMAKE_BINARY_DIR = /home/lsh/dfcpp/grpc_dfcpp

# Include any dependencies generated for this target.
include benchmark/CMakeFiles/kmean.dir/depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/kmean.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/kmean.dir/flags.make

benchmark/CMakeFiles/kmean.dir/kmean.cpp.o: benchmark/CMakeFiles/kmean.dir/flags.make
benchmark/CMakeFiles/kmean.dir/kmean.cpp.o: ../benchmark/kmean.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/grpc_dfcpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/kmean.dir/kmean.cpp.o"
	cd /home/lsh/dfcpp/grpc_dfcpp/benchmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kmean.dir/kmean.cpp.o -c /home/lsh/dfcpp/benchmark/kmean.cpp

benchmark/CMakeFiles/kmean.dir/kmean.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kmean.dir/kmean.cpp.i"
	cd /home/lsh/dfcpp/grpc_dfcpp/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/benchmark/kmean.cpp > CMakeFiles/kmean.dir/kmean.cpp.i

benchmark/CMakeFiles/kmean.dir/kmean.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kmean.dir/kmean.cpp.s"
	cd /home/lsh/dfcpp/grpc_dfcpp/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/benchmark/kmean.cpp -o CMakeFiles/kmean.dir/kmean.cpp.s

# Object files for target kmean
kmean_OBJECTS = \
"CMakeFiles/kmean.dir/kmean.cpp.o"

# External object files for target kmean
kmean_EXTERNAL_OBJECTS =

benchmark/kmean: benchmark/CMakeFiles/kmean.dir/kmean.cpp.o
benchmark/kmean: benchmark/CMakeFiles/kmean.dir/build.make
benchmark/kmean: benchmark/CMakeFiles/kmean.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/grpc_dfcpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kmean"
	cd /home/lsh/dfcpp/grpc_dfcpp/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kmean.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/kmean.dir/build: benchmark/kmean

.PHONY : benchmark/CMakeFiles/kmean.dir/build

benchmark/CMakeFiles/kmean.dir/clean:
	cd /home/lsh/dfcpp/grpc_dfcpp/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/kmean.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/kmean.dir/clean

benchmark/CMakeFiles/kmean.dir/depend:
	cd /home/lsh/dfcpp/grpc_dfcpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp /home/lsh/dfcpp/benchmark /home/lsh/dfcpp/grpc_dfcpp /home/lsh/dfcpp/grpc_dfcpp/benchmark /home/lsh/dfcpp/grpc_dfcpp/benchmark/CMakeFiles/kmean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark/CMakeFiles/kmean.dir/depend

