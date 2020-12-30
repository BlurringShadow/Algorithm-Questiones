// Created by BlurringShadow at 2020-10-27-下午 10:41

#pragma once
#include "../algorithm_utility/utils.h"

class marketing_scheme
{
    uint64_t min_, max_;

public:
    constexpr marketing_scheme(const uint64_t min, const uint64_t max) noexcept: min_(min), max_(max) {}

    void solve() const noexcept { cout << (max_ < 2 * min_ ? "YES\n" : "NO\n"); }

#ifdef __cpp_lib_concepts
    template<typename InputStream>
    requires std::derived_from<std::remove_reference_t<InputStream>, std::istream>
#else
    // ReSharper disable once CppRedundantParentheses
    template<typename InputStream, SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        for(auto i = get_from_stream<uint64_t>(is); i > 0; --i)
            marketing_scheme{get_from_stream<uint64_t>(is), get_from_stream<uint64_t>(is)}.solve();
    }
};
