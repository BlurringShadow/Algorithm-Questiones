/*
 * Given a string, find the length of the longest substring without repeating characters.
 */

#include <array>
#include <iostream>
#include <optional>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    std::array<std::optional<size_t>, std::numeric_limits<char>::max()> char_indices{};

    // ReSharper disable once CppInconsistentNaming
    int lengthOfLongestSubstring(const std::string_view& s)
    {
        size_t begin_index = 0;
        size_t largest_count = 0;

        {
            const auto size = s.size();

            for(size_t i = 0; i != size; ++i)
            {
                auto& index = char_indices[s[i]];
                if(index)
                {
                    const auto new_begin_index = *index + 1;
                    for(; begin_index < new_begin_index; ++begin_index)
                        char_indices[s[begin_index]].reset();
                }
                else
                {
                    const auto count = i - begin_index + 1;
                    if(count > largest_count) largest_count = count;
                }

                index = i;
            }
        }
        return static_cast<int>(largest_count);
    }
};

int main()
{
    std::cout << Solution{}.lengthOfLongestSubstring("abcabcbb");
    return 0;
}
