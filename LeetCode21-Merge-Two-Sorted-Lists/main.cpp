/*
 * https://leetcode.com/problems/merge-two-sorted-lists/
 * Merge two sorted linked lists and return it as a new sorted list.
 * The new list should be made by splicing together the nodes of the first two lists.
*/

#include <array>
#include <iostream>
#include <string>
#include <vector>

using std::array;
using std::pair;
using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::initializer_list;
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
    static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;

        vector<int> l1_nums;
        auto head = l1;
        for(; head->next != nullptr; head = head->next) l1_nums.emplace_back(head->val);
        head->next = l2;
        l1_nums.emplace_back(head->val);

        if(l1_nums.back() > l2->val)
        {
            const auto l1_size = l1_nums.size();
            head = l1;
            size_t i;
            for(i = 0; i < l1_size && l2 != nullptr; head = head->next)
            {
                const auto l1_num = l1_nums[i];
                const auto l2_num = l2->val;
                if(l1_num < l2_num)
                {
                    head->val = l1_num;
                    ++i;                
                }
                else
                {
                    head->val = l2_num;
                    l2 = l2->next;
                }
            }

            if(l2 == nullptr) for(; head != nullptr; head = head->next, ++i) head->val = l1_nums[i];
            else for(; head != nullptr; head = head->next, l2 = l2->next) head->val = l2->val;
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
