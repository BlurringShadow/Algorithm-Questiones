// Created by BlurringShadow at 2020-12-09-下午 7:13

#pragma once
#include "../algorithm_utility/utils.h"

#include <numeric>
#include <set>

class perform_easily final
{
public:
    using value_t = uint32_t;

private:
    std::set<value_t> strings_;
    std::set<value_t> notes_;

    struct performer
    {
        decltype(strings_)::const_iterator string_it{};
        value_t note{};

        performer(const decltype(string_it) it, const decltype(note) n) noexcept : string_it(it), note(n) {}

        [[nodiscard]] auto perform() const { return note - *string_it; }

        [[nodiscard]] bool operator<(const performer right) const { return perform() < right.perform(); }
    };

public:
    perform_easily(decltype(strings_) strings, decltype(notes_) notes) noexcept :
        strings_(std::move(strings)),
        notes_(std::move(notes)) {}

    void solve() const
    {
        using namespace std;

        auto candidate = std::numeric_limits<value_t>::max();

        if(notes_.size() <= 1) candidate = 0;
        else
        {
            multiset<performer> performers;

            for(const auto note : notes_) performers.emplace(strings_.cbegin(), note);

            for(const auto& strings_end = strings_.cend();;)
            {
                auto&& max_performer_it = std::prev(performers.end());

                set_if_lesser(candidate, max_performer_it->perform() - performers.begin()->perform());
                if(candidate == 0) break;

                auto&& node = performers.extract(max_performer_it);
                auto& string_it = node.value().string_it;
                if(std::distance(string_it, strings_end) == 1)break;
                std::advance(string_it, 1);

                performers.insert(std::move(node));
            }
        }

        cout << candidate << '\n';
    }

    template<typename InputStream
#ifdef __cpp_lib_concepts
    > requires requires(InputStream&& is) { get_from_stream<int>(is); }
#else
    , SFINAE((std::is_base_of_v<std::istream, std::remove_reference_t<InputStream>>))>
#endif
    static void create_from_input(InputStream&& is)
    {
        using namespace std;

        std::set<value_t> strings;
        std::set<value_t> notes;

        for(uint8_t i = 0; i < 6; ++i) strings.emplace(get_from_stream(is));
        for(value_t i = get_from_stream(is); i > 0; --i) notes.emplace(get_from_stream(is));

        perform_easily{std::move(strings), std::move(notes)}.solve();
    }
};
