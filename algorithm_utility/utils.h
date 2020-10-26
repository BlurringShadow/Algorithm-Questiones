// Created by BlurringShadow at 2020-10-26-上午 10:09

#pragma once
#ifndef _DEBUG
#define NDEBUG
#endif
#include <list>

constexpr auto is_debug =
#ifdef NDEBUG
    false
#else
    true
#endif
;

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std::literals; // NOLINT(clang-diagnostic-header-hygiene)
using std::size_t;
using std::vector;
using std::string;
using std::cout;
using std::cin;

[[maybe_unused]] const auto static_ini_ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return std::cout.tie(nullptr);
}();

class console_output_buffer_binder final
{
    using buf_ptr_t = std::streambuf*;

    vector<std::stringbuf> buffers_;
    const buf_ptr_t console_buf_ = cout.rdbuf();

public:
    explicit console_output_buffer_binder(const size_t additional_count = 0) noexcept :
        buffers_(additional_count + 1),
        console_buf_(std::cout.rdbuf(&buffers_.front())) { bind_to(0); }

    console_output_buffer_binder(const console_output_buffer_binder&) = delete;
    console_output_buffer_binder& operator=(const console_output_buffer_binder&) = delete;

    struct scope_binder
    {
        const buf_ptr_t new_buf_p;
        const buf_ptr_t old_buf_p;

        explicit scope_binder(std::streambuf* new_buf) : new_buf_p(new_buf), old_buf_p(cout.rdbuf(new_buf)) {}
        ~scope_binder() { cout.rdbuf(old_buf_p); }
    };

    void bind_to(const size_t i) { cout.rdbuf(&buffers_[i]); }

    auto scope_bind_to(const size_t i) { return scope_binder{&buffers_[i]}; }

    void add_to_front() { buffers_.emplace_back(); }

    auto scope_add_front()
    {
        add_to_front();
        return scope_bind_to(buffers_.size() - 1);
    }

    ~console_output_buffer_binder()
    {
        cout.rdbuf(console_buf_);
        const auto size = buffers_.size();
        for(auto i = size - 1; i < size; --i) cout << buffers_[i].str();
    }
};

#ifdef __cpp_lib_concepts
#include <concepts>
#include <ranges>

template<typename From, typename To>
concept ConvertibleToRef = std::convertible_to<From, std::decay_t<To>&&> || std::convertible_to<From, std::decay_t<To>&>;

template<typename T, ConvertibleToRef<std::istream> InputStream, typename... Args>
requires requires(InputStream is, T t)
{
    std::constructible_from<T, Args...>;
    is >> t;
}
#else
template<
    typename T,
    typename InputStream,
    typename... Args,
    std::enable_if_t<std::is_constructible_v<T, Args...>>* = nullptr,
    std::enable_if_t<std::is_convertible_v<T, std::istream&&> || std::is_convertible_v<T, std::istream&>>* = nullptr
>
#endif
T get_from_stream(InputStream&& is, Args&&... args)
{
    if constexpr(sizeof...(Args) > 0)
    {
        T t{(std::forward<Args>(args), ...)};
        is >> t;
        return t;       
    }
    else return *std::istream_iterator<T>(is);
}
