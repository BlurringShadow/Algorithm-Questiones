// Created by BlurringShadow at 2021-02-28-下午 9:52


#pragma once
#include "../algorithm_utility/utils.h"

class k_th_largest_value final
{
    vector<unsigned short> nums_;
    vector<std::pair<bool, uint64_t>> queries_;

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        vector<int> results;

        auto nums = nums_;
        size_t count_of_ones = std::count(nums.cbegin(), nums.cend(), 1);

        results.reserve(nums.size());
        for(auto [type, value] : queries_)
            if(type) results.emplace_back(count_of_ones >= value);
            else
            {
                auto& num = nums[value - 1];
                if(num == 0)
                {
                    ++count_of_ones;
                    num = 1;
                }
                else
                {
                    --count_of_ones;
                    num = 0;
                }
            }

        return results;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, k_th_largest_value& s)
    {
        console_output_buffer_binder b;
        for(auto result : s.solve())
            os << result << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, k_th_largest_value& v)
    {
        auto& queries = v.queries_;
        {
            auto& nums = v.nums_;
            nums.resize(get_from_stream(is));
            queries.resize(get_from_stream(is));
            for(auto& num : nums) is >> num;
        }

        for(auto& [type, value] : queries)
        {
            type = get_from_stream<unsigned short>(is) == 2;
            is >> value;
        }

        return is;
    }

    k_th_largest_value() noexcept {}
};

using problem_t = k_th_largest_value;
