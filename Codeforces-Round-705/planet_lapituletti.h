// Created by BlurringShadow at 2021-03-06-下午 11:13

#pragma once
#include "../algorithm_utility/utils.h"

#include <charconv>

class planet_lapituletti final
{
    static constexpr auto invalid_mirrored_ = std::numeric_limits<unsigned>::max();

    static constexpr auto mirrored_map_ = []
    {
        constexpr auto invalid_single_mirrored_ = std::numeric_limits<uint8_t>::max();

        constexpr auto single_mirrored_nums = [=]
        {
            std::array<uint8_t, 10> nums{};

            for(size_t i = 3; i < nums.size(); ++i) nums[i] = invalid_single_mirrored_;
            nums[1] = 1;
            nums[2] = 5;
            nums[5] = 2;
            nums[8] = 8;

            return nums;
        }();
        std::array<unsigned, 100> map{};

        for(size_t i = 1; i < map.size(); ++i) map[i] = invalid_mirrored_;

        for(uint8_t i = 0; i < single_mirrored_nums.size(); ++i)
        {
            const auto& mirrored1 = single_mirrored_nums[i];
            if(mirrored1 != invalid_single_mirrored_)
                for(uint8_t j = 0; j < single_mirrored_nums.size(); ++j)
                {
                    const auto& mirrored2 = single_mirrored_nums[j];
                    if(mirrored2 != invalid_mirrored_)
                        map[i * 10 + j] = mirrored1 + mirrored2 * 10;
                }
        }

        return map;
    }();

    unsigned hours_per_day_{}, min_per_hours_{};
    unsigned hour_{}, min_{};

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        auto hour = hour_;
        auto min = min_;

        while(true)
        {
            for(; hour < hours_per_day_; ++hour)
            {
                const auto& mirrored_hour = mirrored_map_[hour];
                if(mirrored_hour != invalid_mirrored_ && mirrored_hour < min_per_hours_)
                    for(; min < min_per_hours_; ++min)
                    {
                        const auto& mirrored_min = mirrored_map_[min];
                        if(mirrored_hour != invalid_mirrored_ && mirrored_min < hours_per_day_)
                            return pair{hour, min};
                    }

                min = 0;
            }
            hour = 0;
        }
    }

public:
    friend std::ostream& operator<<(std::ostream& os, planet_lapituletti& s)
    {
        const auto [hour, min] = s.solve();
        if(hour < 10) os << '0';
        os << hour << ':';
        if(min < 10) os << '0';
        return os << min << '\n';
    }

    friend std::istream& operator>>(std::istream& is, planet_lapituletti& v)
    {
        is >> v.hours_per_day_ >> v.min_per_hours_;

        const string& time = get_from_stream(is);
        std::from_chars(time.data(), time.data() + 2, v.hour_);
        std::from_chars(time.data() + 3, time.data() + 5, v.min_);
        return is;
    }

    planet_lapituletti() noexcept {}
};

using problem_t = planet_lapituletti;
