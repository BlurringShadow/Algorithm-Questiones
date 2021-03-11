// Created by BlurringShadow at 2021-03-11-下午 10:08

#pragma once

#include "../algorithm_utility/utils.h"

class searching_local_minimum final
{
    std::istream* is_;

    uint32_t size_;

    [[nodiscard]] uint32_t query(const uint32_t i) const
    {
        if(i > 0 && i <= size_)
        {
            (cout << "? " << i << '\n').flush();
            return get_from_stream(*is_);
        }
        return size_ + 1;
    }
 

    [[nodiscard]] auto solve() const
    {
        using namespace std;
        uint32_t l = 1, r = size_;
        while(l != r)
        {
            const auto m = (l + r) / 2;
            if(query(m) < query(m + 1)) r = m;
            else l = m + 1;
        }
        return "! " + std::to_string(l);
    }

public:
    friend std::ostream& operator<<(std::ostream& os, searching_local_minimum& s)
    {
        return os << s.solve() << '\n';
    }

    friend std::istream& operator>>(std::istream& is, searching_local_minimum& v)
    {
        v.is_ = &is;
        return is >> v.size_;
    }
};

using problem_t = searching_local_minimum;
