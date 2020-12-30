// Created by BlurringShadow at 2020-12-29-上午 11:20

#pragma once
#include "../algorithm_utility/utils.h"

#include <bitset>

class reverse_binary_strings final
{
    using length_t = uint32_t;

    length_t count_{};
    std::bitset<100'000> bits_{};

    auto solve() const
    {
        using namespace std;

        length_t res = 0;
        for(length_t i = 0; i < count_ - 1; ++i) if(bits_[i] == bits_[i + 1]) ++res;

        return (res + 1) / 2;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, reverse_binary_strings& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, reverse_binary_strings& v)
    {
        is >> v.count_;
        for(length_t i = 0; i < v.count_; ++i) v.bits_[i] = get_from_stream<char>(is) == '1';
        return is;
    }
};
