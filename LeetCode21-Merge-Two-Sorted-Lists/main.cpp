/*
 * https://leetcode.com/problems/merge-two-sorted-lists/
 * Merge two sorted linked lists and return it as a new sorted list.
 * The new list should be made by splicing together the nodes of the first two lists.
*/

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using std::pair;
using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::queue;
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
    static ListNode* mergeTwoLists(ListNode* const l1, ListNode* l2)
    {
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;

        queue<int> l1_nums;
        auto first_head = l1, second_head = l2;
        {
            decltype(first_head) previous_head = nullptr;
            for(; first_head != nullptr; previous_head = first_head, first_head = first_head->next)
            {
                const auto l2_num = second_head->val;

                if(l1_nums.empty())
                {
                    const auto l1_num = first_head->val;
                    if(l1_num > l2_num)
                    {
                        l1_nums.push(first_head->val);
                        first_head->val = l2_num;
                        second_head = second_head->next;
                    }
                }
                else
                {
                    const auto l1_num = l1_nums.front();
                    l1_nums.push(first_head->val);
                    if(l1_num < l2_num)
                    {
                        first_head->val = l1_num;
                        l1_nums.pop();
                    }
                    else
                    {
                        first_head->val = l2_num;
                        second_head = second_head->next;
                    }
                }

                if(second_head == nullptr)
                {
                    previous_head = first_head;
                    for(first_head = first_head->next;
                        first_head != nullptr;
                        previous_head = first_head, first_head = first_head->next, l1_nums.pop())
                    {
                        auto& v = first_head->val;
                        l1_nums.push(v);
                        v = l1_nums.front();
                    }
                    previous_head->next = l2;
                    for(first_head = l2; first_head != nullptr; first_head = first_head->next, l1_nums.pop())
                    {
                        first_head->val = l1_nums.front();
                    }
                    return l1;
                }
            }
            previous_head->next = l2;
        }

        for(first_head = l2; ; first_head = first_head->next)
        {
            if(l1_nums.empty()) break;

            const auto l1_num = l1_nums.front();
            const auto l2_num = second_head->val;

            if(l1_num < l2_num)
            {
                first_head->val = l1_num;
                l1_nums.pop();
            }
            else
            {
                first_head->val = l2_num;
                second_head = second_head->next;
                if(second_head == nullptr)
                {
                    for(first_head = first_head->next; first_head != nullptr; first_head = first_head->next, l1_nums.
                        pop()) { first_head->val = l1_nums.front(); }
                    break;
                }
            }
        }

        return l1;
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
