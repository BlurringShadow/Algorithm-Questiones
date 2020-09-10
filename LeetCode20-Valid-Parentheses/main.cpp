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

#include <array>
#include <iostream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

using std::array;
using std::cout;
using std::size_t;
using std::string;
using std::string_view;
using std::vector;
using std::stack;
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
    static bool isValid(const string_view& str)
    {
        static constexpr auto matches = []()
        {
            array<char, std::numeric_limits<char>::max() + 1> m{};
            m[')'] = '(';
            m[']'] = '[';
            m['}'] = '{';

            return m;
        }();
        static constexpr auto cend = matches.cend();

        stack<char> match_stack;

        for(const auto c : str)
        {
            const auto match = matches[c];
            if(match == char{}) match_stack.push(c);
            else
            {
                if(match_stack.empty() || match_stack.top() != match) return false;
                match_stack.pop();
            }
        }

        return match_stack.empty();
    }
};

int main() noexcept
{
    try
    {
        vector<string> test_data{"((", "()", "()[]{}", "(]", "([)]", "{[]}", "("};
        string output;

        for(const auto& str : test_data) 
            output += "str: " + str + "\tresults:" + 
                std::to_string(Solution::isValid(str)) + "\n\n";
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
