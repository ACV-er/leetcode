// 给定一个二叉树，返回所有从根节点到叶子节点的路径。

// 说明: 叶子节点是指没有子节点的节点。

// 示例:

// 输入:

//    1
//  /   \
// 2     3
//  \
//   5

// 输出: ["1->2->5", "1->3"]

// 解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

#include "iostream"
#include "queue"
#include "string"
#include "vector"

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// class Solution {
//    private:
//     vector<string> rel;
//     void init(void) {
//         rel.clear();
//         rel.shrink_to_fit();
//     }

//    public:
//     vector<string> binaryTreePaths(TreeNode *root) {
//         init();

//         if (root != nullptr) getPath(root, "");

//         return rel;
//     }

//     void getPath(TreeNode *root, string path) {
//         path += to_string(root->val);

//         if (root->right == nullptr && root->left == nullptr) {
//             rel.push_back(path);
//             return;
//         }

//         if (root->right != nullptr) getPath(root->right, path + "->");
//         if (root->left != nullptr) getPath(root->left, path + "->");

//         return;
//     }
// };

// 分解为节点->子树的路径

class Solution {
   public:
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> rel{};
        if (root == nullptr) return rel;
        if (root->right == nullptr && root->left == nullptr) {
            rel.push_back(to_string(root->val));
            return rel;
        }

        vector<string> lRel = binaryTreePaths(root->left);
        vector<string> rRel = binaryTreePaths(root->right);

        for (string item : lRel) {
            rel.push_back(to_string(root->val) + "->" + item);
        }

        for (string item : rRel) {
            rel.push_back(to_string(root->val) + "->" + item);
        }

        return rel;
    }
};

// 简单建树，直接建完全二叉树。空缺补零，不影响结果
TreeNode *buildTree(vector<int> node) {
    queue<TreeNode *> node_queue;
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
    Solution *solution = new Solution();
    auto rel = solution->binaryTreePaths(buildTree(
        *(new vector<int>{5, 4, 8, 11, 0, 13, 4, 7, 2, 0, 0, 0, 0, 0, 1})));
    cout << "------" << endl;
    for (auto str : rel) {
        cout << str << endl;
    }
    cout << endl << "------" << endl;

    return 0;
}