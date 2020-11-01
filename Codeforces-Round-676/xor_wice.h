// Created by BlurringShadow at 2020-11-01-下午 1:02

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * In order to celebrate Twice's 5th anniversary, Tzuyu and Sana decided to play a game.
 * Tzuyu gave Sana two integers a and b and a really important quest.
 * In order to complete the quest, Sana has to output the smallest possible value of (a⊕x) + (b⊕x) for any given x, 
 * where ⊕ denotes the bitwise XOR operation.
 * 
 * Input
 * Each test contains multiple test cases. 
 * The first line contains the number of test cases t (1≤t≤104). Description of the test cases follows.
 * 
 * The only line of each test case contains two integers a and b (1≤a,b≤109).
 * 
 * Output
 * For each testcase, output the smallest possible value of the given expression.
 */
// ReSharper disable once IdentifierTypo
class xor_wice
{
    uint32_t left_, right_;

public:
    // ReSharper disable once IdentifierTypo
    constexpr xor_wice(const uint32_t left, const uint32_t right) : left_(left), right_(right) {}

    void solve() const noexcept { cout << (left_ ^ right_) << '\n'; }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
    , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        for(auto size = get_from_stream<size_t>(is); size > 0; --size)
        {
            const auto l = get_from_stream<uint32_t>(is);
            const auto r = get_from_stream<uint32_t>(is);
            xor_wice{l, r}.solve();
        }
    }
};
