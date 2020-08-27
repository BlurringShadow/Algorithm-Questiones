/*
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 * Given a linked list, remove the n-th node from the end of list and return its head.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using std::array;
using std::cout;
using std::size_t;
using std::string;
using std::tuple;
using std::vector;

// Definition for singly-linked list.
struct ListNode
{
    int val{};
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
    // ReSharper disable once CppInconsistentNaming
    static ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        auto current = head;
        ListNode* pre = nullptr;            

        for(; n > 0; --n, current = current->next);

        {
            auto end = current;
            for(current = head; end != nullptr; end = end->next, pre = current, current = current->next);
        }

        // remove node
        auto& next = current->next;
        (pre == nullptr ? head : pre->next) = next;
        //next = nullptr;
        //delete current; // NOLINT(cppcoreguidelines-owning-memory)

        return head;
    }
};

int main() noexcept
{
    try
    {
        constexpr auto nodes_size = 5;
        array<tuple<array<ListNode, nodes_size>, int>, nodes_size> test_data;
        std::for_each(
            test_data.begin(),
            test_data.end(),
            [value = 1](auto& element)mutable
            {
                auto& [nodes, pos] = element;
                std::generate(
                    nodes.begin(),
                    nodes.end(),
                    [value = 1u, &nodes]()mutable
                    {
                        const auto temp = value++;
                        return ListNode{static_cast<int>(temp), temp == nodes.size() ? nullptr : &nodes[temp]};
                    }
                );

                pos = value++;
            }
        );
        string output;

        for(auto&& [nodes, target] : test_data)
        {
            output += "nodes: {";
            for(const auto node : nodes) { output += std::to_string(node.val) + ','; }
            output.resize(output.size() - 1);
            output += "}\tpos: " + std::to_string(target) + "\tresults:";

            for(auto res = Solution::removeNthFromEnd(&nodes.front(), target); res != nullptr; res = res->next)
                output +=
                    std::to_string(res->val);
            output += "\n\n";
        }
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
