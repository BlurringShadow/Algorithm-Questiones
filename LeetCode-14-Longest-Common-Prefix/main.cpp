/*
 * https://leetcode.com/problems/longest-common-prefix/
 * Write a function to find the longest common prefix string amongst an array of strings.

 * If there is no common prefix, return an empty string "".

 * Example:
 * Input: ["flower","flow","flight"] Output: "fl"
 * Input: ["dog","racecar","car"] Output: "" Explanation: There is no common prefix among the input strings.
*/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

// ReSharper disable once CppInconsistentNaming
class Solution
{
    inline static const auto _ = []()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
        return 0;
    }();

public:

    // ReSharper disable once CppInconsistentNaming
    static std::string longestCommonPrefix(const vector<std::string>& strs)
    {
        const auto size = strs.size();
        if(size == 0) { return ""; }
        if(size == 1) { return strs[0]; }

        const auto& anchor_str = strs[0];
        size_t i;

        {
            const auto anchor_str_size = anchor_str.size();
            for(i = 0; i < anchor_str_size; ++i)
            {
                const auto current_char = anchor_str[i];
                for(size_t j = 1; j < size; ++j)
                {
                    const auto& compared_str = strs[j];
                    if(i >= compared_str.size() || compared_str[i] != current_char) goto out_of_scan;
                }
            }
        }

    out_of_scan:
        return i == 0 ? "" : anchor_str.substr(0, i);
    }
};

int main() noexcept
{
    cout << Solution::longestCommonPrefix({"flower", "flow", "flight"});
    return 0;
}
