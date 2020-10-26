// Created by BlurringShadow at 2020-10-26-下午 1:55

#pragma once
#include "../algorithm_utility/utils.h"
#include <string_view>

using std::string_view;

/*
 * Zookeeper is playing a game.
 * In this game, Zookeeper must use bombs to bomb a string that consists of letters 'A' and 'B'.
 * He can use bombs to bomb a substring which is either "AB" or "BB".
 * When he bombs such a substring, the substring gets deleted from the string
 * and the remaining parts of the string get concatenated.
 * For example, Zookeeper can use two such operations: AABABBA → AABBA → AAA.
 * Zookeeper wonders what the shortest string he can make is.
 * Can you help him find the length of the shortest string?
 *
 * Input:
 * Each test contains multiple test cases.
 * The first line contains a single integer t (1≤t≤20000)  — the number of test cases.
 * The description of the test cases follows.
 * Each of the next t lines contains a single test case each,
 * consisting of a non-empty string s: the string that Zookeeper needs to bomb.
 * It is guaranteed that all symbols of s are either 'A' or 'B'.
 * It is guaranteed that the sum of |s| (length of s) among all test cases does not exceed 2105.
 * Output:
 * For each test case, print a single integer: the length of the shortest string that Zookeeper can make.
 */
class ABBB
{
    string_view str_;
public:
    explicit constexpr ABBB(const string_view str) noexcept : str_(str) {}

    void solve() const
    {
        size_t size = 0;
        for(const auto c : str_)
            if(c == 'B' && size > 0) --size;
            else ++size;
        cout << size << '\n';
    }

    static void create_from_input()
    {
        size_t size;
        cin >> size;

        for(decltype(size) i = 0; i < size; ++i)
        {
            string str;
            cin >> str;
            ABBB{std::move(str)}.solve();
        }
    }
};
