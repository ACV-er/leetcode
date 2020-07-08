// 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。

// 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
//
// 示例：
// 给你这个链表：1->2->3->4->5
// 当 k = 2 时，应当返回: 2->1->4->3->5
// 当 k = 3 时，应当返回: 3->2->1->4->5
//  

// 说明：

// 你的算法只能使用常数的额外空间。
// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/reverse-nodes-in-k-group
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 头插法，但是要先算长度

#include "assert.h"
#include "iostream"
#include "vector"

using namespace std;

// 写完之后发现letcode的ListNode是不能被改动的
// 没办法添加成员方法，所以后面写了函数形式。
class ListNode {
   public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}

    void insertList(ListNode* node) {
        ListNode* tmp = this->next;
        this->next = node;
        if (tmp != nullptr) {
            while (node->next != nullptr) {
                node = node->next;
            }

            node->next = tmp;
        }
    }

    void insertNode(ListNode* node) {
        ListNode* tmp = this->next;
        this->next = node;
        node->next = tmp;
    }

    ListNode* deleteNextNode() {
        if (this->next == nullptr) return nullptr;

        ListNode* tmp = this->next;
        this->next = this->next->next;

        return tmp;
    }
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        int len = 0, cnt;
        ListNode *st, *curIdx = head;
        ListNode* ctrl = new ListNode(0);  // 方便操作链表
        ctrl->next = head;
        while (curIdx != nullptr) {
            curIdx = curIdx->next;
            len++;
        }
        curIdx = st = ctrl;
        cnt = len / k;
        assert(cnt >= 0);
        while (cnt--) {
            // 转换k个只需要k-1次，两个节点只需要插一次。
            st = curIdx;
            curIdx = st->next;
            for (int i = 1; i < k; i++) {
                insertNode(st, deleteNextNode(curIdx));
            }
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
    auto rel = solution->reverseKGroup(head, 3);
    cout << "------" << endl;
    while (rel != nullptr) {
        cout << rel->val << " ";
        rel = rel->next;
    }
    cout << endl;
    cout << endl << "------" << endl;
    return 0;
}