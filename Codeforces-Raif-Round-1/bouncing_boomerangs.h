// Created by BlurringShadow at 2020-10-26-下午 2:19

#pragma once

#include "../algorithm_utility/utils.h"

#ifndef NDEBUG
#include "../algorithm_utility/debug_utils.h"
#endif

using std::initializer_list;
using std::pair;

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

#ifdef __cpp_lib_concepts
    template<ConvertibleToRef<std::istream> InputStream>
#else
    template<
        typename InputStream,
        std::enable_if_t<std::is_convertible_v<T, std::istream&&> || std::is_convertible_v<T, std::istream&>>* = nullptr
    >
#endif
    static void create_from_input(InputStream&& in)
    {
        vector<uint8_t> values(get_from_stream<size_t>(in));

        for(auto& v : values)
            v = static_cast<decltype(values)::value_type>(get_from_stream<unsigned short>(in));

        bouncing_boomerangs{std::move(values)}.solve();
    }
};
