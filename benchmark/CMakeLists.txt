list(APPEND BENCHMARK
        fibo
        wavefront
        matdot
        linear
        matdot_random
        binary_tree
        graph
        kmean
        )

find_package(Threads REQUIRED)
foreach(app IN LISTS BENCHMARK)
    add_executable(${app} ${app}.cpp)
    target_link_libraries(${app} Threads::Threads numa)

endforeach(app IN LISTS EXAMPLES)
add_executable(stl_kmean stl_kmean.cpp)
target_link_libraries(stl_kmean Threads::Threads)
add_subdirectory(./openmp)
add_subdirectory(./tbb)



