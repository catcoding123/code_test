#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 198. 打家劫舍
难度: Medium
标签: [动态规划, 数组]
LeetCode链接: https://leetcode.cn/problems/house-robber/

题目描述:
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你不触动警报装置的情况下，
一夜之内能够偷窃到的最高金额。

示例 1:
输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。

示例 2:
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

约束条件:
- 1 <= nums.length <= 100
- 0 <= nums[i] <= 400

思考要点:
1. 这是什么类型的DP？与70题爬楼梯有什么区别？
2. 状态定义：dp[i] 表示什么含义？
3. 决策分析：对于每个房屋有几种选择？
4. 状态转移方程：如何表达"偷"与"不偷"的决策？
5. 边界条件：第1间房和第2间房怎么处理？

核心难点:
- 理解决策类DP：每步都要在多个选择中做最优决策
- 正确处理约束条件：相邻房屋不能同时偷
- 状态转移方程的推导：max(偷当前房, 不偷当前房)
*/

class Solution {
public:
    // 方法1: 递归 - 会超时，但有助理解问题本质
    int robRecursive(vector<int>& nums) {
        // TODO: 实现递归解法
        // 思考：对于第i间房，有偷和不偷两种选择
        // rob(i) = max(nums[i] + rob(i-2), rob(i-1))
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        return helper(nums, nums.size() - 1);
    }
    
private:
    int helper(vector<int>& nums, int i) {
        // TODO: 实现递归helper
        // 边界条件：i < 0 时返回0
        // 递归关系：max(偷当前房, 不偷当前房)
        if (i<0) return 0;
        return max(helper(nums,i-2)+ nums[i], helper(nums,i-1));
    }
    
public:
    // 方法2: 记忆化搜索 - 递归 + 缓存
    int robMemo(vector<int>& nums) {
        // TODO: 实现记忆化搜索
        vector<int> memo(nums.size(), -1);
        if (nums.size()==0) return 0;
        return helperMemo(nums, nums.size() - 1, memo);
    }
    
private:
    int helperMemo(vector<int>& nums, int i, vector<int>& memo) {
        // TODO: 实现记忆化递归
        // 检查缓存，递归计算，存储结果
        if (i<0) return 0;
        if(i==0) return nums[0];
        if(memo[i] !=-1) return memo[i];
        memo[i] = max(helperMemo(nums,i-2,memo) + nums[i], helperMemo(nums,i-1,memo)); // 这里需要赋值！！
        return memo[i];
    }
    
public:
    // 方法3: 动态规划 - 自底向上 ⭐ 推荐
    int robDP(vector<int>& nums) {
        // TODO: 实现动态规划解法
        // 1. 状态定义：dp[i] = 偷前i+1间房能得到的最大金额
        // 2. 状态转移：dp[i] = max(nums[i] + dp[i-2], dp[i-1])
        // 3. 边界条件：dp[0] = nums[0], dp[1] = max(nums[0], nums[1])
        // 4. 返回结果：dp[n-1]
        
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        vector<int> dp(n);
        // TODO: 初始化边界条件和填充dp数组
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for (int i=2;i<n;i++) {
            dp[i] = max(dp[i-2]+nums[i], dp[i-1]);
        } 
        return dp[n-1];
    }
    
    // 方法4: 动态规划空间优化 - O(1) 空间
    int robDPOptimized(vector<int>& nums) {
        // TODO: 实现空间优化版本
        // 观察：dp[i] 只依赖于 dp[i-1] 和 dp[i-2]
        // 所以只需要两个变量即可
        
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int prev2 = nums[0];        // dp[i-2]
        int prev1 = max(nums[0], nums[1]); // dp[i-1]
        
        // TODO: 使用滚动变量计算
        for(int i=2;i<n;i++) {
            int curr = max(nums[i]+prev2, prev1);
            prev2 = prev1; 
            prev1 = curr;
        }
        return prev1;
    }
    
    // 方法5: 状态机DP - 另一种思考角度 (进阶)
    int robStateMachine(vector<int>& nums) {
        // TODO: 实现状态机解法 (选做)
        // 定义两个状态：rob[i] = 偷第i间房的最大收益
        //              not_rob[i] = 不偷第i间房的最大收益
        
        return 0;
    }
    
    // 主函数 - 选择你想实现的方法
    int rob(vector<int>& nums) {
        // 推荐先实现动态规划，理解决策类DP的核心思想
        return robDP(nums);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 198. 打家劫舍" << endl;
    cout << "====================" << endl;
    
    // 测试用例1
    vector<int> nums1 = {1,2,3,1};
    int result1 = sol.rob(nums1);
    cout << "测试1: [1,2,3,1]" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 4" << endl;
    cout << (result1 == 4 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> nums2 = {2,7,9,3,1};
    int result2 = sol.rob(nums2);
    cout << "测试2: [2,7,9,3,1]" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 12" << endl;
    cout << (result2 == 12 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3: 单个房屋
    vector<int> nums3 = {5};
    int result3 = sol.rob(nums3);
    cout << "测试3: [5]" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 5" << endl;
    cout << (result3 == 5 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 两个房屋
    vector<int> nums4 = {2,1};
    int result4 = sol.rob(nums4);
    cout << "测试4: [2,1]" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 2" << endl;
    cout << (result4 == 2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 递增数组
    vector<int> nums5 = {1,2,3,4,5};
    int result5 = sol.rob(nums5);
    cout << "测试5: [1,2,3,4,5]" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 9" << endl;
    cout << (result5 == 9 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 决策类DP思路演示
void demonstrateDecisionDP() {
    cout << "\n📚 决策类DP思路演示" << endl;
    cout << "====================" << endl;
    
    vector<int> nums = {2,7,9,3,1};
    cout << "房屋金额: [";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "约束: 不能偷相邻的房屋" << endl << endl;
    
    cout << "💡 决策类DP核心思想：" << endl;
    cout << "对于每间房屋，小偷面临选择：偷 or 不偷？" << endl;
    cout << "- 偷第i间房：获得nums[i] + 前i-2间房的最优解" << endl;
    cout << "- 不偷第i间房：获得前i-1间房的最优解" << endl;
    cout << "- 选择更优的方案：dp[i] = max(nums[i] + dp[i-2], dp[i-1])" << endl << endl;
    
    cout << "🔍 手工计算过程：" << endl;
    int n = nums.size();
    vector<int> dp(n);
    
    // 边界条件
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    cout << "dp[0] = " << dp[0] << " (只有1间房，直接偷)" << endl;
    cout << "dp[1] = max(" << nums[0] << "," << nums[1] << ") = " << dp[1] << " (两间房选金额大的)" << endl;
    
    for (int i = 2; i < n; i++) {
        int rob_current = nums[i] + dp[i-2];    // 偷当前房
        int not_rob_current = dp[i-1];          // 不偷当前房
        dp[i] = max(rob_current, not_rob_current);
        
        cout << "dp[" << i << "] = max(" << nums[i] << "+" << dp[i-2] 
             << ", " << dp[i-1] << ") = max(" << rob_current 
             << ", " << not_rob_current << ") = " << dp[i];
        
        if (rob_current > not_rob_current) {
            cout << " (偷第" << i << "间房)" << endl;
        } else {
            cout << " (不偷第" << i << "间房)" << endl;
        }
    }
    
    cout << "\n🎯 结果：最大金额 = " << dp[n-1] << endl;
    
    // 追踪最优方案
    cout << "\n🔍 最优偷窃方案追踪：" << endl;
    vector<bool> solution(n, false);
    int i = n - 1;
    while (i >= 0) {
        if (i == 0) {
            solution[i] = true;
            break;
        }
        if (i == 1) {
            if (nums[1] > nums[0]) {
                solution[1] = true;
            } else {
                solution[0] = true;
            }
            break;
        }
        
        if (nums[i] + dp[i-2] > dp[i-1]) {
            solution[i] = true;
            i -= 2;
        } else {
            i -= 1;
        }
    }
    
    cout << "偷窃方案: ";
    for (int i = 0; i < n; i++) {
        if (solution[i]) {
            cout << "房屋" << i << "(金额:" << nums[i] << ") ";
        }
    }
    cout << endl;
}

// 复杂度分析和对比
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 递归解法:" << endl;
    cout << "   时间复杂度: O(2^n) - 每个位置都有偷/不偷两种选择" << endl;
    cout << "   空间复杂度: O(n) - 递归栈深度" << endl;
    cout << "   问题: 大量重复子问题" << endl << endl;
    
    cout << "2. 记忆化搜索:" << endl;
    cout << "   时间复杂度: O(n) - 每个位置只计算一次" << endl;
    cout << "   空间复杂度: O(n) - 缓存数组 + 递归栈" << endl;
    cout << "   优势: 避免重复计算" << endl << endl;
    
    cout << "3. 动态规划: ⭐ 推荐" << endl;
    cout << "   时间复杂度: O(n)" << endl;
    cout << "   空间复杂度: O(n)" << endl;
    cout << "   优势: 自底向上，逻辑清晰" << endl << endl;
    
    cout << "4. 空间优化DP:" << endl;
    cout << "   时间复杂度: O(n)" << endl;
    cout << "   空间复杂度: O(1) - 只用两个变量" << endl;
    cout << "   优势: 空间最优" << endl << endl;
    
    cout << "💡 与70题爬楼梯的区别：" << endl;
    cout << "- 爬楼梯：纯递推关系，f(n) = f(n-1) + f(n-2)" << endl;
    cout << "- 打家劫舍：决策问题，f(n) = max(选择A, 选择B)" << endl;
    cout << "- 决策类DP更复杂，需要分析所有可能的选择" << endl;
}

// 决策类DP概念讲解
void decisionDPConcepts() {
    cout << "\n🎓 决策类DP核心概念" << endl;
    cout << "===================" << endl;
    
    cout << "📖 什么是决策类DP？" << endl;
    cout << "在每个状态下，需要从多个选择中做出最优决策的动态规划问题" << endl;
    cout << "核心：状态转移不是简单的数学递推，而是选择最优方案" << endl << endl;
    
    cout << "🔑 决策类DP的特征：" << endl;
    cout << "1. 每个状态面临多种选择" << endl;
    cout << "2. 状态转移方程包含max/min函数" << endl;
    cout << "3. 需要分析约束条件对选择的影响" << endl << endl;
    
    cout << "📋 解题步骤：" << endl;
    cout << "1. 分析每个状态的所有可能选择" << endl;
    cout << "2. 确定每种选择的收益/代价" << endl;
    cout << "3. 写出状态转移方程：dp[i] = opt(choice1, choice2, ...)" << endl;
    cout << "4. 处理边界条件和约束" << endl << endl;
    
    cout << "🎯 打家劫舍的决策分析：" << endl;
    cout << "- 状态：dp[i] = 偷前i+1间房的最大金额" << endl;
    cout << "- 选择：偷第i间房 vs 不偷第i间房" << endl;
    cout << "- 约束：相邻房屋不能同时偷" << endl;
    cout << "- 转移：dp[i] = max(nums[i]+dp[i-2], dp[i-1])" << endl << endl;
    
    cout << "🌟 常见的决策类DP题目：" << endl;
    cout << "- 198. 打家劫舍 (选择/不选择)" << endl;
    cout << "- 121. 买卖股票 (买入/卖出/持有)" << endl;
    cout << "- 322. 零钱兑换 (选择不同面额硬币)" << endl;
    cout << "- 01背包问题 (物品选择/不选择)" << endl;
}

int main() {
    cout << "🚀 LeetCode 198. 打家劫舍" << endl;
    cout << "=========================" << endl;
    cout << "🔥 这是决策类动态规划的经典题目！" << endl;
    cout << "💡 重点掌握选择决策的DP思维" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    decisionDPConcepts();
    demonstrateDecisionDP();
    runTests();
    complexityAnalysis();
    
    return 0;
}