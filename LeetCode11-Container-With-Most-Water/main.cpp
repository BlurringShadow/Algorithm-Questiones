/*
 * Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
 * n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
 * Find two lines, which together with x-axis forms a container, such that the container contains the most water.
 */

#include <iostream>
#include <vector>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    // ReSharper disable once CppInconsistentNaming
    [[nodiscard]] static int maxArea(const std::vector<int>& height)
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        auto left_index = 0, right_index = static_cast<int>(height.size() - 1);
        auto max = 0;
        while(left_index < right_index)
        {
            decltype(left_index) next;
            decltype(max) product;

            const auto l_value = height[left_index], r_value = height[right_index];

            if(l_value < r_value)
            {
                product = l_value * (right_index - left_index);
                for(next = left_index + 1;
                    next < right_index && height[next] < r_value && height[next] - l_value < next - left_index;
                    ++next);
                left_index = next;
            }
            else
            {
                product = height[right_index] * (right_index - left_index);
                for(next = right_index - 1;
                    next > left_index && height[next] < l_value && height[next] - r_value < right_index - next;
                    --next);
                right_index = next;
            }
            if(product > max) max = product;
        }
        return max;
    }
};

int main()
{
    const auto test_data = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    try
    {
        std::cout << Solution::maxArea(test_data);
    }
    catch(...)
    {
    }
    return 0;
}
