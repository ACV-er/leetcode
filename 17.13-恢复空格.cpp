// 哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。像句子"I
// reset the computer. It still didn’t
// boot!"已经变成了"iresetthecomputeritstilldidntboot"。在处理标点符号和大小写之前，你得先把它断成词语。当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。假设文章用sentence表示，设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。

// 注意：本题相对原题稍作改动，只需返回未识别的字符数

//  

// 示例：

// 输入：
// dictionary = ["looked","just","like","her","brother"]
// sentence = "jesslookedjustliketimherbrother"
// 输出： 7
// 解释： 断句后为"jess looked just like tim her brother"，共7个未识别字符。
// 提示：

// 0 <= len(sentence) <= 1000
// dictionary中总字符数不超过 150000。
// 你可以认为dictionary和sentence中只包含小写字母。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/re-space-lcci
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 看了下题解，用的后缀树，手写一个试试。

#include "cmath"
#include "iostream"
#include "string"
#include "unordered_map"
#include "vector"

using namespace std;

class Trie {
   public:
    unordered_map<char, Trie*> trie;
    bool isEnd = false;

    void insert(string s) {
        Trie* trie_node = this;
        const char* word = s.c_str();
        int curIdx = s.length();
        while (curIdx--) {
            if (trie_node->trie.find(word[curIdx]) == trie_node->trie.end()) {
                trie_node->trie[word[curIdx]] = new Trie();
            }
            trie_node = trie_node->trie[word[curIdx]];
        }
        trie_node->isEnd = true;
    }
};

class Solution {
   public:
    int respace(vector<string>& dictionary, string sentence) {
        Trie *root = new Trie(), *curPos;
        for (auto item : dictionary) {
            root->insert(item);
        }

        // 前i个字符失配多少个
        vector<int> dp(sentence.length() + 1);
        const char* word = sentence.c_str();
        int curIdx, st, len = sentence.length();

        dp[0] = 0;

        for (st = 0; st < len; st++) {
            dp[st + 1] = dp[st] + 1;

            if (root->trie.find(word[st]) != root->trie.end()) {
                curPos = root;
                for (curIdx = st; curIdx >= 0; curIdx--) {
                    // cout << "*" << curIdx << " " << st << endl;
                    if (curPos->trie.find(word[curIdx]) == curPos->trie.end()) {
                        // cout << "#" << curIdx << " " << st << endl;
                        break;
                    } else if (curPos->trie[word[curIdx]]->isEnd) {
                        // cout << curIdx << " " << st << endl;
                        dp[st + 1] = min(dp[st + 1], dp[curIdx]);
                    }
                    if (dp[st + 1] == 0) break;  // 不可能更新值了

                    curPos = curPos->trie[word[curIdx]];
                }
            }
        }
        // cout << "------" << endl;
        // for (auto item : dp) {
        //     cout << item << " ";
        // }
        // cout << endl << "------" << endl;
        return dp[len];
    }
};

int main(void) {
    Solution* solution = new Solution();
    vector<string> data = {"looked", "just", "like", "her", "brother"};
    auto rel = solution->respace(data, "jesslookedjustliketimherbrother");
    cout << rel << endl;
    return 0;
}