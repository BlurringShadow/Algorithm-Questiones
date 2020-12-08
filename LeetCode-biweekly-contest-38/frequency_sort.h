// Created by BlurringShadow at 2020-10-31-下午 11:18

#pragma once
#include <array>
#include "../algorithm_utility/utils.h"

/*
 * Given an array of integers nums, sort the array in increasing order based on the frequency of the values. If multiple values have the same frequency, sort them in decreasing order.

Return the sorted array.
 */
class frequency_sort
{
public:
    // ReSharper disable once CppInconsistentNaming
    [[nodiscard]] static vector<int> frequencySort(const vector<int>& nums)
    {
        constexpr auto min = -100, max = 100;
        constexpr auto max_length = 100;

        std::array<int, max - min + 1> count_set{}; // record num count
        std::array<vector<int>, max_length + 1> num_set{}; // last count
        vector<int> res;
        res.reserve(nums.size());

        for(const auto num : nums) ++count_set[num - min];

        for(auto i = static_cast<int>(count_set.size()) - 1; i >= 0; --i)
        {
            const auto count = count_set[i];

            num_set[count].emplace_back(i + min);
        }

        for(size_t i = 1; i < num_set.size(); ++i)
        {
            for(const auto& num : num_set[i])
                res.resize(res.size() + i, num);
        }

        return res;
    }
};
