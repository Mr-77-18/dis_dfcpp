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
include CMakeFiles/send_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/send_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/send_server.dir/flags.make

CMakeFiles/send_server.dir/send_server.cc.o: CMakeFiles/send_server.dir/flags.make
CMakeFiles/send_server.dir/send_server.cc.o: ../send_server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lsh/dfcpp/grpc_dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/send_server.dir/send_server.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/send_server.dir/send_server.cc.o -c /home/lsh/dfcpp/grpc_dfcpp/send_server.cc

CMakeFiles/send_server.dir/send_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/send_server.dir/send_server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lsh/dfcpp/grpc_dfcpp/send_server.cc > CMakeFiles/send_server.dir/send_server.cc.i

CMakeFiles/send_server.dir/send_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/send_server.dir/send_server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lsh/dfcpp/grpc_dfcpp/send_server.cc -o CMakeFiles/send_server.dir/send_server.cc.s

# Object files for target send_server
send_server_OBJECTS = \
"CMakeFiles/send_server.dir/send_server.cc.o"

# External object files for target send_server
send_server_EXTERNAL_OBJECTS =

send_server: CMakeFiles/send_server.dir/send_server.cc.o
send_server: CMakeFiles/send_server.dir/build.make
send_server: libneed_utils.a
send_server: /home/lsh/.local/lib/libabsl_flags.a
send_server: /home/lsh/.local/lib/libabsl_flags_parse.a
send_server: /home/lsh/.local/lib/libgrpc++_reflection.a
send_server: /home/lsh/.local/lib/libgrpc++.a
send_server: /home/lsh/.local/lib/libprotobuf.a
send_server: /home/lsh/.local/lib/libgrpc.a
send_server: /home/lsh/.local/lib/libcares.a
send_server: /home/lsh/.local/lib/libaddress_sorting.a
send_server: /home/lsh/.local/lib/libre2.a
send_server: /home/lsh/.local/lib/libupb.a
send_server: /home/lsh/.local/lib/libgpr.a
send_server: /home/lsh/.local/lib/libz.a
send_server: /home/lsh/.local/lib/libabsl_random_distributions.a
send_server: /home/lsh/.local/lib/libabsl_random_seed_sequences.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_pool_urbg.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_randen.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_randen_hwaes.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_randen_slow.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_platform.a
send_server: /home/lsh/.local/lib/libabsl_random_internal_seed_material.a
send_server: /home/lsh/.local/lib/libabsl_random_seed_gen_exception.a
send_server: /home/lsh/.local/lib/libssl.a
send_server: /home/lsh/.local/lib/libcrypto.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_check_op.a
send_server: /home/lsh/.local/lib/libabsl_leak_check.a
send_server: /home/lsh/.local/lib/libabsl_die_if_null.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_conditions.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_message.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_nullguard.a
send_server: /home/lsh/.local/lib/libabsl_examine_stack.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_format.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_proto.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_log_sink_set.a
send_server: /home/lsh/.local/lib/libabsl_log_sink.a
send_server: /home/lsh/.local/lib/libabsl_log_entry.a
send_server: /home/lsh/.local/lib/libabsl_log_initialize.a
send_server: /home/lsh/.local/lib/libabsl_log_globals.a
send_server: /home/lsh/.local/lib/libabsl_log_internal_globals.a
send_server: /home/lsh/.local/lib/libabsl_statusor.a
send_server: /home/lsh/.local/lib/libabsl_status.a
send_server: /home/lsh/.local/lib/libabsl_strerror.a
send_server: /home/lsh/.local/lib/libutf8_validity.a
send_server: /home/lsh/.local/lib/libabsl_flags_usage.a
send_server: /home/lsh/.local/lib/libabsl_flags_usage_internal.a
send_server: /home/lsh/.local/lib/libabsl_flags.a
send_server: /home/lsh/.local/lib/libabsl_flags_internal.a
send_server: /home/lsh/.local/lib/libabsl_flags_marshalling.a
send_server: /home/lsh/.local/lib/libabsl_str_format_internal.a
send_server: /home/lsh/.local/lib/libabsl_flags_reflection.a
send_server: /home/lsh/.local/lib/libabsl_flags_config.a
send_server: /home/lsh/.local/lib/libabsl_flags_private_handle_accessor.a
send_server: /home/lsh/.local/lib/libabsl_flags_commandlineflag.a
send_server: /home/lsh/.local/lib/libabsl_flags_commandlineflag_internal.a
send_server: /home/lsh/.local/lib/libabsl_flags_program_name.a
send_server: /home/lsh/.local/lib/libabsl_cord.a
send_server: /home/lsh/.local/lib/libabsl_cordz_info.a
send_server: /home/lsh/.local/lib/libabsl_cord_internal.a
send_server: /home/lsh/.local/lib/libabsl_cordz_functions.a
send_server: /home/lsh/.local/lib/libabsl_cordz_handle.a
send_server: /home/lsh/.local/lib/libabsl_crc_cord_state.a
send_server: /home/lsh/.local/lib/libabsl_crc32c.a
send_server: /home/lsh/.local/lib/libabsl_crc_internal.a
send_server: /home/lsh/.local/lib/libabsl_crc_cpu_detect.a
send_server: /home/lsh/.local/lib/libabsl_hash.a
send_server: /home/lsh/.local/lib/libabsl_bad_variant_access.a
send_server: /home/lsh/.local/lib/libabsl_city.a
send_server: /home/lsh/.local/lib/libabsl_low_level_hash.a
send_server: /home/lsh/.local/lib/libabsl_raw_hash_set.a
send_server: /home/lsh/.local/lib/libabsl_bad_optional_access.a
send_server: /home/lsh/.local/lib/libabsl_hashtablez_sampler.a
send_server: /home/lsh/.local/lib/libabsl_exponential_biased.a
send_server: /home/lsh/.local/lib/libabsl_synchronization.a
send_server: /home/lsh/.local/lib/libabsl_graphcycles_internal.a
send_server: /home/lsh/.local/lib/libabsl_time.a
send_server: /home/lsh/.local/lib/libabsl_civil_time.a
send_server: /home/lsh/.local/lib/libabsl_time_zone.a
send_server: /home/lsh/.local/lib/libabsl_stacktrace.a
send_server: /home/lsh/.local/lib/libabsl_symbolize.a
send_server: /home/lsh/.local/lib/libabsl_strings.a
send_server: /home/lsh/.local/lib/libabsl_strings_internal.a
send_server: /home/lsh/.local/lib/libabsl_int128.a
send_server: /home/lsh/.local/lib/libabsl_throw_delegate.a
send_server: /home/lsh/.local/lib/libabsl_malloc_internal.a
send_server: /home/lsh/.local/lib/libabsl_debugging_internal.a
send_server: /home/lsh/.local/lib/libabsl_demangle_internal.a
send_server: /home/lsh/.local/lib/libabsl_base.a
send_server: /home/lsh/.local/lib/libabsl_raw_logging_internal.a
send_server: /home/lsh/.local/lib/libabsl_log_severity.a
send_server: /home/lsh/.local/lib/libabsl_spinlock_wait.a
send_server: CMakeFiles/send_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lsh/dfcpp/grpc_dfcpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable send_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/send_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/send_server.dir/build: send_server

.PHONY : CMakeFiles/send_server.dir/build

CMakeFiles/send_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/send_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/send_server.dir/clean

CMakeFiles/send_server.dir/depend:
	cd /home/lsh/dfcpp/grpc_dfcpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lsh/dfcpp/grpc_dfcpp /home/lsh/dfcpp/grpc_dfcpp /home/lsh/dfcpp/grpc_dfcpp/build /home/lsh/dfcpp/grpc_dfcpp/build /home/lsh/dfcpp/grpc_dfcpp/build/CMakeFiles/send_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/send_server.dir/depend

