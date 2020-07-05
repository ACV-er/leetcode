// 给定一个字符串 (s) 和一个字符模式 (p)
// ，实现一个支持 '?' 和 '*' 的通配符匹配。

// '?' 可以匹配任何单个字符。
// '*' 可以匹配任意字符串（包括空字符串）。
// 两个字符串完全匹配才算匹配成功。

// 说明:

//     s 可能为空，且只包含从 a-z 的小写字母。
//     p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。

// 示例 1:
// 输入:
//     s = "aa"
//     p = "a"
// 输出: false
// 解释: "a" 无法匹配 "aa" 整个字符串。

// 示例 2:
// 输入:
//     s = "aa"
//     p = "*"
// 输出: true
// 解释: '*' 可以匹配任意字符串。

// 示例 3:
// 输入:
//     s = "cb"
//     p = "?a"
// 输出: false
// 解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。

// 示例 4:
// 输入:
//     s = "adceb"
//     p = "*a*b"
// 输出: true
// 解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".

// 示例 5:
// 输入:
//     s = "acdcb"
//     p = "a*c?b"
// 输出: false

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/wildcard-matching
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include "iostream"
#include "string"
#include "vector"

using namespace std;

// 递归超时，*会一直往后匹配，如果*过多，则会大量递归。
// class Solution {
//    public:
//     bool isMatch(string s, string p) { return isMatch(s.c_str(), p.c_str());
//     } bool isMatch(const char* s, const char* p) {
//         if (*p == '*') {  // 处理多*连续
//             while (*(p + 1) == '*') {
//                 p++;
//             }
//         }
//         if (*p == '\0') {  // 模式匹配完毕
//             return *s == '\0';
//         }
//         if (*s == '\0') {  // 模式末尾是*
//             return (*p == '*') && (*(p + 1) == '\0');
//         }
//         if (*p == *s || *p == '?') {  // 普通匹配成功
//             return isMatch(s + 1, p + 1);
//         }
//         if (*p == '*') {  // 通配任意字符串
//             return isMatch(s, p + 1) || isMatch(s + 1, p);
//         }

//         return false;  // 匹配失败
//     }
// };

// 动态规划 可以通过
// class Solution {
//    public:
//     bool isMatch(string s, string p) {
//         int m = s.length();  // 保存长度，之后很多地方会用到
//         int n = p.length();

//         vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

//         // 空字符串必然可以匹配空字符串
//         dp[0][0] = true;

//         // 避免之后的遍历中i=0出现需要通过dp[i-1][x]作为依据判断
//         for (int i = 0; i < n; i++) {
//             if (p[i] == '*') {
//                 dp[i + 1][0] = true;
//             } else {
//                 break;
//             }
//         }

//         // 其实可以只要一个mx2规格的dp数组

//         // 每次判断匹配串的前i个能否匹配字符串的前1， 2, 3 ... m个
//         for (int i = 1; i <= n; i++) {
//             for (int j = 1; j <= m; j++) {
//                 // 第一种情况是？匹配或者相同匹配
//                 // 第二种情况是*匹配
//                 if (((p[i - 1] == '?' || s[j - 1] == p[i - 1]) &&
//                      dp[i - 1][j - 1]) ||

//                     (p[i - 1] == '*' &&
//                      (dp[i - 1][j - 1] || dp[i][j - 1] || dp[i - 1][j]))) {
//                     dp[i][j] = true;
//                 }
//             }
//         }

//         return dp[n][m];
//     }
// };

// 贪心，尽快匹配完模式串，比动态规划快
class Solution {
   public:
    bool isMatch(string s, string p) {
        int s_cur = 0, p_cur = 0;

        // 设置为0则不知道是从来没有被动过还是被重置为0了
        int s_start = -1, p_start = -1;
        int s_len = s.length(), p_len = p.length();
        while (s_cur < s_len) {
            if (s[s_cur] == p[p_cur] || (p_cur < p_len && p[p_cur] == '?')) {
                s_cur++, p_cur++;
            } else if (p_cur < p_len && p[p_cur] == '*') {  // 默认*匹配空字符串
                s_start = s_cur;
                p_start = ++p_cur;
            } else if (s_start >= 0) {
                // 匹配过*，后面匹配失败，则*比上一次再多匹配一个字符
                s_cur = ++s_start;
                p_cur = p_start;
            } else {
                // 回天乏术，失败
                return false;
            }
        }
        // 可能末尾有多个*，去除
        while (p[p_cur] == '*') {
            p_cur++;
        }

        return p_cur == p_len;
    }
};

int main(void) {
    Solution* solution = new Solution();
    cout << solution->isMatch(string("acdcb"), string("a*c?b")) << "=0" << endl;
    cout << solution->isMatch(string("cb"), string("?a")) << "=0" << endl;
    cout << solution->isMatch(string("adceb"), string("*a*b")) << "=1" << endl;
    cout << solution->isMatch(string("ad"), string("*a****")) << "=1" << endl;
    cout << solution->isMatch(string("aa"), string("*")) << "=1" << endl;
    cout << solution->isMatch(string("acbabc"), string("a*b*d")) << "=0"
         << endl;
    cout << solution->isMatch(string(""), string("*")) << "=1" << endl;

    return 0;
}