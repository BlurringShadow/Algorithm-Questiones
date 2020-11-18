// Created by BlurringShadow at 2020-11-17-上午 11:02

#pragma once
#include "../algorithm_utility/utils.h"

#include <algorithm>

/*
 * Bandits appeared in the city! One of them is trying to catch as many citizens as he can.
 * The city consists of n squares connected by n−1 roads in such a way that
 * it is possible to reach any square from any other square.
 * The square number 1 is the main square.
 *
 * After Sunday walk all the roads were changed to one-way roads in such a way that
 * it is possible to reach any square from the main square.
 * 
 * At the moment when the bandit appeared on the main square there were ai citizens on the i-th square.
 * Now the following process will begin.
 * First, each citizen that is currently on a square with some outgoing one-way roads
 * chooses one of such roads and moves along it to another square.
 * Then the bandit chooses one of the one-way roads outgoing from the square he is located and moves along it.
 * The process is repeated until the bandit is located on a square with no outgoing roads.
 * The bandit catches all the citizens on that square.
 * 
 * The bandit wants to catch as many citizens as possible;
 * the citizens want to minimize the number of caught people.
 * The bandit and the citizens know positions of all citizens at any time,
 * the citizens can cooperate. If both sides act optimally, how many citizens will be caught?
 * 
 * Input
 * The first line contains a single integer n — the number of squares in the city (2≤n≤2⋅105).
 * 
 * The second line contains n−1 integers p2,p3…pn
 * meaning that there is a one-way road from the square pi to the square i (1≤pi<i).
 * 
 * The third line contains n integers a1,a2,…,an — the number of citizens on each square initially (0≤ai≤109).
 * 
 * Output
 * Print a single integer — the number of citizens the bandit will catch if both sides act optimally.
 */
class bandit_in_a_city final
{
public:
    using square_count_t = std::uint32_t;
    using people_count_t = std::uint64_t;

private:
    static constexpr people_count_t invalid_people_size_ = std::numeric_limits<people_count_t>::max();

    vector<vector<square_count_t>> paths_;
    vector<people_count_t> people_vec_;

public:
    bandit_in_a_city(decltype(paths_) paths, decltype(people_vec_) people_vec) noexcept :
        paths_(std::move(paths)),
        people_vec_(std::move(people_vec)) {}

    void solve() const noexcept
    {
        auto people_sums = people_vec_;
        vector<square_count_t> leaves_counts(people_vec_.size());
        people_count_t ans = 0;

        // input limitation ensure that parent index is larger than children's index.
        for(auto square_index = paths_.size() - 1; square_index < paths_.size(); --square_index)
        {
            const auto& destinations = paths_[square_index];
            auto& leaves_count = leaves_counts[square_index];
            if(destinations.empty()) leaves_count = 1;
            else 
                for(const auto destination : destinations)
                {
                    leaves_count += leaves_counts[destination];
                    people_sums[square_index] += people_sums[destination];
                }

            set_if_greater(ans, (people_sums[square_index] + leaves_count - 1) / leaves_count);
        }

        cout << ans << '\n';
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
        // ReSharper disable once CppRedundantParentheses
        , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        vector<people_count_t> people_vec(get_from_stream<square_count_t>(is));
        vector<vector<square_count_t>> paths(people_vec.size());

        for(square_count_t i = 0; i < paths.size() - 1; ++i) paths[get_from_stream<square_count_t>(is) - 1].emplace_back(i + 1);

        for(auto& people_count : people_vec) is >> people_count;

        bandit_in_a_city{std::move(paths), std::move(people_vec)}.solve();
    }
};
