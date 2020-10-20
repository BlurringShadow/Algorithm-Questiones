#pragma once
#include <concepts>
#include <ranges>
#include <string>

#include <fmt/format.h>

using std::string;
using namespace std::literals;

constexpr auto to_identical = []<typename T>(T&& value) { return std::forward<T>(value); };

template<typename T, typename Input, typename Output>
concept Converter = std::invocable<T, Input> && std::convertible_to<std::invoke_result_t<T, Input>, Output>;

template<
    typename... ParameterType,
    std::ranges::input_range InputRange,
    Converter<std::ranges::range_value_t<InputRange>, ParameterType...> InputConverter,
    std::invocable<ParameterType...> Func,
    Converter<std::invoke_result_t<Func, ParameterType...>, string> OutputConverter
>
static void test_run(
    const InputRange& input_data,
    Func func,
    InputConverter input_converter = to_identical,
    OutputConverter output_converter = to_identical,
    const std::string_view format_str = "{}\n"
)
{
    string output;
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
