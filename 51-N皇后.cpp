// n 皇后问题研究的是如何将 n 个皇后放置在 n×n
// 的棋盘上，并且使皇后彼此之间不能相互攻击。

// 上图为 8 皇后问题的一种解法。

// 给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

// 每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.'
// 分别代表了皇后和空位。

// 示例：

// 输入：4
// 输出：[
//  [".Q..",  // 解法 1
//   "...Q",
//   "Q...",
//   "..Q."],

//  ["..Q.",  // 解法 2
//   "Q...",
//   "...Q",
//   ".Q.."]
// ]
// 解释: 4 皇后问题存在两个不同的解法。

#include "cstring"
#include "iostream"
#include "vector"

using namespace std;

class Solution {
    vector<vector<string>> rel{{}};
    vector<string> distribution;

    int col[10], dg[18], udg[18];

    void init() {
        rel.clear();
        rel.shrink_to_fit();
        memset(col, 0, sizeof(col));
        memset(dg, 0, sizeof(dg));
        memset(udg, 0, sizeof(udg));
    }

   public:
    vector<vector<string>> solveNQueens(int n) {
        if (n < 0) {
            return {{}};
        }
        if (n > 100) {
            return {{"Too large prama 'n'"}};
        }
        distribution.resize(n, string(n, '.'));
        init();
        dfs(0, n);
        return rel;
    }
    void dfs(int pos, int n) {
        if (pos == n) {
            rel.push_back(distribution);
        }
        for (size_t i = 0; i < n; i++) {
            if (!col[i] && !dg[pos - i + n] && !udg[i + pos]) {
                col[i] = dg[pos - i + n] = udg[i + pos] = true;
                distribution[pos][i] = 'Q';
                dfs(pos + 1, n);
                col[i] = dg[pos - i + n] = udg[i + pos] = false;
                distribution[pos][i] = '.';
            }
        }
    }
};

int main(void) {
    Solution *solution = new Solution();
    auto rel = solution->solveNQueens(1000);
    cout << "------" << endl;
    for (auto dist : rel) {
        for (auto str : dist) {
            cout << str << endl;
        }
        cout << endl;
    }
    cout << endl << "------" << endl;
    return 0;
}