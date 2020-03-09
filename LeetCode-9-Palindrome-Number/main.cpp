/*
 * Determine whether an integer is a palindrome.
 * An integer is a palindrome when it reads the same backward as forward.
 */

#include <array>
#include <ios>
#include <iostream>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    // ReSharper disable once CppInconsistentNaming
    static constexpr bool isPalindrome(int input_int)
    {
        if(input_int < 0) return false;
        if(input_int < 10) return true;

        std::array<int, std::numeric_limits<int>::digits10 + 1> nums{};
        std::size_t end = 0;

        while(input_int)
        {
            const auto num = input_int % 10;
            nums[end] = num;
            input_int /= 10;

            ++end;
        }

        --end;
        for(std::size_t begin = 0; begin < end; ++begin, --end)
            if(nums[begin] != nums[end]) return false;

        return true;
    }
};

/*
 * Here is another way of implementation
// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    // ReSharper disable once CppInconsistentNaming
    static constexpr bool isPalindrome(int input_int)
    {
        if(input_int < 0) return false;
        if(input_int == 0) return true;

        std::size_t digits = 0;
        double floating_value = input_int;
        while(floating_value >= 1)
        {
            floating_value /= 10;
            ++digits;
        }

        {
            const auto half_digits = digits / 2;
            for(std::size_t i = 0; i < half_digits; ++i)
            {
                floating_value *= 10;

                const auto right_num = input_int % 10;
                const auto left_num = static_cast<int>(floating_value);

                if(right_num != left_num) return false;

                input_int /= 10;
                floating_value -= left_num;
            }
        }
        return true;
    }
};
 */

int main()
{
    const auto v = Solution::isPalindrome(1000000001);
    std::cout << std::boolalpha << v;
    return 0;
}
