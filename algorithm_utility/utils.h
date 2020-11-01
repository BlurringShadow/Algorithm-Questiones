// Created by BlurringShadow at 2020-10-26-上午 10:09

#pragma once
#ifndef _DEBUG
#define NDEBUG
#endif

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

template<typename From, typename To>
struct is_convertible_to_ref : std::bool_constant<std::is_convertible_v<From, std::conditional_t<
        std::is_rvalue_reference_v<From>,
        std::add_rvalue_reference_t<To>,
        std::add_lvalue_reference_t<To>
    >>> {};

template<typename From, typename To>
constexpr auto is_convertible_to_ref_v = is_convertible_to_ref<From, To>::value;

#define COMMA ,
#define SFINAE(condition) std::enable_if_t<condition>* = nullptr

#ifdef __cpp_lib_concepts
#include <concepts>

template<typename... Args, typename T>
concept ConstructibleTo = std::constructible_from<T, Args...>;

template<typename From, typename To>
concept ConvertibleToRef = is_convertible_to_ref_v<From, To>;

template<typename T, typename InputStream, ConstructibleTo<T>... Args>
requires requires(InputStream is, T t)
{
    std::derived_from<std::remove_reference_t<InputStream>, std::istream>;
    is >> t;
}
#else
template<
    typename T,
    typename InputStream,
    typename... Args,
    // ReSharper disable once CppRedundantParentheses
    SFINAE((std::is_constructible_v<T, Args...>)),
    // ReSharper disable once CppRedundantParentheses
    SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))
>
#endif
[[nodiscard]] T get_from_stream(InputStream&& is, Args&&... args)
{
    T t(std::forward<Args>(args)...);
    is >> t;
    return t;
}

template<typename T>
struct auto_cast
{
    T&& t;

#ifdef __cpp_lib_concepts
    template<typename U> requires requires { static_cast<std::decay_t<U>>(std::forward<T>(t)); }
#else
    template<typename U, std::enable_if_t<std::is_convertible_v<T, std::decay_t<U>>>* = nullptr>
#endif
    constexpr operator U() noexcept(std::is_nothrow_constructible_v<T, std::decay_t<U>>)
    {
        return static_cast<std::decay_t<U>>(std::forward<T>(t));
    }
};

template<
    typename ReturnT,
    typename Left,
    typename Right,
    typename Op
#ifdef __cpp_lib_concepts
> requires std::convertible_to<std::conditional_t<
    std::is_convertible_v<Left, ReturnT>,
    std::invoke_result_t<Op, ReturnT, Right>,
    std::invoke_result_t<Op, Left, ReturnT>
>, ReturnT>
#else
    ,
    std::enable_if_t<std::is_convertible_v<std::conditional_t<
        std::is_convertible_v<Left, ReturnT>,
        std::invoke_result_t<Op, ReturnT, Right>,
        std::invoke_result_t<Op, Left, ReturnT>
    >, ReturnT>>* = nullptr
>
#endif
constexpr ReturnT cast_op(Left&& left, Right&& right, Op op)
{
    if constexpr(std::is_convertible_v<Left, ReturnT>)
        return op(static_cast<ReturnT>(std::forward<Left>(left)), std::forward<Right>(right));
    else return op(std::forward<Left>(left), static_cast<ReturnT>(std::forward<Right>(right)));
}
