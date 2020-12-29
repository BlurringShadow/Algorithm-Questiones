// Created by BlurringShadow at 2020-12-17-上午 11:41

#pragma once

#include "../algorithm_utility/utils.h"

#include <numeric>

/*
 * You are given an array a of length 2n.
 * Consider a partition of array a into two subsequences p and q of length n each
 * (each element of array a should be in exactly one subsequence: either in p or in q).
 * Let's sort p in non-decreasing order, and q in non-increasing order,
 * we can denote the sorted versions by x and y, respectively.
 * Then the cost of a partition is defined as f(p,q)=∑ni=1|xi−yi|.
 * Find the sum of f(p,q) over all correct partitions of array a.
 * Since the answer might be too big, print its remainder modulo 998244353.
 */
class divide_and_sum final
{
    using value_t = uint32_t;
    using promoted_t = uint64_t;

    static constexpr promoted_t magic_modulo_ = 998244353;
    inline static auto&& inv_ = get_inverse_elements(magic_modulo_, value_t{1});

    value_t half_size_{};
    vector<value_t> nums_;

    static auto permutation(const value_t n, const value_t m)
    {
        const auto origin_size = inv_.size();
        if(origin_size < m)
        {
            inv_.resize(m);
            generate_inverse_elements(inv_, magic_modulo_, auto_cast{origin_size}, m);
        }

        return mod_permutation(inv_, n, m, magic_modulo_);
    }

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        const auto& begin = nums_.cbegin();
        const auto& mid = begin + half_size_;
        return inner_product(mid, nums_.cend(), begin, promoted_t{0}, plus<>{}, minus<>{}) % magic_modulo_ * 
            permutation(auto_cast{nums_.size()}, half_size_) % magic_modulo_;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, divide_and_sum& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, divide_and_sum& v)
    {
        is >> v.half_size_;
        v.nums_.resize(v.half_size_ * 2);
        for(auto& num : v.nums_) is >> num;
        sort(v.nums_.begin(), v.nums_.end());
        return is;
    }
};
