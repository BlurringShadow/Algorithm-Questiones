/*
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 *  Symbol       Value
 *  I             1
 *  V             5
 *  X             10
 *  L             50
 *  C             100
 *  D             500
 *  M             1000
 */
#include <array>
#include <iostream>
#include <string_view>

//aggressive constexpr usage

template<auto Count>
using str_buffer_type = std::array<char, Count>;

struct roman_digit_trait_base
{
    using roman_num_buffer_type = str_buffer_type<5>;
    using roman_digits_type = std::array<std::array<roman_num_buffer_type, 10>, 4>;
    using roman_nums_type = std::array<str_buffer_type<16>, 4000>;

    static constexpr std::array<std::pair<char, char>, 4> roman_pairs = {
        std::pair{'I', 'V'},
        {'X', 'L'},
        {'C', 'D'},
        {'M', '\0'}
    };

    static constexpr roman_num_buffer_type get_roman_digit_impl(unsigned value, const unsigned digit)
    {
        roman_num_buffer_type buffer{};
        const auto index = digit - 1;

        switch(value)
        {
        case 4:
            {
                buffer[0] = roman_pairs[index].first;
                buffer[1] = roman_pairs[index].second;
            }
            break;
        case 9:
            {
                buffer[0] = roman_pairs[index].first;

                buffer[1] = roman_pairs[digit].first;
            }
            break;
        default:
            {
                std::size_t i = 0;
                if(value >= 5)
                {
                    buffer[i++] = roman_pairs[index].second;
                    value -= 5;
                }

                for(; value > 0; --value) buffer[i++] = roman_pairs[index].first;
            }
        }

        return buffer;
    }

    static constexpr roman_digits_type implementation()
    {
        roman_digits_type digits{};

        for(unsigned i = 0; i < 3; ++i)
            for(unsigned j = 1; j < 10; ++j)
                digits[i][j] = get_roman_digit_impl(j, i + 1);

        for(unsigned i = 1; i < 4; ++i)
            digits[3][i] = get_roman_digit_impl(i, 4);

        return digits;
    }
};

struct roman_digit_trait : roman_digit_trait_base
{
    static constexpr auto roman_digit = implementation();

    static constexpr auto get_nums()
    {
        std::array<str_buffer_type<16>, 4000> strs{};

        for(decltype(strs)::size_type i = 1; i < strs.size(); ++i)
        {
            auto& str = strs[i];
            std::decay_t<decltype(str)>::size_type str_index = 0;
            auto value = i;
            for(unsigned j = 3, pow = 1000; value > 0; --j)
            {
                const auto quotient = value / pow;

                if(quotient != 0)
                {
                    for(const auto c : roman_digit[j][quotient])
                    {
                        if(c == char{}) break;
                        str[str_index++] = c;
                    }
                    value -= quotient * pow;
                }
                pow /= 10;
            }
        }
        return strs;
    }
};

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    Solution()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
    }

    static constexpr auto roman_nums = roman_digit_trait::get_nums();

    // ReSharper disable once CppInconsistentNaming
    static std::string intToRoman(const int num) { return roman_nums[num].data(); }
};

int main()
{
    int num;
    while(std::cin >> num)
        std::cout << Solution::intToRoman(num) << '\n';
    return 0;
}
