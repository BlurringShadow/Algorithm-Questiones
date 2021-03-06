/*
 *The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 *(you may want to display this pattern in a fixed font for better legibility)
    P   A   H   N
    A P L S I I G
    Y   I   R
 *And then read line by line: "PAHNAPLSIIGYIR"
*/

#include <iostream>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    static std::string convert(const std::string_view& input_str, const size_t row_size)
    {
        const auto str_size = input_str.size();

        if(row_size == 1 || row_size >= str_size) return {input_str.cbegin(), input_str.cend()};

        const auto pattern_size = 2 * (row_size - 1);

        std::string res;
        size_t res_index = 0;

        res.resize(str_size);

        for(size_t i = 0; i < str_size; i += pattern_size, ++res_index)
            res[res_index] = input_str[i];

        for(size_t i = 1; i < row_size - 1; ++i)
        {
            const auto step_size_two = 2 * i;
            const auto step_size_one = pattern_size - step_size_two;
            for(auto j = i;;)
            {
                if(j >= str_size) break;

                res[res_index] = input_str[j];
                j += step_size_one, ++res_index;
                if(j >= str_size) break;

                res[res_index] = input_str[j];
                j += step_size_two, ++res_index;
            }
        }

        for(auto i = row_size - 1; i < str_size; i += pattern_size, ++res_index)
            res[res_index] = input_str[i];

        return res;
    }
};

int main()
{
    std::cout << Solution::convert("0123456789", 4);
    return 0;
}
