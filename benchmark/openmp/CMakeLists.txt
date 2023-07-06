list(APPEND BENCHMARKOMP
    omp_kmean
)
find_package(OpenMP REQUIRED)

foreach(app IN LISTS BENCHMARKOMP)
    add_executable(${app} ${app}.cpp)
    target_link_libraries(${app} OpenMP::OpenMP_CXX)
endforeach()