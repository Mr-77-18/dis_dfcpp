cmake_minimum_required(VERSION 3.8)                                             

project(add CXX)

include(./common.cmake)

set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/../commu.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../commu.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/../commu.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../commu.grpc.pb.h")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(need_utils
  ${hw_proto_srcs}
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_hdrs})

target_link_libraries(need_utils
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

foreach(_target
    schedule)
  add_executable(${_target} "${_target}.cc")
  include_directories(
    ../dfcpp/
    ../dagP/src/dfcpp_dagP_port
    )
  target_link_libraries(${_target}
    need_utils
    absl::flags
    absl::flags_parse
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    -lm
    /home/lsh/dfcpp/dagP/lib/libdagp.a
    )

endforeach()

