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
include benchmark/tbb/CMakeFiles/tbb_matdot.dir/depend.make

# Include the progress variables for this target.
include benchmark/tbb/CMakeFiles/tbb_matdot.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/tbb/CMakeFiles/tbb_matdot.dir/flags.make

benchmark/tbb/CMakeFiles/tbb_matdot.dir/matdot.cpp.o: benchmark/tbb/CMakeFiles/tbb_matdot.dir/flags.make
benchmark/tbb/CMakeFiles/tbb_matdot.dir/matdot.cpp.o: ../benchmark/tbb/matdot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/build_liu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/tbb/CMakeFiles/tbb_matdot.dir/matdot.cpp.o"
	cd /home/lsh/dfcpp/build_liu/benchmark/tbb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tbb_matdot.dir/matdot.cpp.o -c /home/lsh/dfcpp/benchmark/tbb/matdot.cpp

benchmark/tbb/CMakeFiles/tbb_matdot.dir/matdot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tbb_matdot.dir/matdot.cpp.i"
	cd /home/lsh/dfcpp/build_liu/benchmark/tbb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/benchmark/tbb/matdot.cpp > CMakeFiles/tbb_matdot.dir/matdot.cpp.i

benchmark/tbb/CMakeFiles/tbb_matdot.dir/matdot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tbb_matdot.dir/matdot.cpp.s"
	cd /home/lsh/dfcpp/build_liu/benchmark/tbb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/benchmark/tbb/matdot.cpp -o CMakeFiles/tbb_matdot.dir/matdot.cpp.s

# Object files for target tbb_matdot
tbb_matdot_OBJECTS = \
"CMakeFiles/tbb_matdot.dir/matdot.cpp.o"

# External object files for target tbb_matdot
tbb_matdot_EXTERNAL_OBJECTS =

benchmark/tbb/tbb_matdot: benchmark/tbb/CMakeFiles/tbb_matdot.dir/matdot.cpp.o
benchmark/tbb/tbb_matdot: benchmark/tbb/CMakeFiles/tbb_matdot.dir/build.make
benchmark/tbb/tbb_matdot: benchmark/tbb/CMakeFiles/tbb_matdot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/build_liu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tbb_matdot"
	cd /home/lsh/dfcpp/build_liu/benchmark/tbb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tbb_matdot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/tbb/CMakeFiles/tbb_matdot.dir/build: benchmark/tbb/tbb_matdot

.PHONY : benchmark/tbb/CMakeFiles/tbb_matdot.dir/build

benchmark/tbb/CMakeFiles/tbb_matdot.dir/clean:
	cd /home/lsh/dfcpp/build_liu/benchmark/tbb && $(CMAKE_COMMAND) -P CMakeFiles/tbb_matdot.dir/cmake_clean.cmake
.PHONY : benchmark/tbb/CMakeFiles/tbb_matdot.dir/clean

benchmark/tbb/CMakeFiles/tbb_matdot.dir/depend:
	cd /home/lsh/dfcpp/build_liu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp /home/lsh/dfcpp/benchmark/tbb /home/lsh/dfcpp/build_liu /home/lsh/dfcpp/build_liu/benchmark/tbb /home/lsh/dfcpp/build_liu/benchmark/tbb/CMakeFiles/tbb_matdot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark/tbb/CMakeFiles/tbb_matdot.dir/depend

