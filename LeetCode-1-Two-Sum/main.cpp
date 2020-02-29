/*
 *https://leetcode.com/problems/two-sum/
 *Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 *You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *Example: Given nums = [2, 7, 11, 15], target = 9, Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].
*/

#include <iostream>
#include <vector>
#include <algorithm>

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

    for (size_t first = 0; first < number_with_index_vec.size(); ++first)
        for (auto second = first + 1; second < number_with_index_vec.size(); ++second)
        {
            const auto res = number_with_index_vec[first].first + number_with_index_vec[second].first;
            if (res > target)
                break;
            if (res == target)
                return {
                    static_cast<int>(number_with_index_vec[first].second),
                    static_cast<int>(number_with_index_vec[second].second)
                };
        }

    throw std::invalid_argument{""};
}

int main() noexcept
{
    try { for (auto index : find_index({3, 2, 4}, 6)) cout << index; }
    catch (...) {}
    return 0;
}
