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
using std::pair;
using std::vector;
using int_limit = std::numeric_limits<int>;

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

    static bool pair_compare(const pair<int, size_t> left, const pair<int, size_t> right)
    {
        return left.first < right.first;
    }

public:

    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> fourSum(const vector<int>& nums, const int target)
    {
        return multi_number_sum<4>(nums, target);
    }

    template<size_t SumSize>
    static auto count_nums(const vector<int>& nums)
    {
        vector<pair<int, size_t>> ordered_num_set;

        ordered_num_set.reserve(nums.size());
        // second iteration to record element count and insert them in order
        for(const auto num : nums)
        {
            const auto& end = ordered_num_set.end();
            auto&& it = std::lower_bound(
                ordered_num_set.begin(),
                end,
                pair{num, size_t{}},
                pair_compare
            );
            if(it != end && it->first == num) ++it->second;
            else ordered_num_set.emplace(it, pair{num, 1});
        }
        ordered_num_set.shrink_to_fit();
        return ordered_num_set;
    }

    template<size_t SumSize>
    static auto find_target(
        const vector<pair<int, size_t>>& ordered_num_set,
        array<size_t, SumSize - 1>& indices,
        const int target
    )
    {
        vector<int> result;
        auto& first_index = indices.front();
        const auto [target_min, target_min_count] = ordered_num_set[first_index];
        // if target is less than our last index in number set,
        // than discard to prevent duplication
        if(target < target_min) first_index = ordered_num_set.size() - 1;
        else if(std::binary_search(
            ordered_num_set.cbegin() + first_index + (target_min_count == 0),
            ordered_num_set.cend(),
            pair{target, size_t{}},
            pair_compare
        ))
        {
            result.resize(SumSize, target);
            std::transform(
                indices.crbegin(),
                indices.crend(),
                result.begin(),
                [&](const auto index) { return ordered_num_set[index].first; }
            );
        }

        return result;
    }

    template<size_t SumSize>
    static vector<vector<int>> multi_number_sum_impl(vector<pair<int, size_t>> ordered_num_set, const int sum_target)
    {
        vector<vector<int>> result_set;

        const auto num_size = ordered_num_set.size();

        array<int, SumSize - 1> sum_cache{};
        array<size_t, SumSize - 1> indices{};
        const auto max = ordered_num_set.back().second;

        // initialization
        indices.back() = 0;
        {
            auto& [front_num, front_count] = ordered_num_set.front();
            sum_cache.back() = front_num;
            --front_count;
        }

        size_t i = indices.size() - 1;
        while(true)
        {
            // assign the out of bound index
            for(; i != 0; --i)
            {
                const auto previous_index = indices[i];
                auto& count = ordered_num_set[previous_index].second;
                auto& next_index = indices[i - 1];
                if(count > 0)
                {
                    next_index = previous_index;
                    --count;
                }
                else
                {
                    next_index = previous_index + 1;
                    --ordered_num_set[next_index].second;
                }
                sum_cache[i - 1] = sum_cache[i] + ordered_num_set[next_index].first;
            }

            // find the target number
            {
                auto&& result = find_target<SumSize>(ordered_num_set, indices, sum_target - sum_cache[0]);
                if(!result.empty()) result_set.emplace_back(std::move(result));
            }

            // increase the indices
            for(i = 0;; ++i)
            {
                if(i == indices.size()) return result_set;

                auto& index = indices[i];
                ++ordered_num_set[index].second;

                // accumulate the counts
                {
                    size_t accumulate_count = 0;
                    const auto next_index = index + 1;
                    for(auto j = next_index; j < num_size; ++j)
                    {
                        accumulate_count += ordered_num_set[j].second;
                        if(accumulate_count + num_size - 1 - j > i)
                        {
                            auto& [num, count] = ordered_num_set[next_index];
                            const auto next_i = i + 1;

                            index = next_index;
                            --count;
                            sum_cache[i] = (next_i < indices.size() ? sum_cache[next_i] : 0) + num;
                            goto end_of_increase_index_loop;
                        }
                    }
                }
            }
        end_of_increase_index_loop: ;
        }
    }

    template<size_t SumSize>
    static vector<vector<int>> multi_number_sum(const vector<int>& nums, const int sum_target)
    {
        static_assert(SumSize >= 2, "Sum size should larger than 0");
        return nums.empty() ?
               vector<vector<int>>{} :
               multi_number_sum_impl<SumSize>(std::move(count_nums<SumSize>(nums)), sum_target);
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
        constexpr auto test_data = Solution::generate_test_data<-4, 9>();

        for(const auto& result : Solution::fourSum({1,0,-1,0,-2,2}, 0))
        {
            for(const auto value : result) cout << value << '\t';
            cout << '\n';
        }
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
