/*
 * https://leetcode.com/problems/merge-two-sorted-lists/
 * Merge two sorted linked lists and return it as a new sorted list.
 * The new list should be made by splicing together the nodes of the first two lists.
*/
#define var decltype(auto)
#include <iostream>
#include <string>
#include <vector>

using std::pair;
using std::cout;
using std::size_t;
using std::string;
using std::vector;
using namespace std::literals;


struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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
    static ListNode* mergeTwoLists(ListNode* first_n, ListNode* second_n)
    {
        ListNode head{};
        for(auto current = &head;; current = current->next)
        {
            auto& next = current->next;
            if(first_n == nullptr)
            {
                next = second_n;
                break;
            }
            if(second_n == nullptr)
            {
                next = first_n;
                break;
            }

            auto& n = first_n->val > second_n->val ? second_n : first_n;
            next = n;
            n = n->next;
        }

        return head.next;
    }
};

template<typename T>
auto generate_nodes_from_nums(const T& t)
{
    vector<ListNode> nodes;
    for(const auto v : t) nodes.emplace_back(v);
    if(!nodes.empty()) for(size_t i = 0; i < nodes.size() - 1; ++i) nodes[i].next = &nodes[i + 1];

    return nodes;
}

int main() noexcept
{
    try
    {
        vector<pair<vector<int>, vector<int>>> test_data
        {
            {{2}, {1}},
            {{-10, -10, -9, -4, 1, 6, 6}, {-7}},
            {{1, 2, 4}, {1, 3, 4}},
            {{1}, {}}
        };
        string output;

        for(auto [first, second] : test_data)
        {
            output += "first nums: ";
            for(const auto v : first) output += std::to_string(v) + ' ';
            output += "\tsecond nums: ";
            for(const auto v : second) output += std::to_string(v) + ' ';
            output += "\nresult: ";
            {
                auto&& first_nodes = generate_nodes_from_nums(first);
                auto&& second_nodes = generate_nodes_from_nums(second);
                for(auto p = Solution::mergeTwoLists(
                        first_nodes.empty() ? nullptr : &first_nodes.front(),
                        second_nodes.empty() ? nullptr : &second_nodes.front()
                    );
                    p != nullptr;
                    p = p->next
                )
                    output += std::to_string(p->val) + ' ';
            }
            output += "\n\n";
        }
        cout << output;
    }
    catch(const std::exception& e) { cout << e.what(); }
    return 0;
}
