/*
 * https://leetcode.com/problems/3sum-closest/
 * Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target.
 * Return the sum of the three integers.
 * You may assume that each input would have exactly one solution.
*/

#include <array>
#include <iostream>
#include <optional>
#include <vector>

using std::cout;
using std::array;
using std::vector;

// ReSharper disable once CppInconsistentNaming
class Solution
{
    [[maybe_unused]] inline static const auto _ = []()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        return 0;
    }();

public:
    static constexpr auto value_range = std::pair<int, int>{-1000, 1000};
    static constexpr auto target_range = std::pair<int, int>{-10000, 10000};
    static constexpr auto max_length = 1000;

    // ReSharper disable once CppInconsistentNaming
    static int threeSumClosest(const vector<int>& nums, const int target)
    {
        constexpr auto min = value_range.first;
        constexpr auto max = value_range.second;

        array<int, max - min + 1> counts{};

        array<int, max_length> value_set{};
        decltype(value_set.size()) length = 0;

        for(const auto num : nums) ++counts[num - min];

        for(auto i = 0; i < static_cast<int>(counts.size()); i++) { if(counts[i] > 0) value_set[length++] = min + i; }

        int offset;
        {
            const auto sum_up_extreme = [&](auto it, const unsigned size)
            {
                unsigned i = 0;
                auto sum = 0;
                while(true)
                {
                    const auto v = *(it++);
                    for(auto count = counts[v - min]; count > 0; --count)
                    {
                        sum += v;
                        ++i;
                        if(i == size) return sum;
                    }
                }
            };

            const auto from_min_offset = sum_up_extreme(value_set.cbegin(), 3) - target;
            const auto from_max_offset = sum_up_extreme(
                std::make_reverse_iterator(value_set.cbegin() + length),
                3
            ) - target;
            offset = -from_min_offset > from_max_offset ? from_min_offset : from_max_offset;
        }

        for(decltype(length) i = 0; i < length; ++i)
        {
            const auto first_v = value_set[i];

            for(auto j = !(counts[first_v - min] > 1) + i; j < length; ++j)
            {
                const auto second_v = value_set[j];
                const auto target_v = target - (first_v + second_v);
                const auto abs_offset = std::abs(offset);
                auto target_min = std::max(target_v - abs_offset, second_v - 1);
                auto candidate = std::min(target_v + abs_offset, value_set[length - 1]);

                if(candidate <= target_min) break;

                do
                {
                    if(counts[candidate - min] > (second_v == candidate ? 1 + (i == j) : 0))
                    {
                        if(candidate == target_v) return target;
                        offset = candidate - target_v;
                        if(offset < 0) break;
                        target_min = std::max(target_v - offset, second_v - 1);
                    }
                    --candidate;
                }
                while(candidate > target_min);
            }
        }

        return target + offset;
    }
};

int main() noexcept
{
    try { std::cout << Solution::threeSumClosest({2, 2, 2, 10}, 14); }
    catch(const std::exception& e) { std::cout << e.what(); }
    return 0;
}
