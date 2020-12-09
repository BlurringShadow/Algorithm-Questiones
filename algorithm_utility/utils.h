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

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
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

    [[maybe_unused]] auto scope_bind_to(const size_t i) { return scope_binder{&buffers_[i]}; }

    void add_to_front() { buffers_.emplace_back(); }

    [[maybe_unused]] auto scope_add_front()
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

template<typename InputStream, typename... Args>
struct input_helper
{
    InputStream is;
    std::tuple<Args&&...> args;

    // ReSharper disable once CppNonExplicitConversionOperator
    template<typename T>
    operator T()
    {
        auto t = std::make_from_tuple<T>(std::move(args));
        is >> t;
        return t;
    }
};

template<typename InputStream, typename... Args, template<typename...> typename Tuple>
input_helper(InputStream&&, Tuple<Args&&...>&&) -> input_helper<InputStream, Args...>;

#ifdef __cpp_lib_concepts
#include <concepts>

template<typename... Args, typename T>
concept ConstructibleTo = std::constructible_from<T, Args...>;

template<typename From, typename To>
concept ConvertibleToRef = is_convertible_to_ref_v<From, To>;

template<typename T = void, typename InputStream, ConstructibleTo<T>... Args>
requires std::derived_from<std::remove_reference_t<InputStream>, std::istream>
#else
template<
    typename T = void,
    typename InputStream,
    typename... Args,
    SFINAE((std::is_same_v<T, void> || std::is_constructible_v<T, Args...>)),
    SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))
>
#endif
[[nodiscard]] auto get_from_stream(InputStream&& is, Args&&...args)
{
    input_helper v{is, std::forward_as_tuple(std::forward<Args>(args)...)};
    if constexpr(std::is_same_v<T, void>) return v;
    else return static_cast<T>(v);
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

template<typename T>
auto_cast(T&& t) -> auto_cast<T>;

template<typename T, typename U, typename Comp>
constexpr std::conditional_t<std::is_lvalue_reference_v<T&&>, T&&, T> set_if(T&& left, U&& right, Comp comp)
{
    if(comp(right, left)) left = std::forward<U>(right);
    return left;
}

template<typename T, typename U>
constexpr decltype(auto) set_if_greater(T&& left, U&& right)
{
    return set_if(std::forward<T>(left), std::forward<U>(right), std::greater<>{});
}

template<typename T>
constexpr T low_bit(const T& t) { return t & ~t + 1; }

template<typename T, typename Func>
class binary_indexed_tree_base
{
    void reset_tree()
    {
        const auto size = vec_.size();
        vec_.resize(vec_.size() * 2 - 1);

        for(size_t i = 1; i < size; ++i)
        {
            get(i) = vec_[i];
            for(auto j = low_bit(i) >> 1; j > 0; j >>= 1)
                get(i) = apply_(std::move(get(i)), get(i - j));
        }
    }

protected:
    vector<T> vec_;
    Func apply_;

    [[nodiscard]] auto get_tree_index(const size_t index) const { return index == 0 ? 0 : index + vec_.size() / 2; }

    [[nodiscard]] auto& get(const size_t index) { return vec_[get_tree_index(index)]; }

    explicit binary_indexed_tree_base(Func f, vector<T> vec = {}) : vec_(std::move(vec)), apply_(std::move(f))
    {
        reset_tree();
    }

public:
    [[nodiscard]] auto& operator[](size_t index) const { return vec_[index]; }

    [[nodiscard]] auto& get(const size_t index) const { return vec_[get_tree_index(index)]; }

    [[nodiscard]] auto get_range(size_t index) const
    {
        T res = vec_[0];
        for(; index > 0; index -= low_bit(index)) res = apply_(std::move(res), get(index));
        return res;
    }

    void reset(vector<T> vec = {})
    {
        vec_ = std::move(vec);
        reset_tree();
    }

    [[nodiscard]] auto begin() const { return vec_.begin(); }
    [[nodiscard]] auto end() const { return vec_.begin() + (vec_.size() + 1) / 2; }
};

template<typename T, typename Func, typename Inverter = void>
class binary_indexed_tree : public binary_indexed_tree_base<T, Func>
{
    Inverter inverter_;

public:
    using base = binary_indexed_tree_base<T, Func>;

    explicit binary_indexed_tree(Func f = {}, Inverter inverter = {}, vector<T> vec = {}) :
        base(std::move(f), std::move(vec)),
        inverter_(std::move(inverter)) {}

    template<typename... Args>
    void update(size_t index, Args&&... args)
    {
        if(index == 0)
        {
            base::vec_[0] = T(args...);
            return;
        }

        const auto& delta = [&, this]()
        {
            auto previous = std::move(base::vec_[index]);
            base::vec_[index] = T(std::forward<Args>(args)...);

            return inverter_(base::vec_[index], previous);
        }();

        const auto size = (base::vec_.size() + 1) / 2;

        while(true)
        {
            index = index + low_bit(index);
            if(index >= size) break;

            base::get(index) = base::apply_(std::move(base::get(index)), delta);
        }
    }

    [[nodiscard]] auto get_range(const size_t begin, const size_t end) const
    {
        return inverter_(base::get_range(end), base::get_range(begin));
    }
};

template<typename T, typename Func>
class binary_indexed_tree<T, Func, void> : public binary_indexed_tree_base<T, Func>
{
public:
    using base = binary_indexed_tree_base<T, Func>;

    using base::get_range;

    explicit binary_indexed_tree(Func f = {}, vector<T> vec = {}) : base(std::move(f), std::move(vec)) {}

    template<typename... Args>
    void update(size_t index, Args&&... args)
    {
        base::vec_[index] = T(args...);

        if(index == 0) return;

        for(const auto size = (base::vec_.size() + 1) / 2; index < size; index = index + low_bit(index))
        {
            base::get(index) = base::vec_[index];

            for(auto i = low_bit(index) >> 1; i > 0; i >>= 1)
                base::get(index) = base::apply_(std::move(base::get(index)), base::get(index - i));
        }
    }

    [[nodiscard]] auto get_range(const size_t begin, size_t end) const
    {
        auto ret = base::vec_[end--];
        for(; begin <= end; ret = base::apply_(std::move(ret), base::vec_[end]), --end)
            while(true)
            {
                const auto pre = end;

                end -= low_bit(end);
                if(end < begin)
                {
                    end = pre;
                    break;
                }
                ret = base::apply_(std::move(ret), base::get(end));
            }
    }
};

template<typename T, typename Compare>
bool is_between(const T& v, const T& min, const T& max, Compare cmp)
{
    return std::addressof(std::clamp(v, min, max, cmp)) == std::addressof(v);
}

template<typename T>
bool is_between(const T& v, const T& min, const T& max) { return is_between(v, min, max, std::less<>{}); }
