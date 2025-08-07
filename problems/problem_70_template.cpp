#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 70. 爬楼梯
难度: Easy
标签: [动态规划, 数学, 记忆化搜索]
LeetCode链接: https://leetcode.cn/problems/climbing-stairs/

题目描述:
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

示例 1:
输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶

示例 2:
输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶

约束条件:
- 1 <= n <= 45

思考要点:
1. 这个问题的本质是什么？和斐波那契数列有什么关系？
2. 如何定义状态？dp[i] 表示什么含义？
3. 状态转移方程是什么？为什么是这样？
4. 边界条件是什么？dp[0] 和 dp[1] 应该是多少？
5. 能否优化空间复杂度？

核心难点:
- 理解动态规划的基本思想：大问题分解为小问题
- 找到正确的状态转移方程
- 处理边界条件
- 这是理解DP思维的最佳入门题目！
*/

class Solution {
public:
    // 方法1: 递归 - 会超时，但有助理解问题本质
    int climbStairsRecursive(int n) {
        // TODO: 实现递归解法
        // 思考：爬到第n阶的方法数 = ?
        // 基础情况：n=1 和 n=2 的答案是什么？
        if (n ==0) return 1;
        if (n ==1) return 1;
        if (n ==2) return 2;
        return climbStairsRecursive(n-2) + climbStairsRecursive(n-1);
    }
    /*
    执行 f(5) 的完整调用树：
    f(5)
    ├── f(4)
    │   ├── f(3)
    │   │   ├── f(2) → 2
    │   │   └── f(1) → 1
    │   └── f(2) → 2  ← f(2)又被计算了一次！
    └── f(3)  ← f(3)被完全重新计算！
        ├── f(2) → 2  ← f(2)第三次计算！
        └── f(1) → 1
    */
    // 这是递归和记忆搜索的区别
    
    // 方法2: 记忆化搜索 - 递归 + 缓存
    int climbStairsMemo(int n) {
        // TODO: 实现记忆化搜索
        // 使用数组或map缓存已计算的结果
        vector<int> memo(n + 1, -1);
        return helper(n,memo);
    }
    /*
    执行过程：
    f(5)
    ├── f(4)
    │   ├── f(3) → 计算得3，存入memo[3]=3
    │   └── f(2) → 返回2
    │   计算得5，存入memo[4]=5
    └── f(3) → 直接从memo[3]返回3，不再递归！
    计算得8
    */
    //这里的"缓存"只是在调用栈中临时存在，函数返回后就消失了。而记忆化搜索是在专门的数组中永久保存，可以跨函数调用使用。
    // 完全正确！这是递归的核心特性 - 深度优先，后进先出。，所以f(5)中的f（3）先计算

private:
    int helper(int n, vector<int>& memo) {
        // TODO: 实现递归helper函数
        // 如果已经计算过，直接返回缓存结果
        if (n <= 1) return 1;
        if (n == 2) return 2;
        if (memo[n] != -1) return memo[n];  // 已计算过
        memo[n] = helper(n-1, memo) + helper(n-2, memo);
        return memo[n];
    }
    
public:
    // 方法3: 动态规划 - 自底向上 ⭐ 推荐
    int climbStairsDP(int n) {
        // TODO: 实现动态规划解法
        // 1. 定义状态：dp[i] 表示爬到第i阶的方法数
        // 2. 状态转移：dp[i] = dp[i-1] + dp[i-2]
        // 3. 边界条件：dp[0] = ?, dp[1] = ?
        // 4. 返回结果：dp[n]
        
        if (n <= 1) return 1;
        if (n == 2) return 2;
        
        vector<int> dp(n + 1);
        // TODO: 初始化边界条件
        dp[0] = 1; dp[1] = 1; dp[2] = 2;  // 需要初始化
        // TODO: 填充dp数组
        for(int i=3;i<=n;i++) {
            dp[i] = dp[i-2] + dp[i-1];
        }  
        return dp[n];
    }
    
    // 方法4: 动态规划空间优化 - O(1) 空间
    int climbStairsDPOptimized(int n) {
        // TODO: 实现空间优化版本
        // 观察：dp[i] 只依赖于 dp[i-1] 和 dp[i-2]
        // 所以只需要两个变量即可
        
        if (n <= 1) return 1;
        if (n==2) return 2;
        int prev2 = 1; // dp[i-2]
        int prev1 = 1; // dp[i-1]
        
        // TODO: 使用滚动变量计算
        for(int i=2;i<=n;i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1= curr;
        }
        return prev1;
    }
    
    // 方法5: 数学公式 - 斐波那契通项公式 (选做)
    int climbStairsMath(int n) {
        // TODO: 实现数学公式解法
        // 这实际上是斐波那契数列：F(n+1)
        // 可以用通项公式或矩阵快速幂
        
        return 0;
    }
    
    // 主函数 - 选择你想实现的方法
    int climbStairs(int n) {
        // 推荐先实现动态规划，它是核心思想
        return climbStairsDP(n);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 70. 爬楼梯" << endl;
    cout << "==================" << endl;
    
    // 测试用例1
    int n1 = 2;
    int result1 = sol.climbStairs(n1);
    cout << "测试1: n = " << n1 << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 2" << endl;
    cout << (result1 == 2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    int n2 = 3;
    int result2 = sol.climbStairs(n2);
    cout << "测试2: n = " << n2 << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 3" << endl;
    cout << (result2 == 3 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    int n3 = 4;
    int result3 = sol.climbStairs(n3);
    cout << "测试3: n = " << n3 << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 5" << endl;
    cout << (result3 == 5 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4
    int n4 = 5;
    int result4 = sol.climbStairs(n4);
    cout << "测试4: n = " << n4 << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 8" << endl;
    cout << (result4 == 8 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 较大的n
    int n5 = 10;
    int result5 = sol.climbStairs(n5);
    cout << "测试5: n = " << n5 << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 89" << endl;
    cout << (result5 == 89 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 动态规划思路演示
void demonstrateDP() {
    cout << "\n📚 动态规划思路演示" << endl;
    cout << "===================" << endl;
    
    int n = 5;
    cout << "问题：爬到第" << n << "阶有多少种方法？" << endl;
    cout << "每次可以爬1阶或2阶" << endl << endl;
    
    cout << "💡 核心思想：" << endl;
    cout << "要爬到第n阶，必须从第(n-1)阶爬1步，或从第(n-2)阶爬2步" << endl;
    cout << "所以：f(n) = f(n-1) + f(n-2)" << endl << endl;
    
    cout << "🔍 手工计算过程：" << endl;
    vector<int> dp(n + 1);
    dp[0] = 1; // 0阶有1种方法（不爬）
    dp[1] = 1; // 1阶有1种方法
    
    cout << "dp[0] = " << dp[0] << " (边界：0阶有1种方法)" << endl;
    cout << "dp[1] = " << dp[1] << " (边界：1阶有1种方法)" << endl;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
        cout << "dp[" << i << "] = dp[" << (i-1) << "] + dp[" << (i-2) << "] = " 
             << dp[i-1] << " + " << dp[i-2] << " = " << dp[i] << endl;
    }
    
    cout << "\n🎯 结果：爬到第" << n << "阶有 " << dp[n] << " 种方法" << endl;
    
    cout << "\n📈 序列观察：1, 1, 2, 3, 5, 8, 13, 21..." << endl;
    cout << "这就是著名的斐波那契数列！" << endl;
}

// 复杂度分析和优化
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 递归解法:" << endl;
    cout << "   时间复杂度: O(2^n) - 指数级，会超时" << endl;
    cout << "   空间复杂度: O(n) - 递归栈深度" << endl;
    cout << "   问题: 重复计算大量子问题" << endl << endl;
    
    cout << "2. 记忆化搜索:" << endl;
    cout << "   时间复杂度: O(n) - 每个子问题只计算一次" << endl;
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
    
    cout << "5. 数学公式:" << endl;
    cout << "   时间复杂度: O(log n) - 使用矩阵快速幂" << endl;
    cout << "   空间复杂度: O(1)" << endl;
    cout << "   优势: 时间最优，但实现复杂" << endl << endl;
    
    cout << "💡 学习建议:" << endl;
    cout << "- 先理解递归思路" << endl;
    cout << "- 再掌握DP自底向上" << endl;
    cout << "- 最后学会空间优化" << endl;
}

// DP核心概念讲解
void dpConcepts() {
    cout << "\n🎓 动态规划核心概念" << endl;
    cout << "===================" << endl;
    
    cout << "📖 什么是动态规划？" << endl;
    cout << "Dynamic Programming (DP) 是解决最优化问题的算法思想" << endl;
    cout << "核心：将复杂问题分解为简单子问题，避免重复计算" << endl << endl;
    
    cout << "🔑 DP的关键要素：" << endl;
    cout << "1. 最优子结构：问题的最优解包含子问题的最优解" << endl;
    cout << "2. 重叠子问题：递归过程中会重复计算相同的子问题" << endl;
    cout << "3. 状态转移方程：描述状态之间的关系" << endl << endl;
    
    cout << "📋 DP解题步骤：" << endl;
    cout << "1. 定义状态：dp[i] 表示什么？" << endl;
    cout << "2. 找转移方程：dp[i] 与之前状态的关系" << endl;
    cout << "3. 确定边界：最小子问题的答案" << endl;
    cout << "4. 计算顺序：确保依赖的子问题已解决" << endl << endl;
    
    cout << "🎯 爬楼梯的DP分析：" << endl;
    cout << "- 状态：dp[i] = 爬到第i阶的方法数" << endl;
    cout << "- 转移：dp[i] = dp[i-1] + dp[i-2]" << endl;
    cout << "- 边界：dp[0] = 1, dp[1] = 1" << endl;
    cout << "- 顺序：从小到大计算" << endl;
}

int main() {
    cout << "🚀 LeetCode 70. 爬楼梯" << endl;
    cout << "======================" << endl;
    cout << "🔥 这是动态规划的入门经典题目！" << endl;
    cout << "💡 重点掌握DP的基本思想和状态转移" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    dpConcepts();
    demonstrateDP();
    runTests();
    complexityAnalysis();
    
    return 0;
}