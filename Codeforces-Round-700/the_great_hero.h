// Created by BlurringShadow at 2021-03-11-下午 9:02


#pragma once

#include "../algorithm_utility/utils.h"

#include <numeric>

class the_great_hero final
{
    struct property
    {
        uint64_t attack{};
        uint64_t health{};
    };

    property hero_prop_;
    vector<property> monsters_prop_;

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        uint64_t max_single_damage = 0;
        const auto& costs = [&, this]
        {
            vector<uint64_t> vec(monsters_prop_.size());

            for(size_t i = 0; i < vec.size(); ++i)
            {
                const auto& monster = monsters_prop_[i];
                vec[i] = (monster.health + hero_prop_.attack - 1) / 
                    hero_prop_.attack * monster.attack;

                set_if_greater(max_single_damage, monsters_prop_[i].attack);
            }

            return vec;
        }();
        return hero_prop_.health + max_single_damage >
            std::accumulate(costs.cbegin(), costs.cend(), uint64_t{});
    }

public:
    friend std::ostream& operator<<(std::ostream& os, the_great_hero& s)
    {
        return os << (s.solve() ? "YES" : "NO") << '\n';
    }

    friend std::istream& operator>>(std::istream& is, the_great_hero& v)
    {
        {
            auto& hero = v.hero_prop_;
            is >> hero.attack >> hero.health;
        }
        {
            auto& monsters = v.monsters_prop_;
            monsters.resize(get_from_stream(is));
            for(auto& prop : monsters) is >> prop.attack;
            for(auto& prop : monsters) is >> prop.health;
        }
        return is;
    }
};

using problem_t = the_great_hero;
