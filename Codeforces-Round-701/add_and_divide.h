// Created by BlurringShadow at 2021-02-12-下午 11:03

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * You have two positive integers a and b.
 * You can perform two kinds of operations:
 * a=⌊ab⌋(replace a with the integer part of the division between a and b)
 * b=b+1 (increase b by 1)
 * Find the minimum number of operations required to make a=0.
 */
class add_and_divide final
{
    uint64_t a_ = 0, b_ = 0;

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        auto min_count = numeric_limits<uint64_t>::max();
        for(auto b = max<decltype(b_)>(b_, 2);; ++b)
        {
            auto count = b - b_;

            if(count >= min_count) break;

            count += upper_log(a_, b);

            if(count < min_count) min_count = count;
        }
        return min_count;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, add_and_divide& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, add_and_divide& v)
    {
        return is >> v.a_ >> v.b_;
    }
};
