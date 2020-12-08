// Created by BlurringShadow at 2020-11-18-上午 9:24

#pragma once

#include "../algorithm_utility/utils.h"

/*
 * In this problem MEX of a certain array is the smallest positive integer not contained in this array.

 * Everyone knows this definition, including Lesha.
 * But Lesha loves MEX, so he comes up with a new problem involving MEX every day, including today.
 * 
 * You are given an array a of length n.
 * Lesha considers all the non-empty subarrays of the initial array and computes MEX for each of them.
 * Then Lesha computes MEX of the obtained numbers.
 * 
 * An array b is a subarray of an array a,
 * if b can be obtained from a by deletion of several (possible none or all) elements from the beginning and
 * several (possibly none or all) elements from the end.
 * In particular, an array is a subarray of itself.
 * 
 * Lesha understands that the problem is very interesting this time,
 * but he doesn't know how to solve it.
 * Help him and find the MEX of MEXes of all the subarrays!
 * 
 * Input
 * The first line contains a single integer n (1≤n≤105) — the length of the array.
 * 
 * The next line contains n integers a1,a2,…,an (1≤ai≤n) — the elements of the array.
 * 
 * Output
 * Print a single integer — the MEX of MEXes of all subarrays.
 */
class complicated_computations final
{
public:
    using uint = std::uint32_t;

    static constexpr std::pair<uint, uint> value_range = {1, static_cast<uint>(1e5)};

private:
    struct backward_linked_num
    {
        uint num = std::numeric_limits<uint>::max();
        uint next_pos = std::numeric_limits<uint>::max();
    };

    static uint comparer(const uint left, const uint right) { return std::max(left, right); }

    vector<backward_linked_num> nums_{};

    binary_indexed_tree<uint, decltype(&comparer)> positions_;

public:
    explicit complicated_computations(const vector<uint>& nums) noexcept : nums_(nums.size()),
        positions_(
            &comparer,
            [this, &nums]
            {
                const auto size = nums.size();
                vector<uint> next_pos(size, auto_cast{size});

                for(auto i = nums.size() - 1; i < size; --i)
                {
                    const auto num = nums[i];
                    nums_[i] = {num, next_pos[num - 1]};
                    next_pos[num - 1] = auto_cast{i};
                }

                return next_pos;
            }()
        ) {}

    void solve()
    {
        const uint num_size = auto_cast{nums_.size()};

        if(num_size == 1)
        {
            cout << std::min<uint>(nums_.front().num, 2);
            return;
        }

        const auto candidate_size = num_size + 1;
        vector<bool> candidates(candidate_size);

        {
            auto candidate_index = num_size;

            for(auto pos = num_size; candidate_index > 0; --candidate_index, pos = positions_[candidate_index])
            {
                if(positions_.get_range(candidate_index - 1) < pos) candidates[candidate_index] = true;
                if(pos != num_size)
                {
                    candidates.front() = true;
                    --candidate_index;
                    break;
                }
            }

            for(; candidate_index > 0; --candidate_index)
                if(positions_.get_range(candidate_index - 1) < positions_[candidate_index])
                    candidates[candidate_index] = true;
        }

        for(uint i = 0; i < num_size; ++i)
        {
            const auto [num, next_pos] = nums_[i];
            auto&& candidate_flag = candidates[num - 1];

            positions_.update(num - 1, next_pos);

            if(!candidate_flag && is_between(num, {2}, static_cast<uint>(candidates.size())))
            {
                // [i, max_pos] contains the all num from 1 to num - 1
                const auto max_pos = positions_.get_range(num - 2);

                if(max_pos < next_pos) candidate_flag = true;
                else if(max_pos == num_size) candidates.resize(max_pos);
            }
        }

        const auto& cbegin = candidates.cbegin();
        cout << std::find(cbegin, candidates.cend(), false) - cbegin + 1 << '\n';
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
    , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        vector<uint> nums(get_from_stream<uint>(is));
        for(auto& num : nums) is >> num;

        complicated_computations{nums}.solve();
    }
};
