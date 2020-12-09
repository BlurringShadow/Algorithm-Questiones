// Created by BlurringShadow at 2020-12-08-下午 1:05

#pragma once
#include "../algorithm_utility/utils.h"

/*
 * All techniques in the ninja world consist of hand seals.
 * At the moment Naruto is learning a new technique, which consists of n⋅m different seals,
 * denoted by distinct numbers. All of them were written in an n×m table.

 * The table is lost now.
 * Naruto managed to remember elements of each row from left to right,
 * and elements of each column from top to bottom,
 * but he doesn't remember the order of rows and columns.
 * Please restore the table consistent with this data
 * so that Naruto will be able to learn the new technique.
 * 
 * Input
 * The first line of the input contains the only integer t (1≤t≤100000) denoting the number of test cases.
 * Their descriptions follow.
 * 
 * The first line of each test case description consists of two space-separated integers n and m (1≤n,m≤500)
 * standing for the number of rows and columns in the table, respectively.
 * All hand seals are encoded by the positive integers from 1 to n⋅m.
 * 
 * The following n lines contain m space separated integers each,
 * denoting elements of an arbitrary row in the table left to right.
 * 
 * The following m lines contain n space separated integers each,
 * denoting elements of an arbitrary column in the table top to bottom.
 * 
 * Sum of nm over all test cases does not exceed 250000.
 * It is guaranteed that each row occurs in the input exactly once, as well as each column.
 * It is also guaranteed that each number from 1 to nm occurs exactly once in all rows,
 * as well as in all columns.
 * Finally, it is guaranteed that a table consistent with the input exists.
 * 
 * Output
 * For each test case, output n lines with m space-separated integers each,
 * denoting the restored table. One can show that the answer is always unique.
 */
class new_technique final
{
public:
    using count_t = std::uint16_t;
    using value_t = std::uint32_t;

    static constexpr std::pair<count_t, count_t> count_range{1, 500};
    static constexpr std::pair<count_t, count_t> value_range{
        count_range.first * count_range.first,
        count_range.second * count_range.second
    };

private:
    vector<vector<value_t>> rows_;
    vector<vector<value_t>> columns_;

public:
    new_technique(decltype(rows_) rows, decltype(columns_) column) noexcept :
        rows_(std::move(rows)),
        columns_(std::move(column)) {}

    void solve() const
    {
        using namespace std;

        const auto row_size = static_cast<count_t>(rows_.size());
        const auto col_size = static_cast<count_t>(columns_.size());

        vector<value_t> result(row_size);
        {
            vector<count_t> column_row_map(row_size * col_size, row_size);

            {
                auto& column = columns_.front();
                for(count_t i = 0; i < row_size; ++i) column_row_map[column[i] - 1] = i;
            }

            {
                const auto col_index = [&front_row = rows_.front(), &column_row_map, row_size]()
                {
                    return static_cast<count_t>(std::find_if(
                        front_row.cbegin(),
                        front_row.cend(),
                        [&column_row_map, row_size](const auto num) { return column_row_map[num - 1] < row_size; }
                    ) - front_row.cbegin());
                }();

                for(count_t i = 0; i < row_size; ++i) result[column_row_map[rows_[i][col_index] - 1]] = i;
            }
        }

        {
            [[maybe_unused]] console_output_buffer_binder binder;
            for(const auto row_index : result)
            {
                for(const auto v : rows_[row_index])
                    cout << v << ' ';
                cout << '\n';
            }
        }
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
    , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        for(std::uint32_t i = get_from_stream(is); i > 0; --i)
        {
            const std::uint16_t row_size = get_from_stream(is), column_size = get_from_stream(is);
            vector<vector<value_t>> rows(row_size, vector<value_t>(column_size));
            vector<vector<value_t>> columns(column_size, vector<value_t>(row_size));

            for(auto& row : rows) for(auto& value : row) is >> value;
            for(auto& column : columns) for(auto& value : column) is >> value;

            new_technique{std::move(rows), std::move(columns)}.solve();
        }
    }
};
