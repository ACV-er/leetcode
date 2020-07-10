// 给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格
// 。​

// 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

// 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
// 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
// 示例:

// 输入: [1,2,3,0,2]
// 输出: 3
// 解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include "cmath"
#include "iostream"
#include "vector"

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 0) return 0;

        int buy = 0, sell = 0, cool = 0, yesterday_sell = 0;

        buy = -prices[0];
        sell = cool = yesterday_sell = 0;

        for (int i = 1; i < len; i++) {
            yesterday_sell = sell;
            sell = max(buy + prices[i], yesterday_sell);
            buy = max(cool - prices[i], buy);
            cool = max(yesterday_sell, cool);
        }

        return max(sell, cool);
    }
};

int main(void) {
    Solution* solution = new Solution();
    vector<int> data = {1, 2, 3, 0, 2};
    auto rel = solution->maxProfit(data);
    cout << rel << endl;

    return 0;
}