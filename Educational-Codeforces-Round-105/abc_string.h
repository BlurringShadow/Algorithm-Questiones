#pragma once
#include "../algorithm_utility/utils.h"

#include <bitset>
#include <list>

class abc_string final
{
    enum class abc { a, b, c };

    std::vector<abc> str_;

    [[nodiscard]] auto solve() const
    {
        using namespace std;

        static constexpr auto maps = []()
        {
            std::array<std::bitset<3>, 6> sets;
            for(uint8_t i = 1; i < 7; ++i) sets[i - 1] = i;
            return sets;
        }();

        for(const auto map : maps)
        {
            std::list<bool> str_list(str_.size());
            std::transform(
                str_.cbegin(),
                str_.cend(),
                str_list.begin(),
                [&](const auto value)
                {
                    return map[static_cast<std::underlying_type_t<abc>>(value)];
                }
            );

            for(auto&& it = str_list.cbegin();;)
            {
                if(str_list.empty()) 
                    return true;

                it = adjacent_find(it, str_list.cend(), std::less<>{});
                if(it == str_list.cend()) break;

                it = str_list.erase(it, next(it, 2));
                if(it != str_list.cbegin()) std::advance(it, -1);
            }
        }

        return false;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, abc_string& s)
    {
        return os << (s.solve() ? "YES" : "NO") << '\n';
    }

    friend std::istream& operator>>(std::istream& is, abc_string& v)
    {
        string&& input_str = get_from_stream(is);
        auto& str = v.str_;
        str.resize(input_str.size());
        std::transform(
            input_str.cbegin(),
            input_str.cend(),
            str.begin(),
            [](const char c)
            {
                switch(c)
                {
                case 'A': return abc::a;
                    break;
                case 'B': return abc::b;
                    break;
                case 'C': return abc::c;
                    break;
                }
                throw std::invalid_argument("");
            }
        );
        return is;
    }
};

using problem_t = abc_string;
