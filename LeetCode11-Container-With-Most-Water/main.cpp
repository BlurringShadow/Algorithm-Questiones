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
        auto i = 0, j = static_cast<int>(height.size() - 1);
        auto max = 0;
        while(i < j)
        {
            decltype(i) next;
            decltype(max) product;

            if(height[i] < height[j])
            {
                product = height[i] * (j - i);
                for(next = i + 1; next < j && height[next] < height[j] && height[next] - height[i] < next - i; ++next);
                i = next;
            }
            else
            {
                product = height[j] * (j - i);
                for(next = j - 1; next > i && height[next] < height[i] && height[next] - height[j] < j - next; --next);
                j = next;
            }
            if(product > max) max = product;
        }
        return max;
    }
};

int main()
{
    std::cout << Solution::maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7});
    return 0;
}
