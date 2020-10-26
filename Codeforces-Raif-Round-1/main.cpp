// Created by BlurringShadow at 2020-10-20-下午 1:46

#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <list>
#include <unordered_set>
#include <utility>

#include "../algorithm_utility/utils.h"

#ifndef NDEBUG
#include "../algorithm_utility/debug_utils.h"
#endif

using std::array;
using std::string_view;
using std::initializer_list;
using std::uint8_t;
using std::pair;
using std::unordered_set;
using std::list;

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
    struct coordinate
    {
        size_t row, col;
    };

    // presentation of a valid chain, as like "(3...)(2)1"
    struct chain
    {
        // 1(2)(3...)
        vector<size_t> column_indices;

        bool has_two;

        [[nodiscard]] auto place_boomerang(size_t available_row_start) const
        {
            const auto indices_size = column_indices.size();
            vector<coordinate> boomerangs(2 * indices_size - 1 - has_two);
            auto add_boomerang = [&, boomerangs_it = boomerangs.begin()](const size_t col)mutable
            {
                *boomerangs_it++ = {available_row_start, col};
            };
            {
                // X...X
                auto i = indices_size - 1;
                for(; i > static_cast<decltype(i)>(has_two); --i)
                {
                    add_boomerang(column_indices[i]);
                    add_boomerang(column_indices[i - 1]);
                    ++available_row_start;
                }
                // X...X
                //     X
                add_boomerang(column_indices[i]);
            }

            // X...X
            if(has_two) add_boomerang(column_indices.front());

            return boomerangs;
        }
    };

    using chain_list_t = vector<chain>;

    vector<bounce_count_t> bounce_times_;

    /**
     * \brief
     * Resolve the chain.
     *
     * As the chain list, three_end_index is 1 or 0.
     *
     * If three_end_index is 1, element(chain_list[0]) will be like 3...(2)1.
     *
     * 2 is optional.
     *
     * From chain_list[three_end_index] to chain_list[two_end_index], elements will be like
     * 2...1
     *
     * At last from chain_list[two_end_index] to chain_list[chain_list.size() - 1], elements will only contain 1
     * \param col which col to resolve
     * \param chain_list input chain list
     * \param three_end_index end index of chain contain 3
     * \param two_end_index end index of chain contain 2
     * \return whether the column resolve successfully
     */
    bool resolve_column(
        const size_t col,
        chain_list_t& chain_list,
        size_t& three_end_index,
        size_t& two_end_index
    ) const
    {
        switch(bounce_times_[col])
        {
            // 1 should be the first of chain
        case 1: chain_list.push_back({initializer_list<size_t>{col}});
            // ignore 0
        case 0: break;
            // 2 should only just appear latter than 1 
        case 2:
            {
                if(two_end_index < three_end_index) two_end_index = three_end_index;
                if(chain_list.size() <= two_end_index) return false;

                auto& chain = chain_list[two_end_index++];
                chain.has_two = true;
                chain.column_indices.emplace_back(col);
            }
            break;
            // 3 is the last
        case 3:
            {
                if(chain_list.empty()) return false;
                if(three_end_index == 0) ++three_end_index;
                chain_list.front().column_indices.emplace_back(col);
            }
            break;
        }

        return true;
    }

    [[nodiscard]] auto find_chains() const
    {
        const auto bounce_times_count = bounce_times_.size();
        chain_list_t chain_list;
        size_t three_end_index = 0, two_end_index = 0;

        using return_t = pair<bool, decltype(chain_list)>;

        for(auto i = bounce_times_count - 1; i < bounce_times_count; --i)
            if(!resolve_column(i, chain_list, three_end_index, two_end_index))
                return return_t{false, chain_list};

        return return_t{true, chain_list};
    }

public:
    explicit bouncing_boomerangs(decltype(bounce_times_) bounce_times) : bounce_times_(std::move(bounce_times)) {}

    void solve() const
    {
#ifndef NDEBUG
        [[maybe_unused]] counter c_;
#endif

        const auto& [is_valid, chains] = find_chains();
        if(!is_valid)
        {
            cout << "-1\n";
            return;
        }

        size_t available_row_start = 0;
        size_t coordinates_count = 0;
        console_output_buffer_binder binder{};
        for(const auto& chain : chains)
        {
            const auto& boomerangs = chain.place_boomerang(available_row_start);
            available_row_start = boomerangs.back().row + 1;
            coordinates_count += boomerangs.size();

            for(const auto [row, col] : boomerangs) cout << row + 1 << ' ' << col + 1 << '\n';
        }

        {
            auto front_scope = binder.scope_add_front();
            cout << coordinates_count << '\n';
        }
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
#ifdef NDEBUG
    bouncing_boomerangs::create_from_input();
#else
    bouncing_boomerangs{{2, 0, 3, 0, 1, 1}}.solve();
    bouncing_boomerangs{{0}}.solve();
    bouncing_boomerangs{{3, 2, 2, 2, 1, 1}}.solve();
    bouncing_boomerangs{{3, 2, 1}}.solve();
    bouncing_boomerangs{{2, 2, 1, 1}}.solve();
    bouncing_boomerangs{{3, 3, 2, 1}}.solve();
    bouncing_boomerangs{{3, 3, 3, 1}}.solve();
    bouncing_boomerangs{{3, 3, 2, 2, 1, 1}}.solve();
    /*
    {
        vector<bouncing_boomerangs::bounce_count_t> values(100000, 2);
        std::fill(values.begin() + values.size() / 2, values.end(), 1);
        bouncing_boomerangs{std::move(values)}.solve();
    }
    */

#endif
    return 0;
}
