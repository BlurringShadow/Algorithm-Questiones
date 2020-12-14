// Created by BlurringShadow at 2020-12-11-上午 11:19

#pragma once
#include "../algorithm_utility/utils.h"

#include <queue>
#include <stack>

/*
 * Tenten runs a weapon shop for ninjas.
 * Today she is willing to sell n shurikens which cost 1, 2, ..., n ryo (local currency).
 * During a day, Tenten will place the shurikens onto the showcase,
 * which is empty at the beginning of the day.
 * Her job is fairly simple: sometimes Tenten places another shuriken (from the available shurikens) on the showcase,
 * and sometimes a ninja comes in and buys a shuriken from the showcase.
 * Since ninjas are thrifty, they always buy the cheapest shuriken from the showcase.

 * Tenten keeps a record for all events, and she ends up with a list of the following types of records:
 * 
 * + means that she placed another shuriken on the showcase;
 * - x means that the shuriken of price x was bought.
 * Today was a lucky day, and all shurikens were bought.
 * Now Tenten wonders if her list is consistent,
 * and what could be a possible order of placing the shurikens on the showcase.
 * Help her to find this out!
 * 
 * Input
 * The first line contains the only integer n (1≤n≤10^5) standing for the number of shurikens.
 * 
 * The following 2n lines describe the events in the format described above.
 * It's guaranteed that there are exactly n events of the first type,
 * and each price from 1 to n occurs exactly once in the events of the second type.
 * 
 * Output
 * If the list is consistent, print "YES".
 * Otherwise (that is, if the list is contradictory and there is no valid order of shurikens placement), print "NO".
 * 
 * In the first case the second line must contain n space-separated integers
 * denoting the prices of shurikens in order they were placed.
 * If there are multiple answers, print any.
*/
class shurikens final
{
public:
    using value_t = uint32_t;

    struct record
    {
        value_t value;

        friend std::istream& operator>>(std::istream& is, record& r)
        {
            switch(get_from_stream<char>(is))
            {
            case '+': r.value = 0;
                break;
            case '-': is >> r.value;
                break;
            }

            return is;
        }
    };

private:
    vector<record> records_{};

    [[nodiscard]] vector<value_t> generate_sequence() const
    {
        using namespace std;

        const value_t size = auto_cast{records_.size() / 2};
        vector<value_t> shuriken_sequence(size);

        auto&& shuriken_stack = [size]()
        {
            vector<value_t> container;
            container.reserve(size);
            return stack(std::move(container));
        }();
        value_t current_shuriken_index = 0;

        for(auto r : records_)
        {
            const auto sold_v = r.value;
            if(sold_v == 0) shuriken_stack.emplace(current_shuriken_index++);
            else
            {
                if(shuriken_stack.empty()) return {};

                shuriken_sequence[shuriken_stack.top()] = sold_v;
                shuriken_stack.pop();
            }
        }

        return shuriken_sequence;
    }

    [[nodiscard]] vector<value_t> solve() const
    {
        using namespace std;

        const auto& shuriken_sequence = generate_sequence();

        if(!shuriken_sequence.empty())
        {
            auto&& price_queue = [size = records_.size() / 2]()
            {
                vector<value_t> container;
                container.reserve(size);
                return priority_queue(std::greater<>{}, std::move(container));
            }();

            value_t current_shuriken_index = 0;

            for(auto r : records_)
            {
                const auto sold_v = r.value;
                if(sold_v == 0) price_queue.emplace(shuriken_sequence[current_shuriken_index++]);
                else
                {
                    if(price_queue.empty() || price_queue.top() != sold_v) return {};
                    price_queue.pop();
                }
            }
        }

        return shuriken_sequence;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, shurikens& s)
    {
        console_output_buffer_binder binder;

        auto&& res = s.solve();
        if(res.empty()) cout << "NO\n";
        else
        {
            cout << "YES\n";
            for(const auto price : res) cout << price << ' ';
            cout << '\n';
        }

        return os;
    }

    friend std::istream& operator>>(std::istream& is, shurikens& s)
    {
        s.records_.resize(get_from_stream<value_t>(is) * 2);
        for(auto& r : s.records_) is >> r;

        return is;
    }
};
