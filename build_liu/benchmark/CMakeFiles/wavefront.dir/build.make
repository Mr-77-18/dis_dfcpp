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
include benchmark/CMakeFiles/wavefront.dir/depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/wavefront.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/wavefront.dir/flags.make

benchmark/CMakeFiles/wavefront.dir/wavefront.cpp.o: benchmark/CMakeFiles/wavefront.dir/flags.make
benchmark/CMakeFiles/wavefront.dir/wavefront.cpp.o: ../benchmark/wavefront.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/build_liu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/wavefront.dir/wavefront.cpp.o"
	cd /home/lsh/dfcpp/build_liu/benchmark && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wavefront.dir/wavefront.cpp.o -c /home/lsh/dfcpp/benchmark/wavefront.cpp

benchmark/CMakeFiles/wavefront.dir/wavefront.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wavefront.dir/wavefront.cpp.i"
	cd /home/lsh/dfcpp/build_liu/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/benchmark/wavefront.cpp > CMakeFiles/wavefront.dir/wavefront.cpp.i

benchmark/CMakeFiles/wavefront.dir/wavefront.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wavefront.dir/wavefront.cpp.s"
	cd /home/lsh/dfcpp/build_liu/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/benchmark/wavefront.cpp -o CMakeFiles/wavefront.dir/wavefront.cpp.s

# Object files for target wavefront
wavefront_OBJECTS = \
"CMakeFiles/wavefront.dir/wavefront.cpp.o"

# External object files for target wavefront
wavefront_EXTERNAL_OBJECTS =

benchmark/wavefront: benchmark/CMakeFiles/wavefront.dir/wavefront.cpp.o
benchmark/wavefront: benchmark/CMakeFiles/wavefront.dir/build.make
benchmark/wavefront: benchmark/CMakeFiles/wavefront.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/build_liu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wavefront"
	cd /home/lsh/dfcpp/build_liu/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wavefront.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/wavefront.dir/build: benchmark/wavefront

.PHONY : benchmark/CMakeFiles/wavefront.dir/build

benchmark/CMakeFiles/wavefront.dir/clean:
	cd /home/lsh/dfcpp/build_liu/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/wavefront.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/wavefront.dir/clean

benchmark/CMakeFiles/wavefront.dir/depend:
	cd /home/lsh/dfcpp/build_liu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp /home/lsh/dfcpp/benchmark /home/lsh/dfcpp/build_liu /home/lsh/dfcpp/build_liu/benchmark /home/lsh/dfcpp/build_liu/benchmark/CMakeFiles/wavefront.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark/CMakeFiles/wavefront.dir/depend

