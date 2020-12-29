// Created by BlurringShadow at 2020-11-01-下午 7:05

#pragma once
#include <array>

#include "../algorithm_utility/utils.h"

class array_rearrangment
{
public:
    using length_t = uint16_t;
    using value_t = uint16_t;

    static constexpr length_t max_length = 50;

private:
    const length_t length_;
    const value_t target_;
    std::array<value_t, max_length> a_array_;
    std::array<value_t, max_length> b_array_;

public:
    constexpr array_rearrangment(
        const length_t length,
        const value_t target,
        const std::array<value_t, max_length>& a_array,
        const std::array<value_t, max_length>& b_array
    ) noexcept : length_(length), target_(target), a_array_(a_array), b_array_(b_array) {}

    void solve()
    {
        for(length_t i = 0; i < length_; ++i)
            if(a_array_[i] + b_array_[length_ - 1 - i] > target_)
            {
                cout << "NO\n";
                return;
            }
        cout << "YES\n";
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
        , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        for(auto i = get_from_stream<uint16_t>(is); i > 0; --i)
        {
            const auto length = get_from_stream<length_t>(is);
            const auto target = get_from_stream<value_t>(is);
            std::array<value_t, max_length> a_array{};
            std::array<value_t, max_length> b_array{};

            for(length_t j = 0; j < length; ++j)
            {
                a_array[j] = get_from_stream<value_t>(is);
                b_array[j] = get_from_stream<value_t>(is);
            }

            array_rearrangment{length, target, a_array, b_array}.solve();          
        }
    }
};
