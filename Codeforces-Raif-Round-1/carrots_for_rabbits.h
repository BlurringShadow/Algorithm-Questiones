// Created by BlurringShadow at 2020-10-26-下午 3:16

#pragma once
#include <queue>
#include "../algorithm_utility/utils.h"

#ifndef NDEBUG
#include "../algorithm_utility/debug_utils.h"
#endif

using std::priority_queue;
using std::pair;

/*
 * There are some rabbits in Singapore Zoo.
 * To feed them, Zookeeper bought n carrots with lengths a1,a2,a3,…,an.
 * However, rabbits are very fertile and multiply very quickly.
 * Zookeeper now has k rabbits and does not have enough carrots to feed all of them.
 * To solve this problem, Zookeeper decided to cut the carrots into k pieces.
 * For some reason, all resulting carrot lengths must be positive integers.
 * Big carrots are very difficult for rabbits to handle and eat, so the time needed to eat a carrot of size x is x2.
 * Help Zookeeper split his carrots while minimizing the sum of time taken for rabbits to eat the carrots.
 * 
 * Input
 * The first line contains two integers n and k (1≤n≤k≤105): the initial number of carrots and the number of rabbits.
 * The next line contains n integers a1,a2,…,an (1≤ai≤106): lengths of carrots.
 * It is guaranteed that the sum of ai is at least k.
 * 
 * Output
 * Output one integer: the minimum sum of time taken for rabbits to eat carrots.
 */
class carrots_for_rabbits
{
public:
    using length_t = uint32_t;
    using cost_t = uint64_t;

    class carrot
    {
        length_t length_;
        cost_t diff_ = 0;
        length_t cut_count_ = 0;

        constexpr static cost_t min_split_cost(const length_t len, const length_t count)
        {
            const cost_t split_length = len / count;
            const auto extra_count = len % count;
            const auto extra_length = split_length + 1;

            return (count - extra_count) * split_length * split_length + extra_count * extra_length * extra_length;
        }

    public:
        explicit constexpr carrot(const length_t length = 0) noexcept : length_(length) {}

        constexpr void cut() noexcept
        {
            ++cut_count_;
            diff_ = min_split_cost(length_, cut_count_) - min_split_cost(length_, cut_count_ + 1);
        }

        constexpr bool operator<(const carrot& right) const noexcept { return diff_ < right.diff_; }

        [[nodiscard]] constexpr auto diff() const noexcept { return diff_; }
    };

private:
    vector<length_t> carrot_lengths_;
    length_t rabbit_count_;

public:
    explicit carrots_for_rabbits(
        decltype(carrot_lengths_) carrots,
        const decltype(rabbit_count_) rabbit_count
    ) noexcept : carrot_lengths_(std::move(carrots)), rabbit_count_(rabbit_count) {}

    void solve()
    {
        cost_t cost = 0;
        priority_queue<carrot> queue;

        for(const auto& length : carrot_lengths_)
        {
            carrot c{length};
            c.cut();
            queue.emplace(c);
            cost += std::multiplies<decltype(cost)>{}(length, length);
        }

        for(auto carrot_pieces_count = carrot_lengths_.size(); carrot_pieces_count < rabbit_count_; carrot_pieces_count++)
        {
            auto top_carrot = queue.top();
            cost -= top_carrot.diff();

            top_carrot.cut();
            queue.pop();
            queue.emplace(top_carrot);
        }

        cout << cost << '\n';
    }

#ifdef __cpp_lib_concepts
    template<ConvertibleToRef<std::istream> InputStream>
#else
    template<
        typename InputStream,
        std::enable_if_t<std::is_convertible_v<InputStream, std::istream&&> || std::is_convertible_v<InputStream, std::istream&>>* = nullptr
    >
#endif
    static void create_from_input(InputStream&& is)
    {
#ifndef NDEBUG
        counter c;
#endif
        vector<length_t> carrot_lengths(get_from_stream<length_t>(is));
        auto rabbit_count = get_from_stream<uint32_t>(is);

        for(auto& carrot_length : carrot_lengths) is >> carrot_length;

        carrots_for_rabbits{std::move(carrot_lengths), rabbit_count}.solve();
    }
};
