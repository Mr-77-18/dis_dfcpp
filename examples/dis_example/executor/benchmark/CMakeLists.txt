list(APPEND EXAMPLES
    create_linear
    create_binary_tree
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




