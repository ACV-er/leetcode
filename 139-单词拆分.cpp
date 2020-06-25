/*
给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s
是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。
示例 1：
    输入: s = "leetcode", wordDict = ["leet", "code"]
    输出: true
    解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。

示例 2：
    输入: s = "applepenapple", wordDict = ["apple", "pen"]
    输出: true
    解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
         注意你可以重复使用字典中的单词。

示例 3：
    输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-break
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include "iostream"
#include "string"
#include "unordered_set"
#include "vector"

using namespace std;

/*
动态规划，将前i个拆分为[可拆分的前j个+词典中的一个单词]。如果有符合条件的j则前i个可拆分。
此时欲得出前i个是否可拆分需要先分别得到前i-1、i-2...1、0个是否可拆分。
设前0个可拆分，则可根据这一结论可迭代得出结果。
*/
class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp = vector<bool>(s.size() + 1, false);
        dp[0] = true;  // 一般化，前0个可以被拆分。（其实不存在这种情况）
        unordered_set<string> h(wordDict.begin(), wordDict.end());

        // 遍历判断前i个是否可以被拆分，直至前s.size()个是否可以被拆分。
        // 这里可以优化，可被拆分的最小长度为字典中最短单词长度l，i可以从l开始遍历。
        for (int i = 1; i <= s.size(); i++) {
            // 前i个被分为前j个和j+1～i。遍历尝试每一种分法。
            // 前j个可以做一个优化，从字典中最短单词长度l开始，但是此时需要在一开始找出dp[i]为true的最小i。无法使用dp[0]==true这个一般化操作.
            for (int j = 0; j < i; j++) {
                // 前j个可以被拆分的情况下，j+1～i个若能则前i个可以被拆分。
                if (dp[j] && h.find(s.substr(j, i - j)) != h.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }
};

int main(void) {
    Solution* solution = new Solution();
    cout << solution->wordBreak("leetcode",
                                *(new vector<string>{"leet", "code"}))
         << endl;
    return 0;
}