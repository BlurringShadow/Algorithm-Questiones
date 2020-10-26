// Created by BlurringShadow at 2020-10-26-下午 2:54

#pragma once
#include "../algorithm_utility/utils.h"

class finding_sasuke
{
    vector<int> energies_;

public:
    explicit finding_sasuke(std::vector<int> energies) noexcept : energies_(std::move(energies)) {}

    void solve() const
    {
        const auto size = energies_.size();
        auto i = size - 1;
        const auto middle_end = size / 2 - 1;
        console_output_buffer_binder binder{};

        for(; i > middle_end; --i) std::cout << -energies_[i] << ' ';
        for(; i < size; --i) std::cout << energies_[i] << ' ';
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
        for(auto test_count = get_from_stream<size_t>(in); test_count > 0; --test_count)
        {
            vector<int> energies(get_from_stream<size_t>(in));
            for(auto& energy : energies) in >> energy;

            finding_sasuke{std::move(energies)}.solve();
        }
    }
};
