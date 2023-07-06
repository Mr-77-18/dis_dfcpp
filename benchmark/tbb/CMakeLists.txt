list(APPEND BENCHMARKTBB
    linearchain
    wavefront
    matdot
    binary_tree
    matdot_random
    graph
    kmean
)

foreach(app IN LISTS BENCHMARKTBB)
    add_executable(tbb_${app} ${app}.cpp)
    target_link_libraries(tbb_${app} tbb)
endforeach()