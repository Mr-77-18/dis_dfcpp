list(APPEND EXAMPLES
    master
    master_test_empty_parti
    valjson
    linear_master
    master_nojson
)

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
        numa
        -lm
        /home/lsh/dfcpp/dagP/lib/libdagp.a
        )
    
endforeach(example IN LISTS EXAMPLES)




