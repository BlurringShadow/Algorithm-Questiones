// Created by BlurringShadow at 2020-12-30-下午 8:53

#pragma once

#include "../algorithm_utility/utils.h"

/*
 * Chef Monocarp has just put n dishes into an oven.
 * He knows that the i-th dish has its optimal cooking time equal to ti minutes.
 * At any positive integer minute T Monocarp can put no more than one dish out of the oven.
 * If the i-th dish is put out at some minute T,
 * then its unpleasant value is |T−ti| — the absolute difference between T and ti.
 * Once the dish is out of the oven, it can't go back in.
 * Monocarp should put all the dishes out of the oven.
 * What is the minimum total unpleasant value Monocarp can obtain?
 */
class chef_monocarp final
{
    using value_t = uint32_t;

    vector<value_t> delicious_dishes_;

    static constexpr auto abs_diff(const value_t left, const value_t right) { return left > right ? left - right : right - left; }

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        const auto dishes_size = static_cast<value_t>(delicious_dishes_.size());

        vector<value_t> dp(dishes_size + 1, numeric_limits<value_t>::max());

        dp.front() = 0;
        for(value_t i = 1; i <= 2 * dishes_size; ++i) 
            for(auto j = dishes_size; j > 0; --j)
            {
                auto& current = dp[j];
                const auto previous = dp[j - 1];
                if(current > previous)
                    current = min(current, previous + abs_diff(delicious_dishes_[j - 1], i));
            }

        return dp.back();
    }

public:
    friend std::ostream& operator<<(std::ostream& os, chef_monocarp& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, chef_monocarp& v)
    {
        v.delicious_dishes_.resize(get_from_stream(is));
        for(auto& dish : v.delicious_dishes_) is >> dish;
        sort(v.delicious_dishes_.begin(), v.delicious_dishes_.end());
        return is;
    }

    chef_monocarp() noexcept {}
};
