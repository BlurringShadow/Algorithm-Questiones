/*
 * https://leetcode.com/problems/generate-parentheses/
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 * For example, given n = 3, a solution set is:
 * "((()))",
 * "(()())",
 * "(())()",
 * "()(())",
 * "()()()"
*/
#define var decltype(auto)
#define val const decltype(auto)

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using namespace std::literals;

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
    static vector<string> generateParenthesis(const int n)
    {
        return {};
    }
};

int main() noexcept
{
    try
    {
        vector<int> test_data
        {
        };
        string output;

        for(const auto v : test_data)
        {
            output += "num: " + std::to_string(v) + "\nresult: ";
            for(const auto& str : Solution::generateParenthesis(v)) output += str + '\n';
            output += "\n\n";
        }
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
