// Created by BlurringShadow at 2021-02-15-下午 10:36


#pragma once
#include "../algorithm_utility/utils.h"

/*
 * n heroes fight against each other in the Arena. Initially, the i-th hero has level ai.
 * Each minute, a fight between two different heroes occurs.
 * These heroes can be chosen arbitrarily
 * (it's even possible that it is the same two heroes that were fighting during the last minute).
 * When two heroes of equal levels fight, nobody wins the fight.
 * When two heroes of different levels fight, the one with the higher level wins,
 * and his level increases by 1.
 * The winner of the tournament is the first hero that wins in at least 100500 fights
 * (note that it's possible that the tournament lasts forever
 * if no hero wins this number of fights, then there is no winner).
 * A possible winner is a hero such that there exists a sequence of fights
 * that this hero becomes the winner of the tournament.
 * Calculate the number of possible winners among n heroes.
 */
class arena final
{
    vector<uint32_t> hero_levels_;

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        const auto& sorted_levels = [this]()
        {
            auto levels = hero_levels_;
            sort(levels.begin(), levels.end());
            return levels;
        }();
        const auto res = sorted_levels.cend() - adjacent_find(
            sorted_levels.cbegin(),
            sorted_levels.cend(),
            [](const auto left, const auto right) { return right > left; }
        );

        return res > 0 ? res - 1 : 0;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, arena& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, arena& v)
    {
        auto& levels = v.hero_levels_;
        levels.resize(get_from_stream(is));
        for(auto& level : levels) is >> level;
        return is;
    }
   
};
