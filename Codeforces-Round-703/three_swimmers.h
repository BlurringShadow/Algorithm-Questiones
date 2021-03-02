// Created by BlurringShadow at 2021-02-23-下午 6:46


#pragma once

#include "../algorithm_utility/utils.h"

class three_swimmers final
{
    uint64_t p_{};
    array<uint64_t, 3> swimming_time_{};

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        auto swimming_time = swimming_time_;

        {
            auto min = numeric_limits<uint64_t>::max();
            for(auto time : swimming_time) if(time >= p_ && min > time) min = time;

            if(numeric_limits<uint64_t>::max() > min) return min - p_;
        }

        for(;;)
        {
            auto&& min = min_element(swimming_time.begin(), swimming_time.end());
            *min += swimming_time_[min - swimming_time.cbegin()];

            if(*min >= p_) return *min - p_;
        }
    }

public:
    friend std::ostream& operator<<(std::ostream& os, three_swimmers& s)
    {
        return os << s.solve() << '\n';
    }

    friend std::istream& operator>>(std::istream& is, three_swimmers& v)
    {
        is >> v.p_;
        for(auto& time : v.swimming_time_)
        {
            is >> time;
        }
        return is;
    }
};

using problem_t = three_swimmers;
