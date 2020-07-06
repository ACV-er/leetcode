// 给定一个包含 n
// 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素
// a，b，c 和 d ，使得 a + b + c +
// d 的值与 target 相等？找出所有满足条件且不重复的四元组。

// 注意：

// 答案中不可以包含重复的四元组。

// 示例：

// 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

// 满足要求的四元组集合为：
// [
//   [-1,  0, 0, 1],
//   [-2, -1, 1, 2],
//   [-2,  0, 0, 2]
// ]

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/4sum
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 2数，3数，4数，太烦了。直接写n数之和的写法吧

#include "algorithm"
#include "iostream"
#include "iterator"
#include "vector"

using namespace std;

class Solution {
   public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return NSum(nums, target, pair<int, int>{0, nums.size() - 1}, 4);
    }

    // pos分别为左右起点（闭区间）, nums必须为升序
    vector<vector<int>> NSum(vector<int>& nums, int target, pair<int, int> pos,
                             int n) {
        int left = pos.first, right = pos.second;
        // cout << "left:" << left << " right:" << right << endl;
        vector<vector<int>> rel = {};

        // 优化，2数之和双指针非常快，右指针不用弹回到right，因为左指针单调
        if (n == 2) {
            int sum;
            while (left < right) {
                sum = nums[left] + nums[right];
                if (sum < target) {
                    left++;
                } else if (sum > target) {
                    right--;
                } else {
                    vector<int> tmp = {nums[left], nums[right]};
                    rel.push_back(tmp);
                    left++, right--;

                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    };
                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                }
            }
            // cout << n << "-----" << endl;
            // for (auto item : rel) {
            //     for (auto value : item) {
            //         cout << value << " ";
            //     }
            //     cout << endl;
            // }
            // cout << "------" << endl;
            return rel;
        }
        vector<vector<int>> tmp;

        for (int i = left; i <= right;) {  // 此处自增写在循环末，去重
            if (target < nums[i] * n) break;
            tmp = NSum(nums, target - nums[i], pair<int, int>{i + 1, right},
                       n - 1);
            if (tmp.size() > 0) {
                for (vector<int> item : tmp) {
                    item.insert(item.begin(), nums[i]);
                    rel.push_back(item);
                }
            }
            i++;
            while (i <= right && nums[i] == nums[i - 1]) {
                i++;
            }
        }
        // cout << n << "-----" << endl;
        // for (auto item : rel) {
        //     for (auto value : item) {
        //         cout << value << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "------" << endl;
        return rel;
    }
};

int main(void) {
    Solution* solution = new Solution();
    for (vector<int> item : solution->fourSum(
             *(new vector<int>{-5, -4, -3, -2, 1, 3, 3, 5}), -11)) {
        for (int value : item) {
            cout << value << " ";
        }
        cout << endl;
    }
    return 0;
}