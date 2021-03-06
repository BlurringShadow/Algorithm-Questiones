﻿// Created by BlurringShadow at 2020-10-26-上午 10:09

#pragma once
#include <chrono>

#include <fmt/format.h>

#include "utils.h"

struct counter
{
    const std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    ~counter()
    {
        fmt::print("{}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count());
    }
};

template<typename T, typename Input, typename Output>
struct is_converter : std::bool_constant<
        std::is_invocable_v<T, Input> &&
        std::is_convertible_v<std::invoke_result_t<T, Input>, Output>
    > {};

template<typename T, typename Input, typename Output>
constexpr auto is_converter_v = is_converter<T, Input, Output>::value;

template<typename T, typename Input, typename Output>
concept Converter = std::invocable<T, Input> && std::convertible_to<std::invoke_result_t<T, Input>, Output>;

template<
    typename... ParameterType,
    std::ranges::input_range InputRange,
    Converter<std::ranges::range_value_t<InputRange>, ParameterType...> InputConverter,
    std::invocable<ParameterType...> Func,
    Converter<std::invoke_result_t<Func, ParameterType...>, std::string> OutputConverter
>
static void test_run(
    const InputRange& input_data,
    Func func,
    InputConverter input_converter = std::identity{},
    OutputConverter output_converter = std::identity{},
    const std::string_view format_str = "{}\n"
)
{
    std::string output;
    for(auto& input : input_data)
    {
        auto&& converted = input_converter(input);
        std::invoke_result_t<Func, ParameterType...> r;
        if constexpr(sizeof...(ParameterType) > 1) r = std::apply(func, std::move(converted));
        else r = func(std::move(converted));
        output += fmt::format(format_str, output_converter(std::move(r)));
    }
    fmt::print("{}\n", output);
}
