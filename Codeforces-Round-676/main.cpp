#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <bitset>

using std::cout;
using std::cin;
using std::array;
using std::size_t;
using std::string;
using std::vector;
using std::uint8_t;
using std::uint32_t;
using std::pair;
using std::bitset;

[[maybe_unused]] static const auto noob_ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    return 0;
}();

// Problem A
// ReSharper disable once IdentifierTypo
class xor_wice
{
    uint32_t left_, right_;

    [[nodiscard]] auto calculate(const uint32_t a, const uint32_t b, const uint32_t x) const noexcept
    {
        return (a ^ x) + (b ^ x);
    }

public:
    // ReSharper disable once IdentifierTypo
    constexpr xor_wice(const uint32_t left, const uint32_t right) : left_(left), right_(right) {}

    void solve() const noexcept
    {
        cout << std::min(
            calculate(left_, right_, left_ | right_),
            calculate(left_, right_, left_ & right_)
        ) << '\n';
    }

    static void create_from_input()
    {
        size_t size;
        cin >> size;

        for(decltype(size) i = 0; i < size; ++i)
        {
            uint32_t l, r;
            cin >> l >> r;

            xor_wice{l, r}.solve();
        }
    }
};

int main()
{
    xor_wice::create_from_input();
    return 0;
}
