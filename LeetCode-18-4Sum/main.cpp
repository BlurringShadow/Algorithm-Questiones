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

public:

    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> fourSum(const vector<int>& nums, const int target)
    {
        return multi_number_sum<4>(nums, target);
    }

    template<size_t SumSize>
    static auto count_nums(const vector<int>& nums)
    {
        vector<int> num_set;
        vector<size_t> counts;

        auto min = int_limit::max(), max = int_limit::min();

        // first iteration to find max and min
        for(const auto num : nums)
        {
            if(num < min) min = num;
            if(num > max) max = num;
        }

        counts.resize(max - min + 1);
        num_set.reserve(counts.size());

        // second iteration to record element count and insert them in order
        for(const auto num : nums)
        {
            auto& count = counts[num - min];
            if(count == 0) num_set.insert(std::lower_bound(num_set.cbegin(), num_set.cend(), num), num);

            ++count;
        }

        return tuple{num_set, counts};
    }

    template<size_t SumSize>
    static vector<vector<int>> multi_number_sum(const vector<int>& nums, const int sum_target)
    {
        static_assert(SumSize >= 2, "Sum size should larger than 0");

        vector<vector<int>> result_set;

        array<int, SumSize - 1> sum_cache{};
        array<size_t, SumSize - 1> indices{};

        auto&& [num_set, counts] = count_nums<SumSize>(nums);
        const auto num_set_size = num_set.size();
        const auto min = num_set[0], max = num_set[num_set_size - 1];

        // initialization
        indices[indices.size() - 1] = 0;
        sum_cache[sum_cache.size() - 1] = num_set[0];
        --counts[num_set[0] - min];
        for(size_t i = indices.size() - 1; i != 0; --i)
        {
            auto& count = counts[num_set[indices[i]] - min];
            auto& next_index = indices[i - 1];
            if(count > 0)
            {
                next_index = indices[i];
                --count;
            }
            else
            {
                next_index = indices[i] + 1;
                --counts[num_set[next_index] - min];
            }
            sum_cache[i - 1] = sum_cache[i] + num_set[next_index];
        }

        while(true)
        {
            // find the target number
            const auto target = sum_target - sum_cache[0];

            // if target is less than our last index in number set,
            // than discard to prevent duplication
            if(target < num_set[indices[0]]) indices[0] = num_set_size - 1;
            else if(target <= max && counts[target - min] != 0)
            {
                vector<int> result(SumSize, target);
                std::transform(
                    indices.crbegin(),
                    indices.crend(),
                    result.begin(),
                    [&](const auto index) { return num_set[index]; }
                );
                result_set.emplace_back(std::move(result));
            }

            // increase the indices
            {
                size_t i = 0;
                for(;; ++i)
                {
                    if(i == indices.size()) return result_set;

                    auto& index = indices[i];
                    ++counts[num_set[index] - min];

                    const auto next_index = index + 1;
                    if(next_index != num_set_size)
                    {
                        const auto next_num = num_set[next_index];
                        auto& next_count = counts[next_num - min];

                        if(num_set_size - next_index + next_count > indices.size() - i)
                        {
                            const auto next_i = i + 1;

                            index = next_index;
                            --next_count;
                            sum_cache[i] = (next_i < indices.size() ? sum_cache[next_i] : 0) + next_num;
                            break;
                        }
                    }
                }

                // assign the out of bound index
                for(; i != 0; --i)
                {
                    auto& count = counts[num_set[indices[i]] - min];
                    auto& next_index = indices[i - 1];
                    if(count > 0)
                    {
                        next_index = indices[i];
                        --count;
                    }
                    else
                    {
                        next_index = indices[i] + 1;
                        --counts[num_set[next_index] - min];
                    }
                    sum_cache[i - 1] = sum_cache[i] + num_set[next_index];
                }
            }
        }
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

        for(const auto& result : Solution::fourSum(vector(test_data.cbegin(), test_data.cend()), 2))
        {
            for(const auto value : result) cout << value << '\t';
            cout << '\n';
        }
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
