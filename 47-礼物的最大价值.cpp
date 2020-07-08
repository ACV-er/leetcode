//
// 在一个m*n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于0）。
// 你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

//  
// 示例 1:
// 输入:
// [
//   [1,3,1],
//   [1,5,1],
//   [4,2,1]
// ]
// 输出: 12
// 解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物
//  

// 提示：
// 0 < grid.length <= 200
// 0 < grid[0].length <= 200

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 动态规划即可

#include "cmath"
#include "cstdio"
#include "iostream"
#include "vector"

using namespace std;

class Solution {
   public:
    int maxValue(vector<vector<int>>& grid) {
        int row = grid.size(), col = grid[0].size();
        if (row == 0) return 0;
        for (int i = 1; i < col; i++) {
            grid[0][i] += grid[0][i - 1];
        }
        for (int i = 1; i < row; i++) {
            grid[i][0] += grid[i - 1][0];
            for (int j = 1; j < col; j++) {
                grid[i][j] += max(grid[i][j - 1], grid[i - 1][j]);
                // printf("grid[%d][%d] = %d\n", i, i, grid[i][j]);
            }
        }

        return grid[row - 1][col - 1];
    }
};

int main(void) {
    Solution* solution = new Solution();
    auto rel = solution->maxValue(
        *(new vector<vector<int>>{{1, 3, 1}, {1, 5, 1}, {1, 2, 1}}));
    cout << rel << "=12" << endl;
    return 0;
}