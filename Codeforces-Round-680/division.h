// Created by BlurringShadow at 2020-11-01-下午 7:59

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * Oleg's favorite subjects are History and Math, and his favorite branch of mathematics is division.
 * To improve his division skills, Oleg came up with t pairs of integers pi and qi and for each pair
 * decided to find the greatest integer xi, such that: pi is divisible by xi;xi is not divisible by qi.
 * Oleg is really good at division and managed to find all the answers quickly, how about you?
 */
class division
{
    using value_t = long long;

    value_t p_{}, q_{};
public:
    [[nodiscard]] auto solve() const
    {
        using namespace std;

        value_t res;

        if([=, &res]
        {
            {
                const auto [quot, rem] = lldiv(p_, q_);
                if(rem != 0) return true;

                res = quot;
            }
            while(true)
            {
                const auto [quot, rem] = lldiv(res, q_);
                if(rem != 0) break;
                res = quot;
            }

            return false;
        }())
            return p_;

        if(q_ >= 4)
            for(value_t factor = 2;; ++factor)
            {
                const auto [quot, rem] = lldiv(q_, factor);
                if(quot < factor) break;

                if(rem == 0)
                {
                    auto tmp = p_;
                    while(tmp % q_ == 0) tmp /= factor;
                    set_if_greater(res, tmp);

                    tmp = p_;
                    while(tmp % q_ == 0) tmp /= quot;
                    set_if_greater(res, tmp);
                }
            }

        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, division& v) { return os << v.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, division& v) { return is >> v.p_ >> v.q_; }
};
