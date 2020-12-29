// Created by BlurringShadow at 2020-12-15-下午 5:58

#pragma once
#include "../algorithm_utility/utils.h"

class elimination final
{
    int a_{}, b_{}, c_{}, d_{};

    auto solve() const noexcept
    {
        using namespace std;
        return max(a_ + b_, c_ + d_);
    }

public:
    friend std::ostream& operator<<(std::ostream& os, elimination& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, elimination& v) { return is >> v.a_ >> v.b_ >> v.c_ >> v.d_; }
};
