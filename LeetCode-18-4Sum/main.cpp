/*
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Given an array nums of n integers and an integer target,
 * are there elements a, b, c, and d in nums such that a + b + c + d = target?
 * Find all unique quadruplets in the array which gives the sum of target.
 * The solution set must not contain duplicate quadruplets.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using std::array;
using std::cout;
using std::size_t;
using std::string;
using std::tuple;
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

    template<size_t SumSize>
    static auto find_target(
        const vector<int>::const_iterator& num_begin,
        const vector<int>::const_iterator& num_end,
        const typename array<size_t, SumSize - 1>::const_iterator& indices_cbegin,
        const typename array<size_t, SumSize - 1>::const_iterator& indices_cend,
        const int target
    )
    {
        vector<int> result;
        const auto first_index = *indices_cbegin;
        auto&& first_num_it = num_begin + first_index;

        // if target is less than our last index in number set, than discard to prevent duplication
        if(std::binary_search(++first_num_it, num_end, target))
        {
            result.resize(SumSize, target);
            std::transform(
                std::make_reverse_iterator(indices_cend),
                std::make_reverse_iterator(indices_cbegin),
                result.begin(),
                [&](const auto index) { return *(num_begin + index); }
            );
        }

        return tuple{result, target <= *first_num_it};
    }

    template<size_t SumSize>
    static auto increase_index(
        const int sum_target,
        const vector<int>::const_iterator& num_begin,
        const vector<int>::const_iterator& num_end,
        array<int, SumSize - 1>& sum_cache,
        const typename array<size_t, SumSize - 1>::iterator& indices_begin,
        const typename array<size_t, SumSize - 1>::iterator& indices_end,
        const size_t current_index_pos
    )
    {
        const auto max_num = *(num_end - 1);
        const size_t num_size = num_end - num_begin;
        const auto last_index = static_cast<size_t>(num_size - 1);
        const auto next_index_pos = current_index_pos + 1;
        auto& current_index = *(indices_begin + current_index_pos);
        const size_t indices_size = indices_end - indices_begin;
        vector<int> result;

        while(true)
        {
            current_index =
                std::upper_bound(num_begin + current_index + 1, num_end, *(num_begin + current_index)) - num_begin;

            // check if available index count is larger than current pos
            if(current_index > last_index || last_index - current_index <= current_index_pos) break;

            sum_cache[current_index_pos] =
                (next_index_pos < indices_size ? sum_cache[next_index_pos] : 0) + *(num_begin + current_index);
            if(!result.empty()) return tuple{true, result};

            // check possible largest sum is larger than target
            for(auto i = decltype(current_index_pos){0}, num_index = last_index - 1;
                i != current_index_pos;
                ++i, --num_index)
                *(indices_begin + i) = num_index;

            for(auto i = current_index_pos; i != 0; --i)
                sum_cache[i - 1] =
                    sum_cache[i] + *(num_begin + *(indices_begin + i - 1));

            const auto largest_sum = sum_cache[0] + max_num;
            if(largest_sum == sum_target)
            {
                result.resize(SumSize, max_num);
                std::transform(
                    std::make_reverse_iterator(indices_end),
                    std::make_reverse_iterator(indices_begin),
                    result.begin(),
                    [&](const auto index) { return *(num_begin + index); }
                );
            }
            else if(largest_sum > sum_target) return tuple{true, result};
        }

        return tuple{false, result};
    }

    template<size_t SumSize>
    static void indices_initialize(
        const vector<int>::const_iterator& num_begin,
        array<int, SumSize - 1>& sum_cache,
        array<size_t, SumSize - 1>& indices,
        const size_t last_increase_pos
    )
    {
        for(auto i = last_increase_pos; i != 0; --i)
            sum_cache[i - 1] =
                sum_cache[i] + *(num_begin + (indices[i - 1] = indices[i] + 1));
    }

    template<size_t SumSize>
    static vector<vector<int>> multi_number_sum_impl(
        const vector<int>::const_iterator& num_begin,
        const vector<int>::const_iterator& num_end, 
        const int sum_target
    )
    {
        vector<vector<int>> result_set;

        array<int, SumSize - 1> sum_cache{};
        array<size_t, SumSize - 1> indices{};

        const auto& indices_begin = indices.begin();
        const auto& indices_end = indices.end();

        size_t last_increase_pos = indices.size() - 1;

        // initialization
        sum_cache.back() = *num_begin;
        while(true)
        {
            // assign the out of bound index
            indices_initialize<SumSize>(num_begin, sum_cache, indices, last_increase_pos);

            bool jump;

            // find the target number
            {
                auto&& [result, is_too_large] =
                    find_target<SumSize>(num_begin, num_end, indices_begin, indices_end, sum_target - sum_cache[0]);
                if(!result.empty()) result_set.emplace_back(std::move(result));
                jump = is_too_large;
            }

            // increase the indices
            for(last_increase_pos = jump ? last_increase_pos + 1 : 0; ; ++last_increase_pos)
            {
                if(last_increase_pos == indices.size()) return result_set;
                auto&& [is_accepted, result] = increase_index<SumSize>(
                    sum_target,
                    num_begin,
                    num_end,
                    sum_cache,
                    indices_begin,
                    indices_end,
                    last_increase_pos
                );
                if(!result.empty()) result_set.emplace_back(std::move(result));
                if(is_accepted) break;
            }
        }
    }

public:
    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> fourSum(vector<int>& nums, const int target)
    {
        return multi_number_sum<4>(nums, target);
    }

    template<size_t SumSize>
    static vector<vector<int>> multi_number_sum(vector<int>& nums, const int sum_target)
    {
        static_assert(SumSize >= 2, "Sum size should larger than 0");
        if(nums.size() < SumSize) return vector<vector<int>>{};
        std::sort(nums.begin(), nums.end());
        return multi_number_sum_impl<SumSize>(nums.cbegin(), nums.cend(), sum_target);
    }
};

int main() noexcept
{
    try
    {
        vector<tuple<vector<int>, int>> test_data = {
            {{0, 0, 0, 0}, 1},
            {{-1, -2, 0, 0, 1, 2}, 0},
            {{-3, -2, -1, 0, 1, 2, 3}, 0},
            {{-3, -2, -1, 0, 0, 1, 2, 3}, 0}
        };
        string output;

        for(auto&& [nums, target] : test_data)
        {
            output += "input: {";
            for(const auto num : nums) { output += std::to_string(num) + ','; }
            output.resize(output.size() - 1);
            output += "}\ttarget: " + std::to_string(target) + "\nresults:\n";
            for(const auto& result : Solution::fourSum(nums, target))
            {
                for(const auto value : result) output += std::to_string(value) + '\t';
                output += '\n';
            }
            output += '\n';
        }
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
