/*
 * https://leetcode.com/problems/3sum/
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 * Find all unique triplets in the array which gives the sum of zero.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

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

    template<typename FuncType, typename SearchIteratorType, typename SumIteratorType>
    [[nodiscard]] static vector<vector<int>> sum_search(
        const FuncType tuple_create_func,
        const SearchIteratorType& search_cbegin,
        const SearchIteratorType& search_cend,
        SumIteratorType sum_up_cbegin,
        SumIteratorType sum_up_cend
    )
    {
        vector<vector<int>> res;

        if(sum_up_cbegin != sum_up_cend)
        {
            auto previous_first = -1;
            do
            {
                const auto first = *sum_up_cbegin;
                if(previous_first != first)
                {
                    auto previous_second = -1;
                    
                    for(auto&& sum_up_next = std::next(sum_up_cbegin); sum_up_next != sum_up_cend; ++sum_up_next)
                    {
                        const auto second = *sum_up_next;
                        if(previous_second != second)
                        {
                            bool is_equal{};
                            const auto sum = first + second;
                            if(std::lower_bound(
                                search_cbegin,
                                search_cend,
                                sum,
                                [&](const auto left, const auto right)
                                {
                                    if(left == right)
                                    {
                                        is_equal = true;
                                        return false;
                                    }
                                    return left < right;
                                }
                            ) == search_cend)
                            {
                                sum_up_cend = sum_up_next;
                                break;
                            }
                            if(is_equal) res.emplace_back(tuple_create_func(first, second, sum));

                            previous_second = second;
                        }
                    }

                    previous_first = first;
                }
                ++sum_up_cbegin;
            }
            while(sum_up_cbegin != sum_up_cend);
        }

        return res;
    }

public:
    // ReSharper disable once CppInconsistentNaming
    static vector<vector<int>> threeSum(const vector<int>& nums)
    {
        unsigned zero_count = 0;

        vector<int> natural_nums, negative_nums;

        natural_nums.reserve(nums.size());
        negative_nums.reserve(nums.size());
        for(const auto num : nums)
            if(num == 0)
            {
                if(zero_count == 0) natural_nums.emplace(natural_nums.cbegin(), 0);
                ++zero_count;
            }
            else if(num > 0)
                natural_nums.emplace(
                    std::upper_bound(natural_nums.cbegin(), natural_nums.cend(), num),
                    num
                );
            else
            {
                const auto reversed = -num;
                negative_nums.emplace(
                    std::upper_bound(negative_nums.cbegin(), negative_nums.cend(), reversed),
                    reversed
                );
            }

        const auto &natural_num_cbegin = natural_nums.cbegin(),
                   &natural_num_cend = natural_nums.cend(),
                   &negative_num_cbegin = negative_nums.cbegin(),
                   &negative_num_cend = negative_nums.cend();

        auto&& res = sum_search(
            [](const int sum_first, const int sum_second, const int sum)
            {
                return vector{-sum_first, -sum_second, sum};
            },
            natural_num_cbegin,
            natural_num_cend,
            negative_num_cbegin,
            negative_num_cend
        );

        // Special case handle for 3 '0's
        if(zero_count >= 3) res.push_back({0, 0, 0});


        {
            auto&& vec = sum_search(
                [](const int sum_first, const int sum_second, const int sum)
                {
                    return vector{sum_first, sum_second, -sum};
                },
                negative_num_cbegin,
                negative_num_cend,
                natural_num_cbegin,
                natural_num_cend
            );

            const auto size = res.size();
            const auto vec_size = vec.size();
            res.resize(size + vec_size);
            for(size_t i = 0; i < vec_size; ++i) res[i + size] = std::move(vec[i]);
        }

        return res;
    }
};

int main() noexcept
{
    try
    {
        for(const auto& element : Solution::threeSum({-1, 0, 1, 2, -1, -4}))
        {
            for(const auto value : element) std::cout << value << ' ';
            std::cout << '\n';
        }
    }
    catch(...) {}
    return 0;
}
