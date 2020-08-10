/*
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Given a string containing digits from 2-9 inclusive,
 * return all possible letter combinations that the number could represent.
 * A mapping of digit to letters (just like on the telephone buttons) is given below.
 * Note that 1 does not map to any letters.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::array;
using std::vector;
using std::string;
using std::size_t;
using namespace std::literals;

// ReSharper disable once CppInconsistentNaming
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
    static constexpr auto letter_map = array<char, 9>{
        'a',
        'd',
        'g',
        'j',
        'm',
        'p',
        't',
        'w',
        'z' + 1 // special element to mark ending
    };

    static vector<string> impl(string&& digits)
    {
        const auto digit_size = digits.size();
        vector<unsigned> nums(digit_size);
        vector<string> combinations;
        size_t combination_size = 1;

        for(size_t i = 0; i < digit_size; ++i)
        {
            const auto num = static_cast<unsigned>(digits[i] - '0' - 2);
            combination_size *= letter_map[num + 1] - letter_map[num];
            nums[i] = num;
        }

        combinations.resize(combination_size);

        std::transform(
            nums.cbegin(),
            nums.cend(),
            digits.begin(),
            [](const auto num) { return letter_map[num]; }
        );
        combinations[0] = std::move(digits);

        for(size_t i = 1; i < combination_size; ++i)
        {
            auto& combination = combinations[i];
            combination = combinations[i - 1];
            for(size_t j = 0; j < digit_size; ++j)
            {
                auto& c = combination[j];
                const auto num = nums[j];
                ++c;
                if(c < letter_map[num + 1]) break;
                c = letter_map[num];
            }
        }
        return combinations;
    }

    // ReSharper disable once CppInconsistentNaming
    static vector<string> letterCombinations(string&& digits)
    {
        return digits.empty() ? vector<string>{} : impl(std::move(digits));
    }
};

int main() noexcept
{
    try { for(const auto& str : Solution::letterCombinations("234")) std::cout << str << '\n'; }
    catch(const std::exception& e) { std::cout << e.what(); }
    return 0;
}
