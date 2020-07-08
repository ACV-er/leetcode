// 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

// 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

//  

// 示例:

// 给定 1->2->3->4, 你应该返回 2->1->4->3.

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 改一改k个一组翻转

#include "assert.h"
#include "iostream"
#include "vector"

using namespace std;

class ListNode {
   public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void insertNode(ListNode* point, ListNode* node) {
    ListNode* tmp = point->next;
    point->next = node;
    node->next = tmp;
}

ListNode* deleteNextNode(ListNode* node) {
    if (node->next == nullptr) return nullptr;

    ListNode* tmp = node->next;
    node->next = node->next->next;

    return tmp;
}

class Solution {
   public:
    ListNode* swapPairs(ListNode* head) {
        int len = 0, cnt;
        ListNode* st = head;
        ListNode* ctrl = new ListNode(0);  // 方便操作链表
        ctrl->next = head;
        while (st != nullptr) {
            st = st->next;
            len++;
        }
        st = ctrl;
        cnt = len / 2;

        while (cnt--) {
            insertNode(st, deleteNextNode(st->next));
            st = st->next->next;
        }

        return ctrl->next;
    }
};

int main(void) {
    ListNode *head = new ListNode(0), *tmp;

    vector<int> data = {1, 2, 3, 4, 5};
    tmp = head;
    tmp->val = data[0];
    for (int i = 1; i < data.size(); i++) {
        tmp->next = new ListNode(data[i]);
        tmp = tmp->next;
    }

    Solution* solution = new Solution();
    auto rel = solution->swapPairs(head);
    cout << "------" << endl;
    while (rel != nullptr) {
        cout << rel->val << " ";
        rel = rel->next;
    }
    cout << endl;
    cout << endl << "------" << endl;
    return 0;
}