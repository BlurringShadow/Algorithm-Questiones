/*
 * https://leetcode.com/problems/3sum/
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using std::cout;
using std::vector;
using std::unordered_map;

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
    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> threeSum(const vector<int>& nums)
    {
        using limits = std::numeric_limits<int>;

        vector<vector<int>> res;
        unordered_map<int, size_t> count_map(nums.size());
        auto max = limits::min(), min = limits::max();
        vector<int> vec;

        for(const auto num : nums)
        {
            ++count_map[num];
            if(num > max) max = num;
            if(num < min) min = num;
        }

        const auto& count_map_end = count_map.cend();

        vec.reserve(nums.size());
        for(auto i = min; i <= max; ++i) if(count_map.find(i) != count_map_end) vec.push_back(i);

        const auto& end = vec.cend();

        for(auto&& i = vec.cbegin(); i != end; ++i)
        {
            const auto first = *i;
            {
                const auto left_count_it = count_map.find(*i);

                if(left_count_it == count_map_end) continue;

                const auto left_count = left_count_it->second;
                if(left_count > 1)
                {
                    const auto third = -(first + first);
                    if(third < first) continue;

                    if(third == first) { if(left_count >= 3) res.push_back({first, first, third}); }
                    else if(count_map.find(third) != count_map_end) res.push_back({first, first, third});
                }
            }

            for(auto&& j = std::next(i); j != end; ++j)
            {
                const auto second = *j;

                const auto third = -(first + second);
                if(third < second) break;

                const auto& third_count_it = count_map.find(third);
                if(third_count_it == count_map_end) continue;
                if(third_count_it->second > (third == second ? 1 : 0)) res.push_back({first, second, third});
            }
        }

        return res;
    }
};

int main() noexcept
{
    try
    {
        for(const auto& element : Solution::threeSum({0, -4, -1, -4, -2, -3, 2}))
        {
            for(const auto value : element) std::cout << value << ' ';
            std::cout << '\n';
        }
    }
    catch(const std::exception& e) { std::cout << e.what(); }
    return 0;
}
