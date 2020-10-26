// Created by BlurringShadow at 2020-10-26-下午 1:53

#pragma once
#include <unordered_set>
#include "../algorithm_utility/utils.h"

using std::pair;
using std::unordered_set;

/*
 * In the snake exhibition, there are n rooms (numbered 0 to n−1) arranged in a circle,
 * with a snake in each room. The rooms are connected by n conveyor belts,
 * and the i-th conveyor belt connects the rooms i and (i+1) mod n.
 * rooms 0 and 1, 1 and 2, …, n−2 and n−1, n−1 and 0 are connected with conveyor belts.
 * The i-th conveyor belt is in one of three states:
 * If it is clockwise, snakes can only go from room i to (i+1)mod n.
 * If it is anticlockwise, snakes can only go from room (i+1)mod n to i.
 * If it is off, snakes can travel in either direction.
 * Above is an example with 4 rooms, where belts 0 and 3 are off, 1 is clockwise, and 2 is anticlockwise.
 * Each snake wants to leave its room and come back to it later.
 * A room is returnable if the snake there can leave the room, and later come back to it using the conveyor belts.
 * How many such returnable rooms are there?
 *
 * Input
 * Each test contains multiple test cases.
 * The first line contains a single integer t (1≤t≤1000): the number of test cases.
 * The first line of each test case description contains a single integer n (2≤n≤300000): the number of rooms.
 * The next line of each test case description contains a string s of length n, consisting of only '<', '>' and '-'.
 * If si= '>', the i-th conveyor belt goes clockwise.
 * If si= '<', the i-th conveyor belt goes anticlockwise.
 * If si= '-', the i-th conveyor belt is off.
 * It is guaranteed that the sum of n among all test cases does not exceed 300000.
 * Output
 * For each test case, output the number of returnable rooms.
 *
 * example
 * input:
 * 4 // test case num
 * 4 // num of room
 * -><- // states of belts
 * 5
 * >>>>>
 * 3
 * <--
 * 2
 * <>
 * output:
 * 3
 * 5
 * 3
 * 0
 */
class belted_rooms
{
    enum class belt_state
    {
        // ">"
        clockwise,
        // "<"
        anticlockwise,
        // "-"
        off
    };

    vector<belt_state> states_;

    [[nodiscard]] pair<bool, vector<size_t>> is_semi_returnable() const noexcept
    {
        vector<size_t> indices_of_off_state;
        size_t i;
        auto semi_returnable = true;
        indices_of_off_state.reserve(states_.size());

        {
            auto is_all_clock_wise = true, is_all_anti_clock_wise = true;
            for(i = 0; i < states_.size(); ++i)
            {
                switch(states_[i])
                {
                case belt_state::clockwise: is_all_anti_clock_wise = false;
                    if(!is_all_clock_wise) goto end_label;
                    break;
                case belt_state::anticlockwise: is_all_clock_wise = false;
                    if(!is_all_anti_clock_wise) goto end_label;
                    break;
                case belt_state::off: indices_of_off_state.emplace_back(i);
                    break;
                end_label:
                    semi_returnable = false;
                }
                if(!semi_returnable) break;
            }
        }

        for(; i < states_.size(); ++i) if(states_[i] == belt_state::off) indices_of_off_state.emplace_back(i);

        return {semi_returnable, indices_of_off_state};
    }

public:
    void solve() const
    {
        const auto& [semi_returnable, indices_of_off_state] = is_semi_returnable();
        if(semi_returnable)
        {
            cout << states_.size() << '\n';
            return;
        }

        unordered_set<size_t> returnable_room_indices(states_.size());
        for(const auto index : indices_of_off_state)
        {
            returnable_room_indices.insert(index);
            returnable_room_indices.insert((index + 1) % states_.size());
        }

        cout << returnable_room_indices.size() << '\n';
    }

    static void create_from_input()
    {
        size_t size;
        cin >> size;

        for(decltype(size) i = 0; i < size; ++i)
        {
            vector<belt_state> states;
            {
                size_t room_num{};
                cin >> room_num;
                states.resize(room_num);
            }

            for(auto& state : states)
            {
                char input_state;
                cin >> input_state;
                switch(input_state)
                {
                case '>': state = belt_state::clockwise;
                    break;
                case '<': state = belt_state::anticlockwise;
                    break;
                case '-': state = belt_state::off;
                    break;
                default: ;
                }
            }

            belted_rooms{std::move(states)}.solve();
        }
    }

    explicit belted_rooms(vector<belt_state> belt_states) : states_(std::move(belt_states)) {}
};
