#pragma once
#include "../algorithm_utility/utils.h"

#include <bitset>
#include <numeric>

class anti_knapsack final
{
    uint16_t n_{}, k_{};

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        if(n_ == 1) return k_ == 0 ? vector<uint16_t>{1} : vector<uint16_t>{};

        uint16_t half = (k_ + 1) / 2;
        vector<uint16_t> nums(n_ - half);
        uint16_t i = 0;
        for(; half < k_; ++i, ++half) nums[i] = half;
        ++half;
        for(; i < nums.size(); ++i, ++half) nums[i] = half;

        return nums;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, anti_knapsack& s)
    {
        const auto& res = s.solve();
        console_output_buffer_binder binder;

        os << res.size() << '\n';
        for(auto v : res) os << v << ' ';
        return os << '\n';
    }

    friend std::istream& operator>>(std::istream& is, anti_knapsack& v)
    {
        return is >> v.n_ >> v.k_;
    }

    anti_knapsack() noexcept {}
};

using problem_t = anti_knapsack;
