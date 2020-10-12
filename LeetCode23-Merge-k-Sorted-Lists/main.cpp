/*
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * You are given an array of k linked-lists lists,
 * each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <fmt/format.h>

#ifdef __cpp_constinit
#define CONSTINIT constinit  // NOLINT(cppcoreguidelines-macro-usage)
#else
#define CONSTINIT
#endif

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using namespace std::literals;

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
};

class Solution
{
    [[maybe_unused]] inline static const auto _ = []()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        return 0;
    }();

public:
    using input_type = vector<ListNode*>;

    // ReSharper disable once CppInconsistentNaming
    static ListNode* mergeKLists(vector<ListNode*> node_list)
    {
        CONSTINIT ListNode head;
        auto node_ptr = &head;
#ifdef __cpp_lib_erase_if
        std::erase(node_list, nullptr);
#else
        node_list.erase(std::remove(node_list.begin(), node_list.end(), nullptr), node_list.cend());
#endif
        while(!node_list.empty())
        {
            using value_type = decltype(node_list)::value_type;

            auto&& min_node_it = std::min_element(
                node_list.begin(),
                node_list.end(),
                [](const value_type left, const value_type right) { return left->val < right->val; }
            );

            auto& min_node = *min_node_it;

            // unlink the node
            node_ptr->next = min_node;
            node_ptr = node_ptr->next;
            min_node = min_node->next;

            if(min_node == nullptr) node_list.erase(min_node_it);
        }
        return head.next;
    }
};

constexpr auto to_identical = [](const auto& t) { return t; };

template<typename T, typename Input, typename Output>
concept Converter = std::invocable<T, Input> && std::convertible_to<std::invoke_result_t<T, Input>, Output>;

template<
    typename... ParameterType,
    std::ranges::input_range InputRange,
    Converter<std::ranges::range_value_t<InputRange>, ParameterType...> InputConverter,
    std::invocable<ParameterType...> Func,
    Converter<std::invoke_result_t<Func, ParameterType...>, string> OutputConverter
>
static void test_run(
    const InputRange& input_data,
    InputConverter input_converter,
    Func func,
    OutputConverter output_converter = to_identical,
    const std::string_view& format_str = "{}\n"
)
{
    string output;
    for(auto& input : input_data)
    {
        auto&& converted = input_converter(input);
        std::invoke_result_t<Func, ParameterType...> r;
        if constexpr(sizeof...(ParameterType) > 1) r = std::apply(func, std::move(converted));
        else r = func(std::move(converted));
        output += fmt::format(format_str, output_converter(std::move(r)));
    }
    cout << output << '\n';
}

int main()
{
    try
    {
        using input_type = vector<vector<int>>;

#ifdef __cpp_lib_constexpr_vector
        constexpr
#else
        const
#endif
            vector<input_type> test_data_list{
                {{1, 2, 3}, {3, 4, 5}, {5, 6, 7}},
                {{1, 3, 5}, {2, 4, 6}}
            };

        vector<std::unique_ptr<ListNode[]>> node_ptrs;

        test_run<Solution::input_type>(
            test_data_list,
            [&](const input_type& data)
            {
                Solution::input_type nodes(data.size());
                std::ranges::transform(
                    data,
                    nodes.begin(),
                    [&](const auto& int_list)
                    {
                        node_ptrs.emplace_back(new ListNode[int_list.size()]);
                        auto& list_nodes = node_ptrs.back();
                        std::ranges::transform(
                            int_list,
                            list_nodes.get(),
                            [next = list_nodes.get()](const auto v) mutable { return ListNode{v, ++next}; }
                        );
                        list_nodes[int_list.size() - 1].next = nullptr;

                        return list_nodes.get();
                    }
                );

                return nodes;
            },
            [](Solution::input_type t) { return Solution::mergeKLists(std::move(t)); },
            [](ListNode* ptr)
            {
                string output;
                for(; ptr != nullptr; ptr = ptr->next) output += std::to_string(ptr->val);
                return output;
            }
        );
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
