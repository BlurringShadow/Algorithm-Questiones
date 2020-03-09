/*
 * Implement atoi which converts a string to an integer.
 * The function first discards as many whitespace characters as necessary until the first non-whitespace character is found.
 * Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.
 * The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.
 * If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
 * If no valid conversion could be performed, a zero value is returned.
 */

#include <iostream>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    static constexpr std::int32_t int32_max = std::numeric_limits<std::int32_t>::max();
    static constexpr std::int32_t int32_min = std::numeric_limits<std::int32_t>::min();

    // ReSharper disable once IdentifierTypo
    // ReSharper disable once CppInconsistentNaming
    static constexpr int myAtoi(const std::string_view& str)
    {
        const auto str_size = str.size();

        if(str_size == 0) return 0;

        auto is_positive = true;
        std::uint64_t res = 0;
        {
            std::size_t str_index = 0;

            for(; str_index < str_size && str[str_index] == ' '; ++str_index);

            switch(str[str_index])
            {
            case '-': is_positive = false;
            case '+': ++str_index;
            default: break;
            }

            for(; str_index < str_size; ++str_index)
            {
                const auto num = str[str_index] - '0';

                if(num < 0 || num > 9) break;

                res *= 10;

                res += num;
                if(res > int32_max) return is_positive ? int32_max : int32_min;
            }
        }

        return (is_positive ? 1 : -1) * static_cast<std::int32_t>(res);
    }
};

int main()
{
    const auto v = Solution::myAtoi("  -9123456789");
    std::cout << v;
    return 0;
}
