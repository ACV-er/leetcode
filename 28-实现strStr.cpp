// 给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle
// 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

// 示例 1:

// 输入: haystack = "hello", needle = "ll"
// 输出: 2
// 示例 2:

// 输入: haystack = "aaaaa", needle = "bba"
// 输出: -1
// 说明:

// 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

// 对于本题而言，当 needle 是空字符串时我们应当返回 0
// 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/implement-strstr
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include "cmath"
#include "iostream"
#include "vector"

using namespace std;

class Solution {
   public:
    int strStr(string haystack, string needle) {
        int len = needle.size();
        if (len == 0) return 0;
        if (len > haystack.size()) return -1;

        int checkSum = 0, sum = 0;

        for (int i = 0; i < len; i++) {
            checkSum += needle[i];
            sum += haystack[i];
        }

        for (int i = len; i <= haystack.size(); i++) {
            if (checkSum == sum) {
                int nedIdx = len - 1;
                int haIdx = i - 1;

                while (nedIdx && needle[nedIdx--] == haystack[haIdx--])
                    ;
                if (nedIdx == 0 && needle[nedIdx] == haystack[haIdx]) {
                    return haIdx;
                }
            }
            sum += haystack[i] - haystack[i - len];
        }

        return -1;
    }
};

int main(void) {
    Solution* solution = new Solution();
    auto rel = solution->strStr("hello", "llo");
    cout << rel << endl;

    return 0;
}