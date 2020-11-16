// Created by BlurringShadow at 2020-11-16-上午 9:48

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * For a given array a consisting of n integers and a given integer m.
 * Find if it is possible to reorder elements of the array a in such a way that n∑i=1 n∑j=i a[j]/j equals m.
 * It is forbidden to delete elements as well as insert new elements.
 * Please note that no rounding occurs during division, for example, 5/2=2.5.
 * Input
 * The first line contains a single integer t — the number of test cases (1≤t≤100).
 * The test cases follow, each in two lines.
 * 
 * The first line of a test case contains two integers n and m (1≤n≤100, 0≤m≤106).
 * The second line contains integers a1,a2,…,an (0≤ai≤106) — the elements of the array.
 * 
 * Output
 * For each test case print "YES",
 * if it is possible to reorder the elements of the array in such a way
 * that the given formula gives the given value, and "NO" otherwise.
 *  */
class reorder
{
public:
    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
        // ReSharper disable once CppRedundantParentheses
        , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {        
        for(auto test_case_count = get_from_stream<unsigned>(is); test_case_count > 0; --test_case_count)
        {
            auto array_size = get_from_stream<size_t>(is);
            auto target = get_from_stream<size_t>(is);
            for(; array_size > 0; --array_size) target -= get_from_stream<size_t>(is);
            cout << (target == 0 ? "YES" : "NO") << '\n';
        }
    }
};
