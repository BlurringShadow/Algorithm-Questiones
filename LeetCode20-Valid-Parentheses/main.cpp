/*
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 * Given a linked list, remove the n-th node from the end of list and return its head.
*/

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
