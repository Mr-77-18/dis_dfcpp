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

list(APPEND EXAMPLES
    main1
    main2
    main3
    main4
    main5
    main7
    main8
    fibonacci
    HoardTest
    loopback
    main_grpc_threemess
    main_grpc_threemess1
    main_grpc_threemess2
    main_grpc_threemess3
    main10
    executor_w_master
    executor_w_master1
)

include_directories(/home/lsh/dfcpp/)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(Threads REQUIRED)
foreach(example IN LISTS EXAMPLES)
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} 
        need_utils
        absl::flags
        absl::flags_parse
        ${_REFLECTION}
        ${_DRPC_DRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
        Threads::Threads 
        numa)
    
endforeach(example IN LISTS EXAMPLES)




