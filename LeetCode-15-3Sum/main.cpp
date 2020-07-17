/*
 * https://leetcode.com/problems/3sum/
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */

#include <iostream>
#include <unordered_set>
#include <vector>

using std::cout;
using std::vector;

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    Solution()
    {
        static const auto _ = []()
        {
            std::ios::sync_with_stdio(false);
            std::cin.tie(nullptr);
            std::cout.tie(nullptr);

            return 0;
        }();
    }

    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> threeSum(const vector<int>& nums)
    {
        std::unordered_set<int> num_set{nums.cbegin(), nums.cend()};
    }
};

int main() noexcept { return 0; }
