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
CMAKE_SOURCE_DIR = /home/lsh/dfcpp/grpc_dfcpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lsh/dfcpp/grpc_dfcpp/build

# Include any dependencies generated for this target.
include CMakeFiles/master_try1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/master_try1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/master_try1.dir/flags.make

CMakeFiles/master_try1.dir/master_try1.cc.o: CMakeFiles/master_try1.dir/flags.make
CMakeFiles/master_try1.dir/master_try1.cc.o: ../master_try1.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/grpc_dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/master_try1.dir/master_try1.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/master_try1.dir/master_try1.cc.o -c /home/lsh/dfcpp/grpc_dfcpp/master_try1.cc

CMakeFiles/master_try1.dir/master_try1.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/master_try1.dir/master_try1.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/grpc_dfcpp/master_try1.cc > CMakeFiles/master_try1.dir/master_try1.cc.i

CMakeFiles/master_try1.dir/master_try1.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/master_try1.dir/master_try1.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/grpc_dfcpp/master_try1.cc -o CMakeFiles/master_try1.dir/master_try1.cc.s

# Object files for target master_try1
master_try1_OBJECTS = \
"CMakeFiles/master_try1.dir/master_try1.cc.o"

# External object files for target master_try1
master_try1_EXTERNAL_OBJECTS =

master_try1: CMakeFiles/master_try1.dir/master_try1.cc.o
master_try1: CMakeFiles/master_try1.dir/build.make
master_try1: libneed_utils.a
master_try1: /home/lsh/.local/lib/libabsl_flags.a
master_try1: /home/lsh/.local/lib/libabsl_flags_parse.a
master_try1: /home/lsh/.local/lib/libgrpc++_reflection.a
master_try1: /home/lsh/.local/lib/libgrpc++.a
master_try1: /home/lsh/.local/lib/libprotobuf.a
master_try1: /home/lsh/dfcpp/dagP/lib/libdagp.a
master_try1: /home/lsh/.local/lib/libgrpc.a
master_try1: /home/lsh/.local/lib/libcares.a
master_try1: /home/lsh/.local/lib/libaddress_sorting.a
master_try1: /home/lsh/.local/lib/libre2.a
master_try1: /home/lsh/.local/lib/libupb.a
master_try1: /home/lsh/.local/lib/libgpr.a
master_try1: /home/lsh/.local/lib/libz.a
master_try1: /home/lsh/.local/lib/libabsl_random_distributions.a
master_try1: /home/lsh/.local/lib/libabsl_random_seed_sequences.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_pool_urbg.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_randen.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_randen_hwaes.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_randen_slow.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_platform.a
master_try1: /home/lsh/.local/lib/libabsl_random_internal_seed_material.a
master_try1: /home/lsh/.local/lib/libabsl_random_seed_gen_exception.a
master_try1: /home/lsh/.local/lib/libssl.a
master_try1: /home/lsh/.local/lib/libcrypto.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_check_op.a
master_try1: /home/lsh/.local/lib/libabsl_leak_check.a
master_try1: /home/lsh/.local/lib/libabsl_die_if_null.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_conditions.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_message.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_nullguard.a
master_try1: /home/lsh/.local/lib/libabsl_examine_stack.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_format.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_proto.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_log_sink_set.a
master_try1: /home/lsh/.local/lib/libabsl_log_sink.a
master_try1: /home/lsh/.local/lib/libabsl_log_entry.a
master_try1: /home/lsh/.local/lib/libabsl_log_initialize.a
master_try1: /home/lsh/.local/lib/libabsl_log_globals.a
master_try1: /home/lsh/.local/lib/libabsl_log_internal_globals.a
master_try1: /home/lsh/.local/lib/libabsl_statusor.a
master_try1: /home/lsh/.local/lib/libabsl_status.a
master_try1: /home/lsh/.local/lib/libabsl_strerror.a
master_try1: /home/lsh/.local/lib/libutf8_validity.a
master_try1: /home/lsh/.local/lib/libabsl_flags_usage.a
master_try1: /home/lsh/.local/lib/libabsl_flags_usage_internal.a
master_try1: /home/lsh/.local/lib/libabsl_flags.a
master_try1: /home/lsh/.local/lib/libabsl_flags_internal.a
master_try1: /home/lsh/.local/lib/libabsl_flags_marshalling.a
master_try1: /home/lsh/.local/lib/libabsl_str_format_internal.a
master_try1: /home/lsh/.local/lib/libabsl_flags_reflection.a
master_try1: /home/lsh/.local/lib/libabsl_flags_config.a
master_try1: /home/lsh/.local/lib/libabsl_flags_private_handle_accessor.a
master_try1: /home/lsh/.local/lib/libabsl_flags_commandlineflag.a
master_try1: /home/lsh/.local/lib/libabsl_flags_commandlineflag_internal.a
master_try1: /home/lsh/.local/lib/libabsl_flags_program_name.a
master_try1: /home/lsh/.local/lib/libabsl_cord.a
master_try1: /home/lsh/.local/lib/libabsl_cordz_info.a
master_try1: /home/lsh/.local/lib/libabsl_cord_internal.a
master_try1: /home/lsh/.local/lib/libabsl_cordz_functions.a
master_try1: /home/lsh/.local/lib/libabsl_cordz_handle.a
master_try1: /home/lsh/.local/lib/libabsl_crc_cord_state.a
master_try1: /home/lsh/.local/lib/libabsl_crc32c.a
master_try1: /home/lsh/.local/lib/libabsl_crc_internal.a
master_try1: /home/lsh/.local/lib/libabsl_crc_cpu_detect.a
master_try1: /home/lsh/.local/lib/libabsl_hash.a
master_try1: /home/lsh/.local/lib/libabsl_bad_variant_access.a
master_try1: /home/lsh/.local/lib/libabsl_city.a
master_try1: /home/lsh/.local/lib/libabsl_low_level_hash.a
master_try1: /home/lsh/.local/lib/libabsl_raw_hash_set.a
master_try1: /home/lsh/.local/lib/libabsl_bad_optional_access.a
master_try1: /home/lsh/.local/lib/libabsl_hashtablez_sampler.a
master_try1: /home/lsh/.local/lib/libabsl_exponential_biased.a
master_try1: /home/lsh/.local/lib/libabsl_synchronization.a
master_try1: /home/lsh/.local/lib/libabsl_graphcycles_internal.a
master_try1: /home/lsh/.local/lib/libabsl_time.a
master_try1: /home/lsh/.local/lib/libabsl_civil_time.a
master_try1: /home/lsh/.local/lib/libabsl_time_zone.a
master_try1: /home/lsh/.local/lib/libabsl_stacktrace.a
master_try1: /home/lsh/.local/lib/libabsl_symbolize.a
master_try1: /home/lsh/.local/lib/libabsl_strings.a
master_try1: /home/lsh/.local/lib/libabsl_strings_internal.a
master_try1: /home/lsh/.local/lib/libabsl_int128.a
master_try1: /home/lsh/.local/lib/libabsl_throw_delegate.a
master_try1: /home/lsh/.local/lib/libabsl_malloc_internal.a
master_try1: /home/lsh/.local/lib/libabsl_debugging_internal.a
master_try1: /home/lsh/.local/lib/libabsl_demangle_internal.a
master_try1: /home/lsh/.local/lib/libabsl_base.a
master_try1: /home/lsh/.local/lib/libabsl_raw_logging_internal.a
master_try1: /home/lsh/.local/lib/libabsl_log_severity.a
master_try1: /home/lsh/.local/lib/libabsl_spinlock_wait.a
master_try1: CMakeFiles/master_try1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/grpc_dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable master_try1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/master_try1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/master_try1.dir/build: master_try1

.PHONY : CMakeFiles/master_try1.dir/build

CMakeFiles/master_try1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/master_try1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/master_try1.dir/clean

CMakeFiles/master_try1.dir/depend:
	cd /home/lsh/dfcpp/grpc_dfcpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp/grpc_dfcpp /home/lsh/dfcpp/grpc_dfcpp /home/lsh/dfcpp/grpc_dfcpp/build /home/lsh/dfcpp/grpc_dfcpp/build /home/lsh/dfcpp/grpc_dfcpp/build/CMakeFiles/master_try1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/master_try1.dir/depend

