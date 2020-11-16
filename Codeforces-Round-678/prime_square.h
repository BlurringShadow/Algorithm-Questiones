// Created by BlurringShadow at 2020-11-16-上午 10:15

#pragma once
#include "../algorithm_utility/utils.h"

#include <array>

using std::array;

/*
 * Sasha likes investigating different math objects, for example, magic squares.
 * But Sasha understands that magic squares have already been studied by hundreds of people,
 * so he sees no sense of studying them further.
 * Instead, he invented his own type of square — a prime square.
 *
 * A square of size n×n is called prime if the following three conditions are held simultaneously:
 * 
 * all numbers on the square are non-negative integers not exceeding 105;
 * there are no prime numbers in the square;
 * sums of integers in each row and each column are prime numbers.
 * Sasha has an integer n. He asks you to find any prime square of size n×n.
 * Sasha is absolutely sure such squares exist, so just help him!
 *
 * Input
 * The first line contains a single integer t (1≤t≤10) — the number of test cases.
 * Each of the next t lines contains a single integer n (2≤n≤100) — the required size of a square.
 *
 * Output
 * For each test case print n lines, each containing n integers — the prime square you built.
 * If there are multiple answers, print any.
 */
class prime_square final
{
    unsigned short square_size_;

public:
    explicit prime_square(const decltype(square_size_) square_size) noexcept: square_size_(square_size) {}

    void solve() const
    {
        vector<vector<unsigned char>> square(square_size_, vector<unsigned char>(square_size_, '0'));

        for(unsigned short i = square_size_ - 1; i < square_size_; --i)
            square[i][i] = square[i][square_size_ - 1 - i] = '1';

        if(square_size_ % 2) square[square_size_ / 2][0] = square[0][square_size_ / 2] = '1';


        for(const auto& row : square)
        {
            for(const auto v : row) cout << v << ' ';
            cout << '\n';
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
        for(auto i = get_from_stream<unsigned short>(is); i > 0; --i)
            prime_square{get_from_stream<unsigned short>(is)}.solve();
    }
};
