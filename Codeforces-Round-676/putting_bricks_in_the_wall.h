// Created by BlurringShadow at 2020-11-01-下午 5:52

#pragma once

#include "../algorithm_utility/utils.h"

#include <array>
#include <bitset>

/*
 * Pink Floyd are pulling a prank on Roger Waters. They know he doesn't like walls, he wants to be able to walk freely,
 * so they are blocking him from exiting his room which can be seen as a grid.
 * Roger Waters has a square grid of size n×n and
 * he wants to traverse his grid from the upper left (1,1) corner to the lower right corner (n,n).
 * Waters can move from a square to any other square adjacent by a side,
 * as long as he is still in the grid. Also except for the cells (1,1) and (n,n) every cell has a value 0 or 1 in it.
 * Before starting his traversal he will pick either a 0 or a 1 and
 * will be able to only go to cells values in which are equal to the digit he chose.
 * The starting and finishing cells (1,1) and (n,n) are exempt from this rule,
 * he may go through them regardless of picked digit.
 * Because of this the cell (1,1) takes value the letter 'S' and the cell (n,n) takes value the letter 'F'.
 * The rest of the band (Pink Floyd) wants Waters to not be able to do his traversal,
 * so while he is not looking they will invert at most two cells in the grid (from 0 to 1 or vice versa).
 * They are afraid they will not be quick enough and asked for your help in choosing the cells.
 * Note that you cannot invert cells (1,1) and (n,n).
 * We can show that there always exists a solution for the given constraints.
 * Also note that Waters will pick his digit of the traversal after the band has changed his grid,
 * so he must not be able to reach (n,n) no matter what digit he picks.
 *
 * Input
 * Each test contains multiple test cases.
 * The first line contains the number of test cases t (1≤t≤50).
 * Description of the test cases follows.
 * The first line of each test case contains one integers n (3≤n≤200).
 * The following n lines of each test case contain the binary grid,
 * square (1,1) being colored in 'S' and square (n,n) being colored in 'F'.
 * The sum of values of n doesn't exceed 200.
 *
 * Output
 * For each test case output on the first line an integer c (0≤c≤2)  — the number of inverted cells.
 * In i-th of the following c lines, print the coordinates of the i-th cell you inverted.
 * You may not invert the same cell twice. Note that you cannot invert cells (1,1) and (n,n).
 */
class putting_bricks_in_the_wall
{
public:
    using grid_size_t = unsigned short;

private:
    size_t grid_size_;
    std::array<bool, 4> bits_;

public:
    constexpr putting_bricks_in_the_wall(const size_t grid_size, const decltype(bits_) grid) noexcept:
        grid_size_(grid_size),
        bits_(grid) {}

    void solve() const
    {
        console_output_buffer_binder binder;
        unsigned short flip_count = 0;
        bool flag;

        if(bits_[0] == bits_[1])
        {
            flag = bits_[0];
            if(bits_[2] == flag)
            {
                cout << grid_size_ - 1 << ' ' << grid_size_ << '\n';
                ++flip_count;
            }
        }
        else
        {
            flag = bits_[2];
            if(bits_[0] == flag)
            {
                cout << 1 << ' ' << 2 << '\n';
                ++flip_count;
            }
            if(bits_[1] == flag)
            {
                cout << 2 << ' ' << 1 << '\n';
                ++flip_count;
            }

            flag = !flag;
        }

        if(bits_[3] == flag)
        {
            cout << grid_size_ << ' ' << grid_size_ - 1 << '\n';
            ++flip_count;
        }

        {
            [[maybe_unused]] const auto& scope = binder.scope_add_front();
            cout << flip_count << '\n';
        }
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
    , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        std::array<bool, 4> bits{};

        for(auto test_count = get_from_stream<unsigned short>(is); test_count > 0; --test_count)
        {
            const auto grid_size = get_from_stream<grid_size_t>(is);

            [[maybe_unused]] auto dummy = get_from_stream<char>(is);

            bits[0] = is.get() > '0';

            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bits[1] = get_from_stream<char>(is) > '0';

            for(auto i = grid_size; i > 2; --i) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            is.unget().unget();
            bits[2] = is.get() > '0';

            is >> dummy;
            is.ignore(grid_size - 3);
            bits[3] = is.get() > '0';

            is.ignore();
            putting_bricks_in_the_wall{grid_size, bits}.solve();
        }
    }
};
