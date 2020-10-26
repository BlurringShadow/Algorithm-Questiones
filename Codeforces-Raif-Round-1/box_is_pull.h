// Created by BlurringShadow at 2020-10-26-下午 1:49

#pragma once
#include "../algorithm_utility/utils.h"

class box_is_pull
{
    struct coordinate
    {
        int x;
        int y;
    };

    coordinate start_;
    coordinate end_;
public:
    constexpr box_is_pull(const coordinate start, const coordinate end) noexcept : start_(start), end_(end) {}

    void solve() const noexcept
    {
        const auto dis_x = std::abs(end_.x - start_.x);
        const auto dis_y = std::abs(end_.y - start_.y);

        if(dis_x == 0) cout << dis_y;
        else if(dis_y == 0) cout << dis_x;
        else cout << dis_x + dis_y + 2;
        cout << '\n';
    }

    static void create_from_input()
    {
        size_t size;
        cin >> size;

        for(decltype(size) i = 0; i < size; ++i)
        {
            coordinate start{};
            coordinate end{};

            cin >> start.x;
            cin >> start.y;
            cin >> end.x;
            cin >> end.y;

            box_is_pull{start, end}.solve();
        }
    }
};
