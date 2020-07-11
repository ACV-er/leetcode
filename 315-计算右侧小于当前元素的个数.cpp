// 给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质：
// counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。

// 示例:

// 输入: [5,2,6,1]
// 输出: [2,1,1,0]
// 解释:
// 5 的右侧有 2 个更小的元素 (2 和 1).
// 2 的右侧仅有 1 个更小的元素 (1).
// 6 的右侧有 1 个更小的元素 (1).
// 1 的右侧有 0 个更小的元素.

#include "algorithm"
#include "iostream"
#include "vector"

using namespace std;

class Solution {
    class Node {
       public:
        Node* left;
        Node* right;
        int val;
        int count;
        Node(int val) : val(val) {
            left = nullptr;
            right = nullptr;
            count = 0;
        };

        int insert(Node* node) {
            int count = 0;
            Node* root = this;
            while (true) {
                if (root->val < node->val) {
                    count += root->count + 1;
                    if (root->left == nullptr) {
                        root->left = node;
                        break;
                    }
                    root = root->left;
                } else if (root->val >= node->val) {
                    root->count++;
                    if (root->right == nullptr) {
                        root->right = node;
                        break;
                    }
                    root = root->right;
                }
            }

            return count;
        }
    };

   public:
    vector<int> countSmaller(vector<int>& nums) {
        int len = nums.size();
        vector<int> rel(len);
        if (len == 0) return rel;
        rel[len - 1] = 0;
        if (len == 1) {
            return rel;
        }

        Node* root = new Node(nums[len - 1]);
        for (int i = len - 2; i >= 0; i--) {
            rel[i] = root->insert(new Node(nums[i]));
        }
        return rel;
    }
};

int main(void) {
    Solution* solution = new Solution();
    vector<int> data = {8, 5, 2, 6, 1, 1};
    auto rel = solution->countSmaller(data);
    cout << "------" << endl;
    for (auto item : rel) {
        cout << item << " ";
    }
    cout << endl << "------" << endl;

    return 0;
}