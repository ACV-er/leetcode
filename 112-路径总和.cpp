// 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

// 说明: 叶子节点是指没有子节点的节点。

// 示例: 
// 给定如下二叉树，以及目标和 sum = 22，

//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \      \
//         7    2      1
// 返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/path-sum
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 水题

#include "iostream"
#include "queue"
#include "vector"

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
   public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == nullptr) return false;
        if (root->val == sum && root->right == nullptr && root->left == nullptr)
            return true;

        return hasPathSum(root->right, sum - root->val) ||
               hasPathSum(root->left, sum - root->val);
    }
};

// 简单建树，直接建完全二叉树。空缺补零，不影响结果
TreeNode* buildTree(vector<int> node) {
    queue<TreeNode*> node_queue;
    TreeNode *head = new TreeNode(node[0]), *tmp;
    node_queue.push(head);
    for (int i = 1; i < node.size(); i++) {
        tmp = node_queue.front();
        node_queue.pop();
        tmp->left = new TreeNode(node[i++]);
        node_queue.push(tmp->left);
        tmp->right = new TreeNode(node[i]);
        node_queue.push(tmp->right);
    }

    return head;
}

int main(void) {
    Solution* solution = new Solution();
    cout << solution->hasPathSum(
                buildTree(*(new vector<int>{5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0,
                                            0, 0, 0, 1})),
                22)
         << endl;
    // cout << solution->hasPathSum() << endl;
    return 0;
}