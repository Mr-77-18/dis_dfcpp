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
CMAKE_SOURCE_DIR = /home/lsh/dfcpp/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lsh/dfcpp/examples/build

# Include any dependencies generated for this target.
include CMakeFiles/HoardTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HoardTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HoardTest.dir/flags.make

CMakeFiles/HoardTest.dir/HoardTest.cpp.o: CMakeFiles/HoardTest.dir/flags.make
CMakeFiles/HoardTest.dir/HoardTest.cpp.o: ../HoardTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HoardTest.dir/HoardTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HoardTest.dir/HoardTest.cpp.o -c /home/lsh/dfcpp/examples/HoardTest.cpp

CMakeFiles/HoardTest.dir/HoardTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HoardTest.dir/HoardTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/examples/HoardTest.cpp > CMakeFiles/HoardTest.dir/HoardTest.cpp.i

CMakeFiles/HoardTest.dir/HoardTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HoardTest.dir/HoardTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/examples/HoardTest.cpp -o CMakeFiles/HoardTest.dir/HoardTest.cpp.s

# Object files for target HoardTest
HoardTest_OBJECTS = \
"CMakeFiles/HoardTest.dir/HoardTest.cpp.o"

# External object files for target HoardTest
HoardTest_EXTERNAL_OBJECTS =

HoardTest: CMakeFiles/HoardTest.dir/HoardTest.cpp.o
HoardTest: CMakeFiles/HoardTest.dir/build.make
HoardTest: libneed_utils.a
HoardTest: /home/lsh/.local/lib/libabsl_flags.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_parse.a
HoardTest: /home/lsh/.local/lib/libgrpc++_reflection.a
HoardTest: /home/lsh/.local/lib/libprotobuf.a
HoardTest: /home/lsh/.local/lib/libgrpc++.a
HoardTest: /home/lsh/.local/lib/libprotobuf.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_check_op.a
HoardTest: /home/lsh/.local/lib/libabsl_leak_check.a
HoardTest: /home/lsh/.local/lib/libabsl_die_if_null.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_conditions.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_message.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_nullguard.a
HoardTest: /home/lsh/.local/lib/libabsl_examine_stack.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_format.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_proto.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_log_sink_set.a
HoardTest: /home/lsh/.local/lib/libabsl_log_sink.a
HoardTest: /home/lsh/.local/lib/libabsl_log_entry.a
HoardTest: /home/lsh/.local/lib/libabsl_log_initialize.a
HoardTest: /home/lsh/.local/lib/libabsl_log_globals.a
HoardTest: /home/lsh/.local/lib/libabsl_log_internal_globals.a
HoardTest: /home/lsh/.local/lib/libutf8_validity.a
HoardTest: /home/lsh/.local/lib/libgrpc.a
HoardTest: /home/lsh/.local/lib/libabsl_statusor.a
HoardTest: /home/lsh/.local/lib/libcares.a
HoardTest: /home/lsh/.local/lib/libaddress_sorting.a
HoardTest: /home/lsh/.local/lib/libre2.a
HoardTest: /home/lsh/.local/lib/libupb.a
HoardTest: /home/lsh/.local/lib/libgpr.a
HoardTest: /home/lsh/.local/lib/libz.a
HoardTest: /home/lsh/.local/lib/libabsl_status.a
HoardTest: /home/lsh/.local/lib/libabsl_strerror.a
HoardTest: /home/lsh/.local/lib/libabsl_random_distributions.a
HoardTest: /home/lsh/.local/lib/libabsl_random_seed_sequences.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_pool_urbg.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_randen.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_randen_hwaes.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_randen_slow.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_platform.a
HoardTest: /home/lsh/.local/lib/libabsl_random_internal_seed_material.a
HoardTest: /home/lsh/.local/lib/libabsl_random_seed_gen_exception.a
HoardTest: /home/lsh/.local/lib/libssl.a
HoardTest: /home/lsh/.local/lib/libcrypto.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_usage.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_usage_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_flags.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_marshalling.a
HoardTest: /home/lsh/.local/lib/libabsl_str_format_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_reflection.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_config.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_private_handle_accessor.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_commandlineflag.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_commandlineflag_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_flags_program_name.a
HoardTest: /home/lsh/.local/lib/libabsl_cord.a
HoardTest: /home/lsh/.local/lib/libabsl_cordz_info.a
HoardTest: /home/lsh/.local/lib/libabsl_cord_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_cordz_functions.a
HoardTest: /home/lsh/.local/lib/libabsl_cordz_handle.a
HoardTest: /home/lsh/.local/lib/libabsl_crc_cord_state.a
HoardTest: /home/lsh/.local/lib/libabsl_crc32c.a
HoardTest: /home/lsh/.local/lib/libabsl_crc_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_crc_cpu_detect.a
HoardTest: /home/lsh/.local/lib/libabsl_hash.a
HoardTest: /home/lsh/.local/lib/libabsl_bad_variant_access.a
HoardTest: /home/lsh/.local/lib/libabsl_city.a
HoardTest: /home/lsh/.local/lib/libabsl_low_level_hash.a
HoardTest: /home/lsh/.local/lib/libabsl_raw_hash_set.a
HoardTest: /home/lsh/.local/lib/libabsl_bad_optional_access.a
HoardTest: /home/lsh/.local/lib/libabsl_hashtablez_sampler.a
HoardTest: /home/lsh/.local/lib/libabsl_exponential_biased.a
HoardTest: /home/lsh/.local/lib/libabsl_synchronization.a
HoardTest: /home/lsh/.local/lib/libabsl_graphcycles_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_time.a
HoardTest: /home/lsh/.local/lib/libabsl_civil_time.a
HoardTest: /home/lsh/.local/lib/libabsl_time_zone.a
HoardTest: /home/lsh/.local/lib/libabsl_stacktrace.a
HoardTest: /home/lsh/.local/lib/libabsl_symbolize.a
HoardTest: /home/lsh/.local/lib/libabsl_strings.a
HoardTest: /home/lsh/.local/lib/libabsl_strings_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_int128.a
HoardTest: /home/lsh/.local/lib/libabsl_throw_delegate.a
HoardTest: /home/lsh/.local/lib/libabsl_malloc_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_debugging_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_demangle_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_base.a
HoardTest: /home/lsh/.local/lib/libabsl_raw_logging_internal.a
HoardTest: /home/lsh/.local/lib/libabsl_log_severity.a
HoardTest: /home/lsh/.local/lib/libabsl_spinlock_wait.a
HoardTest: CMakeFiles/HoardTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HoardTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HoardTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HoardTest.dir/build: HoardTest

.PHONY : CMakeFiles/HoardTest.dir/build

CMakeFiles/HoardTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HoardTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HoardTest.dir/clean

CMakeFiles/HoardTest.dir/depend:
	cd /home/lsh/dfcpp/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp/examples /home/lsh/dfcpp/examples /home/lsh/dfcpp/examples/build /home/lsh/dfcpp/examples/build /home/lsh/dfcpp/examples/build/CMakeFiles/HoardTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HoardTest.dir/depend
