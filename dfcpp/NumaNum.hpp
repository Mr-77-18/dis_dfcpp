//
// Created by ljr on 12/4/22.
//

#ifndef DFCPP_NUMANUM_HPP
#define DFCPP_NUMANUM_HPP

#ifdef DFCPP_NUMA
#include <numa.h>
#endif

namespace DFCPP{
#ifdef DFCPP_NUMA
    const int NUMANUM = numa_max_node() + 1;
#else
    constexpr int NUMANUM = 1;
#endif

};


#endif //DFCPP_NUMANUM_HPP
