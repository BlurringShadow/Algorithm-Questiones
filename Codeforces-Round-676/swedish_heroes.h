// Created by BlurringShadow at 2020-11-06-上午 10:49

#pragma once
#include <array>

#include "../algorithm_utility/utils.h"

using std::array;

class swedish_heroes
{
public:
    using power_t = int64_t;

private:
    vector<power_t> powers_;

    template<typename T, typename U>
    static constexpr void set_max(T& a, U&& b) { if(b > a) a = std::forward<U>(b); }

public:
    explicit swedish_heroes(decltype(powers_) power) noexcept : powers_(std::move(power)) {}

    /*
     * General rule is (num_count + minus_count) % 3 = 1.
     * But sequences like '+-+-+...' is invalid, to avoid getting invalid sequences,
     * Create invalid sequences first, and turn them to valid sequence.
     * By adding new plus or minus nums.
     */
    void solve() const
    {
        const auto size = powers_.size();
        if(size == 1)
        {
            cout << powers_[0] << '\n';
            return;
        }

        static constexpr auto min = std::numeric_limits<power_t>::min();

        power_t invalid_sequence_sum = 0;
        array<power_t, 3> sequence_by_mod{min, min, min};
        for(size_t i = 0; i < size; i++)
        {
            array<power_t, 3> next_sequences_by_mod{min, min, min};
            
            {
                decltype(invalid_sequence_sum) target_sum;
                if(i % 2)
                {
                    target_sum = invalid_sequence_sum + powers_[i];
                    invalid_sequence_sum -= powers_[i];
                }
                else
                {
                    target_sum = invalid_sequence_sum - powers_[i];
                    invalid_sequence_sum += powers_[i];
                }
                next_sequences_by_mod[2] = target_sum;
            }

            for(size_t a = 0; a < 3; a++)
            {
                const auto pre_power = sequence_by_mod[a];
                if(pre_power != min)
                {
                    // number count add 1, minus count remain. mod result add 1.
                    set_max(next_sequences_by_mod[((a + 1) % 3)], pre_power + powers_[i]);

                    // number count add 1, minus count add. mod result add 2.
                    set_max(next_sequences_by_mod[((a + 2) % 3)], pre_power - powers_[i]);
                }
            }

            sequence_by_mod = next_sequences_by_mod;
        }

        cout << sequence_by_mod[1] << '\n';
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
    , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        vector<power_t> powers(get_from_stream<size_t>(is));
        for(auto& power : powers) is >> power;

        swedish_heroes{std::move(powers)}.solve();
    }
};
