// Created by BlurringShadow at 2021-02-07-下午 10:37

#pragma once

#include "../algorithm_utility/utils.h"

/*
 * Homer has two friends Alice and Bob. Both of them are string fans.
 * One day, Alice and Bob decide to play a game on a string s=s1s2…sn of length n
 * consisting of lowercase English letters.
 * They move in turns alternatively and Alice makes the first move.
 * In a move, a player must choose an index i (1≤i≤n) that has not been chosen before,
 * and change si to any other lowercase English letter c that c≠si.
 * When all indices have been chosen, the game ends.
 * The goal of Alice is to make the final string lexicographically as small as possible,
 * while the goal of Bob is to make the final string lexicographically as large as possible.
 * Both of them are game experts, so they always play games optimally.
 * Homer is not a game expert, so he wonders what the final string will be.
 * A string a is lexicographically smaller than a string b
 * if and only if one of the following holds:
 * a is a prefix of b, but a≠b;
 * in the first position where a and b differ,
 * the string a has a letter that appears earlier in the alphabet
 * than the corresponding letter in b.
 */
class yet_another_string_game final
{
    string str_;

    auto solve()
    {
        using namespace std;

        auto str = str_;

        for(size_t i = 0; i < str.size(); i += 2)
        {
            auto& c = str[i];
            c = c == 'a' ? 'b' : 'a';
        }

        for(size_t i = 1; i < str.size(); i += 2)
        {
            auto& c = str[i];
            c = c == 'z' ? 'y' : 'z';
        }

        return str;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, yet_another_string_game& s)
    {
        return os << s.solve() << '\n';
    }

    friend std::istream& operator>>(std::istream& is, yet_another_string_game& v)
    {
        return is >> v.str_;
    }
};
