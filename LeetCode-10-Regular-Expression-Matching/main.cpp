/*
 * Given an input string (s) and a pattern (p).
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
*/

#include <iostream>
#include <optional>
#include <stack>
#include <unordered_set>
#include <vector>

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:
    class regex_pattern
    {
        static constexpr char any_char_ = -1;

        struct regex
        {
            char c = any_char_;
            std::optional<std::unordered_set<char>> next;
        };

        std::vector<regex> pattern_;
        decltype(pattern_)::size_type end_ = 0;

    public:
        regex_pattern(const std::string_view& pattern)
        {
            const auto size = pattern.size();

            pattern_.reserve(size);

            for(std::decay_t<decltype(size)> i = 0; i < size; ++i)
            {
                auto c = pattern[i];
                {
                    const auto pattern_size = pattern_.size();
                    if(c == '*')
                    {
                        auto& back = pattern_.back();

                        if(back.c == any_char_)
                        {
                            auto previous = pattern_size - 2;
                            for(; previous < pattern_size && pattern_[previous].next; --previous);

                            pattern_[previous + 1].c = any_char_;
                            pattern_.resize(previous + 2);
                        }
                        else
                            for(auto previous = pattern_size - 2; previous < pattern_size; --previous)
                            {
                                const auto& r = pattern_[previous];
                                if(!r.next) break;
                                if(r.c == any_char_ || r.c == back.c)
                                {
                                    pattern_.pop_back();
                                    goto do_not_add;
                                }
                            }
                        back.next.emplace(std::unordered_set<char>{});

                    do_not_add:;
                    }
                    else
                    {
                        if(c == '.') c = any_char_;
                        for(auto index = pattern_size - 1; index < pattern_size; --index)
                        {
                            auto& r = pattern_[index];
                            if(!r.next) break;
                            if(c == any_char_) r.next->clear();
                            r.next->insert(c);
                        }
                        pattern_.push_back({c});
                    }
                }
            }

            for(end_ = pattern_.size() - 1; end_ < pattern_.size(); --end_)
            {
                auto& r = pattern_[end_];
                if(!r.next) break;
            }
        }

        bool match(const std::string_view& input)
        {
            const auto pattern_size = pattern_.size();

            if(pattern_size == 1)
            {
                const auto& r = pattern_.front();
                if(!r.c && r.next) return true;
            }

            const auto str_size = input.size();
            std::size_t str_index = 0;
            std::size_t pattern_index = 0;

            std::stack<std::pair<std::size_t, std::size_t>> star_match_stack;

            while(true)
            {
                for(; pattern_index < pattern_size && str_index < str_size;)
                {
                    const auto& r = pattern_[pattern_index];
                    const auto c = input[str_index];
                    const auto equal = r.c != any_char_ ? r.c == c : true;
                    const auto has_star = r.next ? true : false;
                    const auto next_equal = has_star ?
                                                r.next->find(c) != r.next->cend() ||
                                                r.next->find(any_char_) != r.next->cend() :
                                                false;

                    if(equal)
                    {
                        if(next_equal)
                        {
                            star_match_stack.push({pattern_index, str_index});
                            ++pattern_index;
                        }
                        else
                        {
                            if(!has_star)
                                ++pattern_index;
                            ++str_index;
                        }
                    }
                    else if(next_equal) ++pattern_index;
                    else break;
                }

                const auto is_regex_match_end = end_ >= pattern_size || pattern_index > end_;
                if(str_index >= str_size && is_regex_match_end) return true;

                while(true)
                {
                    if(star_match_stack.empty()) 
                        return false;

                    auto& [previous_pattern_index, previous_str_index] = star_match_stack.top();
                    const auto c = pattern_[previous_pattern_index].c;

                    ++previous_str_index;
                    if(previous_str_index < str_size)
                    {
                        if(c == any_char_ || c == input[previous_str_index - 1])
                        {
                            pattern_index = previous_pattern_index + 1, str_index = previous_str_index;
                            break;
                        }
                    }
                    else if(is_regex_match_end) return true;
                    star_match_stack.pop();
                }
            }
        }
    };

    // ReSharper disable once CppInconsistentNaming
    [[nodiscard]] static bool isMatch(const std::string_view& input_str, const std::string_view& pattern)
    {
        return regex_pattern{pattern}.match(input_str);
    }
};

int main()
{
    std::cout << std::boolalpha << Solution::isMatch("cacbcacbacbccac", ".*c*c*bb*c*..*a*a");
    return 0;
}
