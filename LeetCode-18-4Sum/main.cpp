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
#include <vector>

using std::array;
using std::cout;
using std::size_t;
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

public:
    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> fourSum(vector<int>& nums, const int target)
    {
        return multi_number_sum<4>(nums, target);
    }

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
    static vector<vector<int>> multi_number_sum_impl(const vector<int>& sorted_nums, const int sum_target)
    {
        vector<vector<int>> result_set;

        const auto num_size = sorted_nums.size();
        const auto& num_begin = sorted_nums.cbegin();
        const auto& num_end = sorted_nums.cend();
        const auto last_index = num_size - 1;

        array<int, SumSize - 1> sum_cache{};
        array<size_t, SumSize - 1> indices{};
        size_t last_increase_pos = indices.size() - 1;

        const auto& indices_cbegin = indices.cbegin();
        const auto& indices_cend = indices.cend();

        // initialization
        sum_cache.back() = *num_begin;

        while(true)
        {
            // assign the out of bound index
            for(auto i = last_increase_pos; i != 0; --i)
                sum_cache[i - 1] =
                    sum_cache[i] + sorted_nums[(indices[i - 1] = indices[i] + 1)];

            // find the target number
            auto&& [result, jump] =
                find_target<SumSize>(num_begin, num_end, indices_cbegin, indices_cend, sum_target - sum_cache[0]);
            if(!result.empty()) result_set.emplace_back(std::move(result));

            // increase the indices
            for(last_increase_pos = jump ? last_increase_pos + 1 : 0;; ++last_increase_pos)
            {
                if(last_increase_pos == indices.size()) return result_set;

                auto& index = indices[last_increase_pos];
                const size_t next_index = std::distance(
                    num_begin,
                    std::upper_bound(num_begin + index + 1, num_end, sorted_nums[index])
                );

                // check if available index count is larger than current pos
                if(next_index <= last_index && last_index - next_index > last_increase_pos)
                {
                    const auto next_i = last_increase_pos + 1;

                    index = next_index;
                    sum_cache[last_increase_pos] = (next_i < indices.size() ? sum_cache[next_i] : 0) + sorted_nums[
                        next_index];
                    break;
                }
            }
        }
    }

    template<size_t SumSize>
    static vector<vector<int>> multi_number_sum(vector<int>& nums, const int sum_target)
    {
        static_assert(SumSize >= 2, "Sum size should larger than 0");
        if(nums.size() < SumSize) return vector<vector<int>>{};
        std::sort(nums.begin(), nums.end());
        return multi_number_sum_impl<SumSize>(std::move(nums), sum_target);
    }

    template<int Min, size_t Size>
    static constexpr auto generate_test_data()
    {
        array<int, 4 * Size> data{};
        size_t index = 0;
        auto num = Min;
        for(size_t i = 0; i < Size; ++i, ++num) for(auto j = 0; j < 4; ++j) data[index++] = num;
        return data;
    }
};

int main() noexcept
{
    try
    {
        vector<int> test_data = {-2, -1, 0, 0, 1, 2};

        for(const auto& result : Solution::fourSum(test_data, 0))
        {
            for(const auto value : result) cout << value << '\t';
            cout << '\n';
        }
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
