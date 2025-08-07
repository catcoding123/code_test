#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <set>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 239. 滑动窗口最大值
难度: Hard
标签: [队列, 数组, 滑动窗口, 单调队列, 堆]
LeetCode链接: https://leetcode.cn/problems/sliding-window-maximum/

题目描述:
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。

示例 1:
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7



3 -1
3 -1 -3
5
5 3
6
7


示例 2:
输入：nums = [1], k = 1
输出：[1]

约束条件:
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- 1 <= k <= nums.length

思考要点:
1. 暴力解法：每个窗口都遍历找最大值，时间复杂度？
2. 如何在O(1)时间内获取窗口最大值？
3. 单调队列是什么？如何维护？
4. 大顶堆可以解决吗？有什么问题？
5. 多重集合(multiset)的解法如何？

核心难点:
- 需要在滑动过程中高效维护窗口内的最大值
- 当窗口滑动时，需要快速删除过期元素，添加新元素
*/

class Solution {
public:
    // 方法1: 暴力解法 - O(nk) 时间复杂度
    vector<int> maxSlidingWindowBruteForce(vector<int>& nums, int k) {
        // TODO: 实现暴力解法
        // 对每个窗口位置，遍历k个元素找最大值
        vector<int> result;
        
        // 你的代码实现
        
        return result;
    }
    
    // 方法2: 单调双端队列 - O(n) 时间复杂度 ⭐ 推荐
    vector<int> maxSlidingWindowMonotonicDeque(vector<int>& nums, int k) {
        // TODO: 实现单调队列解法
        // 维护一个递减的双端队列，存储数组下标
        // 队首永远是当前窗口的最大值的下标
        
        vector<int> result;
        deque<int> dq;  // 存储下标，保持递减顺序
        // 你的代码实现
        int i = 0;
        for (; i < nums.size(); i++) {
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();  // 移除过期元素
            }
            while(!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();  // 保持递减顺序
            }
            dq.push_back(i);  // 添加当前元素下标
            if (i >= k - 1) { // 这样就可以避免第一次窗口未满的情况
                // 当窗口满时，添加最大值到结果
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
    
    // 方法3: 优先队列(大顶堆) - O(n log n) 时间复杂度
    vector<int> maxSlidingWindowPriorityQueue(vector<int>& nums, int k) {
        // TODO: 实现优先队列解法
        // 使用大顶堆，但需要处理过期元素问题
        
        vector<int> result;
        priority_queue<pair<int, int>> pq;  // (值, 下标) 按照值排序的

        // 你的代码实现
        for (int i=0; i<nums.size(); i++) {
            pq.push({nums[i],i});  //直到为什么要pair么？

            while(!pq.empty() && pq.top().second <= i-k) {
                pq.pop();
            }
            if (i >= k -1) {
                result.push_back(pq.top().first);
            }
         }
        // 注意：这里的时间复杂度是O(n log n)，因为每次插入和删除堆元素都需要log n时间
        // 但由于我们需要处理过期元素，实际性能可能不如单调队列
        // 这是因为堆无法高效地删除过期元素，导致每次都需要遍历堆来清理过期元素
        return result;
    }
    
    // 方法4: 多重集合 - O(n log k) 时间复杂度
    vector<int> maxSlidingWindowMultiset(vector<int>& nums, int k) {
        // TODO: 实现multiset解法
        // 使用multiset维护窗口内元素，自动排序
        
        vector<int> result;
        multiset<int> window;
        
        // 你的代码实现
        
        return result;
    }
    
    // 主函数 - 选择你想实现的方法
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 推荐先实现单调队列，它是最优解法
        return maxSlidingWindowMonotonicDeque(nums, k);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 239. 滑动窗口最大值" << endl;
    cout << "============================" << endl;
    
    // 测试用例1
    vector<int> nums1 = {1,3,-1,-3,5,3,6,7};
    int k1 = 3;
    vector<int> result1 = sol.maxSlidingWindow(nums1, k1);
    vector<int> expected1 = {3,3,5,5,6,7};
    cout << "测试1: [1,3,-1,-3,5,3,6,7], k=3" << endl;
    cout << "你的结果: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望结果: [3,3,5,5,6,7]" << endl;
    cout << (result1 == expected1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> nums2 = {1};
    int k2 = 1;
    vector<int> result2 = sol.maxSlidingWindow(nums2, k2);
    vector<int> expected2 = {1};
    cout << "测试2: [1], k=1" << endl;
    cout << "你的结果: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望结果: [1]" << endl;
    cout << (result2 == expected2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3: 递减数组
    vector<int> nums3 = {7,6,5,4,3,2,1};
    int k3 = 3;
    vector<int> result3 = sol.maxSlidingWindow(nums3, k3);
    vector<int> expected3 = {7,6,5,4,3};
    cout << "测试3: [7,6,5,4,3,2,1], k=3" << endl;
    cout << "你的结果: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望结果: [7,6,5,4,3]" << endl;
    cout << (result3 == expected3 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 单调队列算法演示
void demonstrateMonotonicDeque() {
    cout << "\n📚 单调队列算法演示" << endl;
    cout << "===================" << endl;
    
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    cout << "数组: [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "], k=" << k << endl;
    cout << "目标: 找到每个大小为" << k << "的滑动窗口的最大值" << endl << endl;
    
    deque<int> dq;  // 存储下标
    vector<int> result;
    
    cout << "单调队列过程 (队列存储下标，保持对应值递减):" << endl;
    
    for (int i = 0; i < nums.size(); i++) {
        cout << "\n步骤 " << (i + 1) << ": 处理 nums[" << i << "] = " << nums[i] << endl;
        
        // 移除过期元素
        while (!dq.empty() && dq.front() <= i - k) {
            cout << "  移除过期下标: " << dq.front() << " (值=" << nums[dq.front()] << ")" << endl;
            dq.pop_front();
        }
        
        // 维护单调性
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            cout << "  移除较小值下标: " << dq.back() << " (值=" << nums[dq.back()] << ")" << endl;
            dq.pop_back();
        }
        
        dq.push_back(i);
        cout << "  添加当前下标: " << i << " (值=" << nums[i] << ")" << endl;
        
        cout << "  当前队列: [";
        for (int j = 0; j < dq.size(); j++) {
            cout << dq[j] << "(" << nums[dq[j]] << ")";
            if (j < dq.size() - 1) cout << ",";
        }
        cout << "]" << endl;
        
        if (i >= k - 1) {
            int maxVal = nums[dq.front()];
            result.push_back(maxVal);
            cout << "  窗口 [" << (i-k+1) << "," << i << "] 最大值: " << maxVal << endl;
        }
    }
    
    cout << "\n🎯 最终结果: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

// 算法复杂度对比
void compareAlgorithms() {
    cout << "\n⚡ 算法复杂度对比" << endl;
    cout << "=================" << endl;
    
    cout << "问题规模: n=" << "数组长度" << ", k=" << "窗口大小" << endl << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 暴力解法:" << endl;
    cout << "   时间复杂度: O(n×k)" << endl;
    cout << "   空间复杂度: O(1)" << endl;
    cout << "   适用场景: k很小时" << endl << endl;
    
    cout << "2. 单调队列: ⭐ 最优解法" << endl;
    cout << "   时间复杂度: O(n)" << endl;
    cout << "   空间复杂度: O(k)" << endl;
    cout << "   优势: 时间最优，空间最优" << endl << endl;
    
    cout << "3. 优先队列(堆):" << endl;
    cout << "   时间复杂度: O(n log n)" << endl;
    cout << "   空间复杂度: O(n)" << endl;
    cout << "   缺点: 无法高效删除过期元素" << endl << endl;
    
    cout << "4. 多重集合(multiset):" << endl;
    cout << "   时间复杂度: O(n log k)" << endl;
    cout << "   空间复杂度: O(k)" << endl;
    cout << "   优势: 实现简单，性能尚可" << endl << endl;
    
    cout << "💡 学习建议: 单调队列 → multiset → 优先队列" << endl;
}

int main() {
    cout << "🚀 LeetCode 239. 滑动窗口最大值" << endl;
    cout << "=================================" << endl;
    cout << "🔥 这是滑动窗口 + 单调队列的经典题目！" << endl;
    cout << "💡 重点掌握单调队列的维护机制" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    runTests();
    demonstrateMonotonicDeque();
    compareAlgorithms();
    
    return 0;
}