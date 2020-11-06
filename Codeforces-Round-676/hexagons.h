// Created by BlurringShadow at 2020-11-05-下午 5:38

#pragma once
#include "../algorithm_utility/utils.h"

#include <array>

class hexagons
{
public:
    using coordinate_t = int32_t;
    using cost_t = uint64_t;

private:
    const coordinate_t x_, y_;
    const std::array<cost_t, 6> costs_;
public:
    hexagons(
        const coordinate_t x,
        const coordinate_t y,
        decltype(costs_)& costs
    ) noexcept: x_(x), y_(y), costs_(costs) {}

    void solve() const noexcept
    {
        const auto [x1, x2] = x_ >= 0 ?
            std::pair<cost_t, cost_t>{costs_[5] * x_, costs_[0] * x_} :
            std::pair<cost_t, cost_t>{costs_[2] * -x_, costs_[3] * -x_};

        const auto [y1, y2] = y_ >= 0 ?
            std::pair<cost_t, cost_t>{costs_[1] * y_, costs_[0] * y_} :
            std::pair<cost_t, cost_t>{costs_[4] * -y_, costs_[3] * -y_};

        const auto diff = x_ - y_;

        const auto [diff1, diff2] = diff >= 0 ?
            std::pair<cost_t, cost_t>{costs_[5] * diff, costs_[4] * diff} :
            std::pair<cost_t, cost_t>{costs_[2] * -diff, costs_[1] * -diff};

        cout << std::min(std::min(x1 + y1, diff1 + y2), diff2 + x2) << '\n';
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
        {
            auto x = get_from_stream<coordinate_t>(is), y = get_from_stream<coordinate_t>(is);
            std::array<cost_t, 6> costs;
            for(auto& cost : costs)
                is >> cost;

            hexagons{x, y, costs}.solve();
        }
    }
};
