//
// Created by Gboom on 2022/10/19.
//

#ifndef DFCPP_TYPES_HPP
#define DFCPP_TYPES_HPP

#include "DFV.hpp"
#include <type_traits>
#include <tuple>


namespace DFCPP{

    class DynamicTask;

    // 空类型，主要用于后续判断T的类型
    template<typename ... T>
    class MetaArg{};

    // T 是否是DFV类型
    template<typename T>
    constexpr bool is_DFV = std::is_base_of_v<DFVAbstract, T>;

    // 是否有一个或多个Args是DFV类型
    template<typename ...Args>
    constexpr bool is_any_DFV = (is_DFV<Args> || ...);  // 表达式折叠

    //-----------------------------static task-----------------------------

    // 既无输入也无输出的静态任务调用类型
    template<typename C>
    constexpr bool is_special_static =
            std::is_invocable_r_v<void, C> &&
            !std::is_invocable_r_v<size_t, C>;

    // 判断是否是sink静态任务：只有输入没有输出
    template<typename C, typename ... ArgIns>
    constexpr bool is_sink_static =
            !is_any_DFV<ArgIns...> &&
            std::is_invocable_r_v<void, C, const ArgIns&...> &&
            !std::is_invocable_r_v<size_t, C, const ArgIns&...>;

    // 判断是否是普通的静态任务：一定包含输出
    template<typename C, typename ... ArgIns, typename ... ArgOuts>
    constexpr bool is_normal_static(MetaArg<ArgIns...>, MetaArg<ArgOuts...>) {
        return !is_any_DFV<ArgIns..., ArgOuts...> &&
                std::is_invocable_r_v<void, C, const ArgIns&..., DFV<ArgOuts>...> &&
                !std::is_invocable_r_v<int, C, const ArgIns&..., DFV<ArgOuts>...>;
    }

    // 此方法无法区分ArgIns和ArgOuts
    // template<typename C, typename ... ArgIns, typename ... ArgOuts>
    // constexpr bool is_normal_static =
    //         !is_any_DFV<ArgIns..., ArgOuts...> &&
    //         std::is_invocable_r_v<void, C, ArgIns&..., std::tuple<DFV<ArgOuts>...>> &&
    //         !std::is_invocable_r_v<size_t, C, ArgIns&..., std::tuple<DFV<ArgOuts>...>>;


    // -----------------------dynamic task----------------------------------

    // 既无输入也无输出的动态任务调用类型
    template<typename C>
    constexpr bool is_special_dynamic =
            std::is_invocable_r_v<void, C, DynamicTask&> &&
            !std::is_invocable_r_v<size_t, C, DynamicTask&>;

    // 判断是否是sink动态任务：只有输入没有输出
    template<typename C, typename ... ArgIns>
    constexpr bool is_sink_dynamic =
            !is_any_DFV<ArgIns...> &&
            std::is_invocable_r_v<void, C, DynamicTask&, const ArgIns&...> &&
            !std::is_invocable_r_v<size_t, C, DynamicTask&, const ArgIns&...>;

    // 判断是否是普通的动态任务：一定包含输出
    template<typename C, typename ... ArgIns, typename ... ArgOuts>
    constexpr bool is_normal_dynamic (MetaArg<ArgIns...>, MetaArg<ArgOuts...>) {
        return !is_any_DFV<ArgIns..., ArgOuts...> &&
                std::is_invocable_r_v<void, C, DynamicTask&, const ArgIns&..., DFV<ArgOuts>...> &&
                !std::is_invocable_r_v<size_t, C, DynamicTask&, const ArgIns&..., DFV<ArgOuts>...>;
    }

    // 判断是否是使用tuple<DFV>的sink动态任务，方便子任务引用动态任务的输入
    template<typename C, typename ...ArgIns>
    constexpr bool is_sink_dynamic_with_tuple =
         !is_any_DFV<ArgIns...> &&
                std::is_invocable_r_v<void, C, DynamicTask&, std::tuple<DFV<ArgIns>...>> &&
                !std::is_invocable_r_v<size_t, C, DynamicTask&, std::tuple<DFV<ArgIns>...>>;

    // 判断是否是使用tuple<DFV>的普通动态任务，方便子任务引用动态任务的输入
    template<typename C, typename ...ArgIns, typename ...ArgOuts>
    constexpr bool is_normal_dynamic_with_tuple(MetaArg<ArgIns...>, MetaArg<ArgOuts...>) {
        return !is_any_DFV<ArgIns...,ArgOuts...> &&
                std::is_invocable_r_v<void, C, DynamicTask&, std::tuple<DFV<ArgIns>...>, DFV<ArgOuts>...> &&
                !std::is_invocable_r_v<size_t, C, DynamicTask&, std::tuple<DFV<ArgIns>...>, DFV<ArgOuts>...>;
    }

    // -----------------------condition task----------------------------------

    // 既无输入也无输出的条件任务调用类型
    template<typename C>
    constexpr bool is_special_condition = std::is_invocable_r_v<size_t, C>;

    // 判断是否是sink条件任务：只有输入没有输出
    template<typename C, typename ... ArgIns>
    constexpr bool is_sink_condition =
            !is_any_DFV<ArgIns...> &&
            std::is_invocable_r_v<size_t, C, ArgIns...>;

    // 判断是否是普通的条件任务：一定包含输出F
    template<typename C, typename ... ArgIns, typename ... ArgOuts>
    constexpr bool is_normal_condition(MetaArg<ArgIns...>, MetaArg<ArgOuts...>) {
        return !is_any_DFV<ArgIns..., ArgOuts...> &&
               std::is_invocable_r_v<size_t, C, const ArgIns&..., DFV<ArgOuts>...>;
    }

}


#endif //DFCPP_TYPES_HPP
