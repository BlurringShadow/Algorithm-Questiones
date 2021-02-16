// Created by BlurringShadow at 2021-02-15-下午 11:14


#pragma once
#include "../algorithm_utility/utils.h"

class cat_cycle final
{
    uint64_t n_{}, hours_{};

    [[nodiscard]] auto solve() const
    {
        using namespace std;
        const auto [quo, rem] = std::div(n_, 2ll);
        const auto hours = hours_ - 1;

        return (rem == 0 ? hours : hours + hours / quo) % n_ + 1;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, cat_cycle& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, cat_cycle& v) { return is >> v.n_ >> v.hours_; }

    cat_cycle() noexcept {}
};
