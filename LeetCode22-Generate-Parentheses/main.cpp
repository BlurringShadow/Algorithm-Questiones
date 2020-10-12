/*
 * https://leetcode.com/problems/generate-parentheses/
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 * For example, given n = 3, a solution set is:
 * "((()))", "(()())", "(())()", "()(())", "()()()"
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

    inline static vector<vector<string>> generated_ = {{""}};

    // see "catalan number" for more detail
    static void generate_to(const size_t n)
    {
        if(n + 1 <= generated_.size()) return;
        const auto old_size = generated_.size();
        generated_.resize(n + 1);

        for(auto i = old_size; i < generated_.size(); ++i)
            for(size_t j = 0; j < i; ++j)
                for(const auto& s1 : generated_[j])
                    for(const auto& s2 : generated_[i - 1 - j])
                    {
                        auto&& str = '(' + s1;
                        str += ')' + s2;
                        generated_[i].emplace_back(std::move(str));
                    }
    }

public:
    // ReSharper disable once CppInconsistentNaming
    static const vector<string>& generateParenthesis(const int n)
    {
        generate_to(n);
        return generated_[n];
    }
};

int main() noexcept
{
    try
    {
        vector<int> test_data{3, 4, 5};
        string output;

        for(const auto v : test_data)
        {
            output += "num: " + std::to_string(v) + "\nresult: \n";
            for(const auto& str : Solution::generateParenthesis(v)) output += str + '\n';
            output += "\n\n";
        }
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
