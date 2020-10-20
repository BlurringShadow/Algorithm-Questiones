#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <optional>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::cin;
using std::array;
using std::stack;
using std::size_t;
using std::string;
using std::string_view;
using std::initializer_list;
using std::vector;
using std::uint8_t;
using std::pair;
using std::optional;
using std::unordered_set;
using std::unordered_map;

[[maybe_unused]] static const auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    return 0;
}();

// Problem A
class rabbit_move_box
{
    struct coordinate
    {
        int x;
        int y;
    };

    coordinate start_;
    coordinate end_;
public:
    constexpr rabbit_move_box(const coordinate start, const coordinate end) noexcept : start_(start), end_(end) {}

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

            rabbit_move_box{start, end}.solve();
        }
    }
};

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
class snake_circle_rooms
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

            snake_circle_rooms{std::move(states)}.solve();
        }
    }

    explicit snake_circle_rooms(vector<belt_state> belt_states) : states_(std::move(belt_states)) {}
};

/*
 * Zookeeper is playing a game.
 * In this game, Zookeeper must use bombs to bomb a string that consists of letters 'A' and 'B'.
 * He can use bombs to bomb a substring which is either "AB" or "BB".
 * When he bombs such a substring, the substring gets deleted from the string
 * and the remaining parts of the string get concatenated.
 * For example, Zookeeper can use two such operations: AABABBA → AABBA → AAA.
 * Zookeeper wonders what the shortest string he can make is.
 * Can you help him find the length of the shortest string?
 *
 * Input:
 * Each test contains multiple test cases.
 * The first line contains a single integer t (1≤t≤20000)  — the number of test cases.
 * The description of the test cases follows.
 * Each of the next t lines contains a single test case each,
 * consisting of a non-empty string s: the string that Zookeeper needs to bomb.
 * It is guaranteed that all symbols of s are either 'A' or 'B'.
 * It is guaranteed that the sum of |s| (length of s) among all test cases does not exceed 2105.
 * Output:
 * For each test case, print a single integer: the length of the shortest string that Zookeeper can make.
 */
class bomb_string
{
    string_view str_;
public:
    explicit constexpr bomb_string(const string_view str) noexcept : str_(str) {}

    void solve() const
    {
        size_t size = 0;
        for(const auto c : str_)
            if(c == 'B' && size > 0) --size;
            else ++size;
        cout << size << '\n';
    }

    static void create_from_input()
    {
        size_t size;
        cin >> size;

        for(decltype(size) i = 0; i < size; ++i)
        {
            string str;
            cin >> str;
            bomb_string{std::move(str)}.solve();
        }
    }
};

/*
 * To improve the boomerang throwing skills of the animals, Zookeeper has set up an n×n grid with some targets,
 * where each row and each column has at most 2 targets each.
 * The rows are numbered from 1 to n from top to bottom, and the columns are numbered from 1 to n from left to right.
 * For each column, Zookeeper will throw a boomerang from the bottom of the column (below the grid) upwards.
 * When the boomerang hits any target, it will bounce off,
 * make a 90 degree turn to the right and fly off in a straight line in its new direction.
 * The boomerang can hit multiple targets and does not stop until it leaves the grid.
 * The boomerang in column i hits exactly ai targets before flying out of the grid. It is known that ai≤3.
 * However, Zookeeper has lost the original positions of the targets.
 * Thus, he asks you to construct a valid configuration of targets that matches the number of hits for each column,
 * or tell him that no such configuration exists. If multiple valid configurations exist, you may print any of them.
 * 
 * Input
 * The first line contains a single integer n (1≤n≤105).
 * The next line contains n integers a1,a2,…,an (0≤ai≤3).
 * Output
 * If no configuration of targets exist, print −1.
 * Otherwise, on the first line print a single integer t (0≤t≤2n): the number of targets in your configuration.
 * 
 * Then print t lines with two spaced integers each per line. Each line should contain two integers r and c (1≤r,c≤n),
 * where r is the target's row and c is the target's column. All targets should be different.
 * Every row and every column in your configuration should have at most two targets each.
 * 
 * Examples
 * input
 * 6
 * 2 0 3 0 1 1
 * output
 * 5
 * 2 1
 * 2 5
 * 3 3
 * 3 6
 * 5 6
 */
class bouncing_boomerangs
{
public:
    using bounce_count_t = uint8_t;

private:
    vector<bounce_count_t> bounce_times_;

    static void generate_output(string& output, const size_t r, const size_t c)
    {
        const auto left = std::to_string(r + 1);
        const auto right = std::to_string(c + 1);
        output.reserve(output.size() + 2 + left.size() + right.size());
        output.append(left).append(" ").append(right).append("\n");
    }

    [[nodiscard]] pair<bool, vector<vector<size_t>>> find_chains() const
    {
        const auto bounce_times_count = bounce_times_.size();
        vector<vector<size_t>> completed_chains;
        vector<vector<size_t>> chains;
        for(size_t i = 0; i < bounce_times_count; ++i)
        {
            const auto current_bounce_count = bounce_times_[i];
            if(current_bounce_count == 0) continue;

            const auto& chain_it = std::find_if(
                chains.begin(),
                chains.end(),
                [current_bounce_count, &bounce_times = bounce_times_](decltype(chains)::const_reference chain)
                {
                    const auto last_bounce_count = bounce_times[chain.back()];
                    return current_bounce_count == 3 ? last_bounce_count == 3 : current_bounce_count < last_bounce_count;
                }
            );
            if(chain_it == chains.cend())
            {
                if(current_bounce_count == 1) completed_chains.emplace_back(initializer_list<size_t>{1}); // chain is ended by 1
                else chains.emplace_back(initializer_list<size_t>{i});
            }
            else
            {
                auto& chain = *chain_it;
                chain.emplace_back(i);

                // chain is ended by 1
                if(current_bounce_count == 1)
                {
                    completed_chains.emplace_back(std::move(chain));
                    chains.erase(chain_it);
                }
            }
        }

        return {chains.empty(), completed_chains};
    }

    static void place_boomerang(string& output, const size_t r, const size_t c, size_t& count)
    {
        generate_output(output, r, c);
        ++count;
    }

    [[nodiscard]] string place_boomerang_for_chains(const vector<vector<size_t>>& chains) const
    {
        string output = "\n";
        size_t available_row_start_index = 0;
        size_t boomerang_count = 0;
        for(const auto& chain : chains)
        {
            bounce_count_t remain = 1;
            for(const auto col : chain)
            {
                place_boomerang(output, available_row_start_index, col, boomerang_count);

                --remain;
                if(remain > 0) place_boomerang(output, ++available_row_start_index, col, boomerang_count);

                remain = bounce_times_[col] - 1;
            }

            ++available_row_start_index;
        }

        return std::to_string(boomerang_count) + output;
    }

public:
    explicit bouncing_boomerangs(decltype(bounce_times_) bounce_times) : bounce_times_(std::move(bounce_times)) {}

    // TODO TLE
    void solve() const
    {
        const auto& [is_valid, chains] = find_chains();
        cout << (is_valid ? place_boomerang_for_chains(chains) : "-1\n");
    }

    static void create_from_input()
    {
        vector<uint8_t> values;
        {
            size_t size;
            cin >> size;
            values.resize(size);
        }

        for(auto& v : values)
        {
            unsigned short temp;
            cin >> temp;
            v = static_cast<decltype(values)::value_type>(temp);
        }
        bouncing_boomerangs{std::move(values)}.solve();
    }
};

int main()
{
    bouncing_boomerangs::create_from_input();
    return 0;
}
