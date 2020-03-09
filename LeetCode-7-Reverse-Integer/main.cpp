#include <iostream>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    static constexpr int int_max = std::numeric_limits<int>::max();
    static constexpr int int_min = std::numeric_limits<int>::min();

    template<typename IntegerType>
    static constexpr IntegerType reverse_impl(IntegerType input_value)
    {
        static_assert(std::is_integral_v<IntegerType>);
        constexpr auto is_signed = std::is_signed_v<IntegerType>;

        constexpr auto digits = std::numeric_limits<IntegerType>::digits10;
        constexpr auto max = std::numeric_limits<IntegerType>::max();
        constexpr auto before_max = max / 10;

        IntegerType res = 0;
        while(input_value)
        {
            if(res > before_max || res < -before_max) return 0;

            if constexpr(is_signed) res *= 10;
            else res *= 10u;

            const auto num = input_value % 10;

            if constexpr(is_signed) { if((res > 0 && res > max - num) || (res < 0 && res < -max - num)) return 0; }
            else if(res + num < res) return 0;

            res += num;
            input_value /= 10;
        }

        return res;
    }

    template<typename IntegerType>
    static constexpr int reverse(const IntegerType input_value)
    {
        if(input_value > int_max || input_value < int_min) return 0;

        return reverse_impl(static_cast<int>(input_value));
    }
};


int main()
{
    const auto v = Solution::reverse(-2147483648);
    std::cout << v;
    return 0;
}
