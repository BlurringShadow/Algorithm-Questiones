/*
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 * You may assume nums1 and nums2 cannot be both empty.
 */
#include <algorithm>
#include <iostream>
#include <vector>

template <typename IteratorType>
static auto impl(IteratorType first_begin,
                 const IteratorType first_end,
                 IteratorType second_begin,
                 const IteratorType second_end,
                 const size_t size


)
{
    auto is_first_end = first_begin == first_end;
    auto is_second_end = second_begin == second_end;
    const bool is_odd = size % 2;
    const auto mid_size = size / 2;

    size_t count = 0;
    auto current = is_first_end
                       ? *second_begin
                       : (is_second_end ? *first_begin : std::min(*first_begin, *second_begin));

    while (true)
    {
        while (first_begin != first_end && *first_begin <= current)
        {
            ++count;
            ++first_begin;
        }

        while (second_begin != second_end && *second_begin <= current)
        {
            ++count;
            ++second_begin;
        }

        is_first_end = first_begin == first_end;
        is_second_end = second_begin == second_end;

        if (is_first_end && is_second_end || count > mid_size)
            return current * 1.0;

        {
            auto&& next_current = is_first_end
                                      ? *second_begin
                                      : (is_second_end ? *first_begin : std::min(*first_begin, *second_begin));

            if (count == mid_size) return is_odd ? next_current : (next_current + current) / 2.0;

            current = std::move(next_current);
        }
    }
}

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    // ReSharper disable once CppInconsistentNaming
    double findMedianSortedArrays(const std::vector<int>& first, const std::vector<int>& second)
    {
        return impl(first.cbegin(), first.cend(), second.cbegin(), second.cend(), first.size() + second.size());
    }
};

int main()
{
    std::cout << Solution{}.findMedianSortedArrays({},
                                                   {1});
    return 0;
}
