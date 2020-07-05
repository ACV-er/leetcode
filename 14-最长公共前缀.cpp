// 编写一个函数来查找字符串数组中的最长公共前缀。

// 如果不存在公共前缀，返回空字符串 ""。

// 示例 1:

// 输入: ["flower","flow","flight"]
// 输出: "fl"
// 示例 2:

// 输入: ["dog","racecar","car"]
// 输出: ""
// 解释: 输入不存在公共前缀。
// 说明:

// 所有输入只包含小写字母 a-z 。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/longest-common-prefix
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 水题，维护一个公共前缀即可

#include "iostream"
#include "string"
#include "vector"

using namespace std;

class Solution {
   public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() < 1) return string("");
        if (strs.size() == 1) return strs[0];
        int cur = 0, max = strs[0].length();

        for (int i = 1; i < strs.size(); i++) {
            cur = 0;
            while (cur < max && strs[0][cur] == strs[i][cur] &&
                   strs[0][cur] != '\0') {
                cur++;
            }
            max = cur;
            if (max == 0) {
                return string("");
            }
        }

        return strs[0].substr(0, max);
    }
};

int main(void) {
    Solution* solution = new Solution();
    cout << solution->longestCommonPrefix(
                *(new vector<string>{"flower", "flow", "flight"}))
         << endl;
    cout << solution->longestCommonPrefix(*(new vector<string>{"c", "c"}))
         << endl;
    return 0;
}