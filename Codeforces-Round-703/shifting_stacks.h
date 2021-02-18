// Created by BlurringShadow at 2021-02-18-下午 10:35

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * You have n stacks of blocks.
 * The i-th stack contains h_i blocks and it's height is the number of blocks in it.
 * In one move you can take a block from the i-th stack (if there is at least one block)
 * and put it to the (i+1)-th stack.
 * Can you make the sequence of heights strictly increasing?
 * Note that the number of stacks always remains n:
 * stacks don't disappear when they have  blocks.
 */
class shifting_stacks final
{
    vector<uint64_t> stacks_;

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        auto delta = stacks_.front();
        for(size_t i = 1; i < stacks_.size(); ++i)
        {
            const auto new_stack = stacks_[i] + delta;
            if(new_stack < i) return false;
            delta = new_stack - i;
        }

        return true;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, shifting_stacks& s)
    {
        return os << (s.solve() ? "yes\n" : "no\n");
    }

    friend std::istream& operator>>(std::istream& is, shifting_stacks& v)
    {
        auto& stacks = v.stacks_;
        stacks.resize(get_from_stream(is));
        for(auto& stack : stacks) is >> stack;
        return is;
    }

    shifting_stacks() noexcept {}
};

using problem_t = shifting_stacks;
