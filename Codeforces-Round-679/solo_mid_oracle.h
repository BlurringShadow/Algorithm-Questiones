// Created by BlurringShadow at 2020-12-14-下午 9:24

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * Meka-Naruto plays a computer game.
 * His character has the following ability: given an enemy hero, deal a instant damage to him,
 * and then heal that enemy b health points at the end of every second,
 * for exactly c seconds, starting one second after the ability is used.
 * That means that if the ability is used at time t, the enemy's health decreases by a at time t,
 * and then increases by b at time points t+1, t+2, ..., t+c due to this ability.
 * The ability has a cooldown of d seconds, i. e.
 * if Meka-Naruto uses it at time moment t, next time he can use it is the time t+d.
 * Please note that he can only use the ability at integer points in time,
 * so all changes to the enemy's health also occur at integer times only.
 * 
 * The effects from different uses of the ability may stack with each other;
 * that is, the enemy which is currently under k spells gets k⋅b amount of heal this time.
 * Also, if several health changes occur at the same moment, they are all counted at once.
 * 
 * Now Meka-Naruto wonders if he can kill the enemy
 * by just using the ability each time he can(that is, every d seconds).
 * The enemy is killed if their health points become 0 or less.
 * Assume that the enemy's health is not affected in any way other than by Meka-Naruto's character ability.
 * What is the maximal number of health points the enemy can have so that Meka-Naruto is able to kill them?
 */
class solo_mid_oracle final
{
    using value_t = uint64_t;

    value_t damage_{};
    value_t heal_{};
    value_t duration_{};
    value_t cooling_{};

    [[nodiscard]] value_t solve() const noexcept
    {
        if(damage_ > heal_ * duration_) return 0;
        const auto max_count = damage_ / (cooling_ * heal_);
        return (1 + max_count) * (damage_ * 2 - cooling_ * heal_ * max_count) / 2;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, solo_mid_oracle& s)
    {
        const auto res = s.solve();
        if(res == 0) os << -1;
        else os << res;
        os << '\n';
        return os;
    }

    friend std::istream& operator>>(std::istream& is, solo_mid_oracle& v)
    {
        is >> v.damage_ >> v.heal_ >> v.duration_ >> v.cooling_;
        return is;
    }
};
