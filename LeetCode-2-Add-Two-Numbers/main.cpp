#include <array>
#include <iostream>
#include <vector>

/*
 *You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 *You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/

template <typename RangeType>
constexpr void link(RangeType& range)
{
    auto&& before = range.begin();
    auto&& after = std::next(before);
    for (; after != range.end(); ++after, ++before) { before->next = &*after; }
}

// ReSharper disable All
struct ListNode
{
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(NULL) {}
};

// ReSharper restore All

// ReSharper disable once CppInconsistentNaming
class Solution
{
public:

    // ReSharper disable once CppInconsistentNaming
    ListNode* addTwoNumbers(ListNode* left, ListNode* right)
    {
        const auto head = new ListNode{0};

        auto node = head;
        ListNode* pre = nullptr;

        auto carry = false;

        while (true)
        {
            int left_v, right_v;
            if (left == nullptr)
            {
                if (right == nullptr)
                {
                    if (!carry)
                    {
                        delete node;
                        pre->next = nullptr;
                        break;
                    }
                    right_v = 0;
                }
                else
                {
                    right_v = right->val;
                    right = right->next;
                }
                left_v = 0;
            }
            else
            {
                left_v = left->val;
                if (right == nullptr) right_v = 0;
                else
                {
                    right_v = right->val;
                    right = right->next;
                }
                left = left->next;
            }

            auto sum = left_v + right_v + carry;
            if (sum >= 10)
            {
                sum -= 10;
                carry = true;
            }
            else carry = false;

            {
                auto& temp = *node;

                temp.val = sum;
                temp.next = new ListNode{0};

                pre = node;
                node = temp.next;
            }
        }

        return head;
    }
};

int main()
{
    try
    {
        std::vector<ListNode> first{{1}, {9}};
        std::vector<ListNode> second{{9}};

        link(first), link(second);

        auto res = Solution{}.addTwoNumbers(&*first.begin(), &*second.begin());
        while (res != nullptr)
        {
            std::cout << res->val;
            res = res->next;
        }
    }
    catch (...) {}
    return 0;
}
