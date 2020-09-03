/*
 * https://leetcode.com/problems/valid-parentheses/
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * An input string is valid if:
    * Open brackets must be closed by the same type of brackets.
    * Open brackets must be closed in the correct order.
    * String is empty
 * Examples :
 * Input    Output
 * "()"     true
 * "()[]{}" true
 * "(]"     false
 * "([)]"   false
 * "{[]}"   true
*/
// test git comment
#include <array>
#include <iostream>
#include <string>

using std::array;
using std::cout;
using std::size_t;
using std::string;
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
    static bool isValid(string&) { return true; }
};

int main() noexcept
{
    try
    {
        constexpr auto nodes_size = 5;
        array<string, nodes_size> test_data;
        string output;

        for(auto& str : test_data) 
            output += "str: {"s + str + "}\tpos:\tresults:" + 
                std::to_string(Solution::isValid(str)) + "\n\n";
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
