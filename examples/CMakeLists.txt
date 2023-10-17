cmake_minimum_required(VERSION 3.16)

project(add CXX)

include(./common.cmake)

set(grpc_source_dir "/home/lsh/dfcpp/grpc_dfcpp/")

set(hw_proto_srcs "${grpc_source_dir}/commu.pb.cc")
set(hw_proto_hdrs "${grpc_source_dir}/commu.pb.h")
set(hw_grpc_srcs "${grpc_source_dir}/commu.grpc.pb.cc")
set(hw_grpc_hdrs "${grpc_source_dir}/commu.grpc.pb.h")

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

include_directories(
    /home/lsh/dfcpp/
    /home/lsh/dfcpp/grpc_dfcpp/
    /home/lsh/dfcpp/dagP/src/dfcpp_dagP_port
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(dis_example)
add_subdirectory(origin_example)
