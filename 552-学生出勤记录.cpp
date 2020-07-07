// 给定一个正整数 n，返回长度为 n 的所有可被视为可奖励的出勤记录的数量。
// 答案可能非常大，你只需返回结果mod 109 + 7的值。

// 学生出勤记录是只包含以下三个字符的字符串：

// 'A' : new_absent，缺勤
// 'L' : Late，迟到
// 'P' : Present，到场
// 如果记录不包含多于一个'A'（缺勤）或超过两个连续的'L'（迟到），则该记录被视为可奖励的。

// 示例 1:

// 输入: n = 2
// 输出: 8
// 解释：
// 有8个长度为2的记录将被视为可奖励：
// "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
// 只有"AA"不会被视为可奖励，因为缺勤次数超过一次。
// 注意：n 的值不会超过100000。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/student-attendance-record-ii
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include "cstring"
#include "iostream"
#include "vector"

using namespace std;

// 简单
// class Solution {
//    public:
//     const int M = 1000000007;
//     int checkRecord(int n) {
//         long a0l0 = 1, a0l1 = 0, a0l2 = 0, a1l0 = 0, a1l1 = 0, a1l2 = 0;
//         long new_a0l0 = 0, new_a1l0 = 0;
//         while (n--) {
//             //
//             状态转变。一种状态可以由哪些状态变化而来。如a0l0可以有a0l0、a0l1、a0l2末尾加P得来
//             new_a0l0 = (a0l0 + a0l1 + a0l2) % M;
//             // a0l1 只能由a0l0加l得来
//             new_a1l0 = (a0l0 + a0l1 + a0l2 + a1l0 + a1l1 + a1l2) % M;
//             a0l2 = a0l1;
//             a0l1 = a0l0;
//             a1l2 = a1l1;
//             a1l1 = a1l0;

//             a0l0 = new_a0l0;
//             a1l0 = new_a1l0;
//         }

//         return (a0l0 + a0l1 + a0l2 + a1l0 + a1l1 + a1l2) % M;
//     }
// };

// 矩阵快速幂，想到可以拿大矩阵去乘小矩阵，这样就可以用快速幂.
// 思想和上面一样
class Solution {
   public:
    const int M = 1000000007;
    int checkRecord(int n) {
        long long mat[6][6] = {{1, 1, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1},
                               {0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0}};
        long long a[6] = {1, 1, 0, 1, 0, 0};
        long long res[6][6];
        for (int i = 0; i < 6; ++i)
            for (int j = 0; j < 6; ++j)
                if (i == j)
                    res[i][j] = 1;
                else
                    res[i][j] = 0;
        --n;
        while (n) {
            if (n & 1) matmult(res, mat);
            matmult(mat, mat);
            n >>= 1;
        }
        long long tot = 0;
        for (int i = 0; i < 6; ++i)
            for (int j = 0; j < 6; ++j) tot += res[i][j] * a[j];
        return (int)(tot % M);
    }

    void matmult(long long m1[][6], long long m2[][6]) {  // 矩阵乘法，复制来的
        long long temp[6][6];
        memset(temp, 0, sizeof(temp));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                for (int k = 0; k < 6; ++k) {
                    temp[i][j] += m1[i][k] * m2[k][j];
                }
                temp[i][j] %= M;
            }
        }
        memcpy(m1, temp, sizeof(temp));
    }
};

int main(void) {
    Solution* solution = new Solution();
    cout << solution->checkRecord(5) << "=94" << endl;
    cout << solution->checkRecord(6) << "=200" << endl;
    cout << solution->checkRecord(100) << "=985598218" << endl;
    return 0;
}