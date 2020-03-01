/*
 *https://leetcode.com/problems/two-sum/
 *Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 *You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *Example: Given nums = [2, 7, 11, 15], target = 9, Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cout;
using std::vector;
using std::pair;

vector<int> find_index(const vector<int>& nums, const int target)
{
    vector<pair<int, size_t>> number_with_index_vec{nums.size()};

    for (size_t i = 0; i < nums.size(); ++i) number_with_index_vec[i] = {nums[i], i};

    std::sort(
        number_with_index_vec.begin(),
        number_with_index_vec.end(),
        [](const auto& left, const auto& right) { return left.first < right.first; }
    );

    const auto& begin = number_with_index_vec.cbegin();
    const auto& end = number_with_index_vec.cend();

    for (auto i = begin; i < end; ++i)
    {
        const auto dif = target - i->first;
        const auto& j = std::lower_bound(
            std::next(i, 1),
            end,
            dif,
            [](decltype(*i)& left, const int right) { return left.first < right; }
        );

        if (j != end && j->first == dif)
            return {static_cast<int>(i->second), static_cast<int>(j->second)};
    }

    throw std::invalid_argument{""};
}

int main() noexcept
{
    try { for (auto index : find_index({3, 2, 4}, 6)) cout << index; }
    catch (...) {}
    return 0;
}
