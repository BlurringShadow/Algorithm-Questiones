/*
 * Given a string s, find the longest palindromic substring in s.
 * You may assume that the maximum length of s is 1000.
 */

#include <array>
#include <iostream>
#include <optional>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:

    static constexpr size_t max_str_length = 1000;
    static constexpr size_t generated_max_str_length = 2 * max_str_length + 1;

    using generated_buffer_type = std::array<std::optional<char>, generated_max_str_length>;

    static constexpr char invalid_char = -1;

    // only suitable for aba pattern
    // return the length of half part offset (a.size())
    [[nodiscard]] static constexpr size_t get_palindrome_count(
        const generated_buffer_type& str,
        const size_t center_index,
        const size_t start_count,
        const size_t str_size
    )
    {
        auto offset = start_count;

        while (true)
        {
            const auto right_index = center_index + offset;
            const auto left_index = center_index - offset;
            if (right_index >= str_size || left_index >= str_size || str[left_index] != str[right_index])
                break;

            ++offset;
        }

        return offset - 1;
    }

    [[nodiscard]] static constexpr auto pre_condition(const std::string_view& str)
    {
        generated_buffer_type new_string{};

        for (size_t i = 0; i < str.size(); ++i)
            new_string[2 * i + 1] = str[i];

        return new_string;
    }

    // ReSharper disable once CppInconsistentNaming
    [[nodiscard]] static std::string longestPalindrome(const std::string_view& str)
    {
        const auto str_size = str.size() * 2 + 1;

        size_t center = 0;
        size_t max_count = 0;

        {
            const auto&& generated_str = pre_condition(str);
            std::array<size_t, generated_max_str_length> counts{};

            for (size_t i = 0, current_center = 0; i < str_size; ++i)
            {
                const auto current_center_count = counts[current_center];
                const auto offset = i - current_center;
                auto& count = counts[i];

                const auto mirrored_count_index = current_center - offset;
                const auto center_based_max_count = current_center_count > offset ? current_center_count - offset : 0;

                if (mirrored_count_index < counts.size())
                {
                    const auto mirrored_count = counts[mirrored_count_index];
                    if (mirrored_count < center_based_max_count)
                    {
                        count = mirrored_count;
                        continue;
                    }
                }

                count = get_palindrome_count(generated_str, i, center_based_max_count, str_size);
                current_center = i;

                if (count > max_count)
                {
                    center = i;
                    max_count = count;
                }
            }
        }

        const auto begin = (center - max_count) / 2;
        const auto count = max_count;
        auto&& sub = str.substr(begin, count);
        return {sub.begin(), sub.end()};
    }
};

int main() noexcept
{
    try
    {
        std::cout << Solution::longestPalindrome(
            "aaabaaaa"
        );
    }
    catch (...) {}
    return 0;
}
