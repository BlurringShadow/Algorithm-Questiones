// Created by BlurringShadow at 2020-11-16-上午 11:39

#pragma once
#include "../algorithm_utility/utils.h"

#include <array>

using std::array;

/*
 * Andrey thinks he is truly a successful developer,
 * but in reality he didn't know about the binary search algorithm until recently.
 * After reading some literature Andrey understood that this algorithm allows to quickly find a certain number x in an array.
 * For an array a indexed from zero, and an integer x the pseudocode of the algorithm is as follows:
 * Note that the elements of the array are indexed from zero, and the division is done in integers (rounding down).
 * Andrey read that the algorithm only works if the array is sorted.
 * However, he found this statement untrue, because there certainly exist unsorted arrays for which the algorithm find x!
 * Andrey wants to write a letter to the book authors,
 * but before doing that he must consider the permutations of size n such that the algorithm finds x in them.
 * A permutation of size n is an array consisting of n distinct integers between 1 and n in arbitrary order.
 * Help Andrey and find the number of permutations of size n which contain x at position pos and
 * for which the given implementation of the binary search algorithm finds x (returns true).
 * As the result may be extremely large, print the remainder of its division by 109+7.

 * Input
 * The only line of input contains integers n, x and pos (1≤x≤n≤1000, 0≤pos≤n−1) —
 * the required length of the permutation, the number to search, and the required position of that number, respectively.
 * 
 * Output
 * Print a single number — the remainder of the division of the number of valid permutations by 109+7.
 */
class binary_search final
{
public:
    static constexpr auto magic_division = 1000'000'007ull;

    using value_t = uint16_t;

    static constexpr value_t max_size = 1000;

    static constexpr const auto& factorials = []()
    {
        array<unsigned long long, max_size> fs{1};
        for(value_t i = 1; i < fs.size(); ++i) fs[i] = fs[i - 1] * i % magic_division;
        return fs;
    }();

    const value_t size;
    const value_t target;
    const value_t pos;

    void solve() const
    {
        unsigned long long larger_count = size - target, less_count = target - 1, ans = 1;

        for(value_t left = 0, right = size; left < right;)
        {
            const value_t middle = (left + right) / 2;

            if(middle <= pos)
            {
                left = middle + 1;
                if(middle != pos)
                {
                    ans = ans * less_count % magic_division;
                    --less_count;
                }
            }
            else
            {
                right = middle;

                ans = ans * larger_count % magic_division;
                --larger_count;
            }
        }

        cout << factorials[less_count + larger_count] * ans % magic_division << '\n';
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
        // ReSharper disable once CppRedundantParentheses
        , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        binary_search{
            get_from_stream<value_t>(is),
            get_from_stream<value_t>(is),
            get_from_stream<value_t>(is)
        }.solve();
    }
};
