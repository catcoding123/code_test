#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 42. 接雨水
难度: Hard
标签: [数组, 双指针, 动态规划, 单调栈]
LeetCode链接: https://leetcode.cn/problems/trapping-rain-water/

📊 题目说明: 
本题需要图形化理解，建议先查看LeetCode链接中的图示说明。
图示展示了柱状图如何形成"凹槽"来接住雨水。

题目描述:
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能够接多少雨水。

示例 1:
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。

示例 2:
输入：height = [4,2,0,3,2,5]
输出：9

约束条件:
- n == height.length
- 1 <= n <= 2 * 10^4
- 0 <= height[i] <= 3 * 10^4

思考要点:
1. 每个位置能接多少雨水？
2. 雨水高度由什么决定？(左边最高 vs 右边最高)
3. 有哪些不同的解法？
4. 双指针解法的核心思想是什么？
5. 单调栈解法如何工作？

核心insight:
对于位置i，能接的雨水 = min(左边最高, 右边最高) - height[i]
关键是如何高效地计算每个位置的左边最高和右边最高。
*/

class Solution {
public:
    // 方法1: 暴力解法 - O(n²) 时间复杂度
    int trapBruteForce(vector<int>& height) {
        // TODO: 实现暴力解法
        // 对每个位置，找左边最高和右边最高
        return 0;
    }
    
    // 方法2: 动态规划 - O(n) 时间，O(n) 空间
    int trapDP(vector<int>& height) {
        // TODO: 实现DP解法
        // 预计算每个位置的左边最高和右边最高
        vector<int> leftmax(height.size(),0);
        vector<int> rightmax(height.size(),0);
        leftmax[0] = 0;
        rightmax[height.size()-1] = 0;
        for(int i = 1; i < height.size(); i++) {
           leftmax[i] = max(leftmax[i-1],height[i-1]);
        }
        for(int i=height.size()-2; i>=0; i--) {
           rightmax[i] = max(rightmax[i+1],height[i+1]);
        }
        int result = 0;
        for(int i=0; i<height.size(); i++) {
           int minh = min(leftmax[i],rightmax[i]);
           if(minh > height[i]) {
               result += minh - height[i];
           }
        }
        return result;
    }
    
    // 方法3: 双指针 - O(n) 时间，O(1) 空间
    int trapTwoPointers(vector<int>& height) {
        // TODO: 实现双指针解法
        // 核心思想：不需要知道确切的左右最高值，只需要知道哪边更小
        int left = 0;
        int right = height.size() - 1;
        int leftmax = 0;
        int rightmax = 0;
        int result = 0;
        while(left < right) {
            if(height[left] < height[right]) {
                if(height[left] >= leftmax) {
                    leftmax = height[left];
                } else {
                    result += leftmax - height[left]; // leftmax实际比left更左边
                }
                left++;
            } else {
                if(height[right] >= rightmax) {
                    rightmax = height[right];
                } else {
                    result += rightmax - height[right];
                }
                right--;
            }
        }
         return result;
    }
    
    // 方法4: 单调栈 - O(n) 时间，O(n) 空间
    int trapMonotonicStack(vector<int>& height) {
        // TODO: 实现单调栈解法
        // 维护一个递减的单调栈，遇到更高的柱子时计算接水量
        stack<int> stk;
        int n = height.size();
        int result = 0;
        for(int i=0;i<n;i++) {
            while(!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if(stk.empty()) {
                    break;
                }
                int left = stk.top(); // 已经弹出过了，这里就是左边的了
                // 计算面积
                int width = (i -left -1);
                int h = min(height[i], height[left]) - height[top];
                result += width * h;
            }
            stk.push(i); // stack是push 不是push_back
        }
        return result;
    }
    
    // 主函数 - 选择你想实现的方法
    int trap(vector<int>& height) {
        // 可以选择实现上面任意一种或多种方法
        return trapTwoPointers(height);  // 推荐从双指针开始
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 42. 接雨水" << endl;
    cout << "==================" << endl;
    
    // 测试用例1
    vector<int> height1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result1 = sol.trap(height1);
    int expected1 = 6;
    cout << "测试1: [0,1,0,2,1,0,1,3,2,1,2,1]" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: " << expected1 << endl;
    cout << (result1 == expected1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> height2 = {4,2,0,3,2,5};
    int result2 = sol.trap(height2);
    int expected2 = 9;
    cout << "测试2: [4,2,0,3,2,5]" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: " << expected2 << endl;
    cout << (result2 == expected2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3: 边界情况
    vector<int> height3 = {3,0,2,0,4};
    int result3 = sol.trap(height3);
    int expected3 = 7; // 0+0+1+2+0 = 3, 实际是 0+3+1+3+0 = 7
    cout << "测试3: [3,0,2,0,4]" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: " << expected3 << endl;
    cout << (result3 == expected3 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 比较不同解法的性能
void compareAlgorithms() {
    cout << "\n⚡ 算法性能对比" << endl;
    cout << "================" << endl;
    
    // 生成测试数据
    vector<int> largeHeight;
    int size = 1000;
    for (int i = 0; i < size; i++) {
        largeHeight.push_back(rand() % 100);
    }
    
    Solution sol;
    
    cout << "数据规模: " << size << " 个元素" << endl;
    cout << "方法对比:" << endl;
    cout << "1. 暴力解法: O(n²) 时间, O(1) 空间" << endl;
    cout << "2. 动态规划: O(n) 时间, O(n) 空间" << endl;
    cout << "3. 双指针: O(n) 时间, O(1) 空间 ⭐" << endl;
    cout << "4. 单调栈: O(n) 时间, O(n) 空间" << endl;
    cout << "\n推荐学习顺序: 双指针 → 动态规划 → 单调栈" << endl;
}

int main() {
    cout << "🚀 LeetCode 42. 接雨水" << endl;
    cout << "========================" << endl;
    cout << "🔥 这是一道经典Hard题目，有多种解法！" << endl;
    cout << "💡 建议先实现双指针解法，再挑战其他方法" << endl;
    cout << "📊 记得先查看LeetCode链接理解题意" << endl << endl;
    
    runTests();
    compareAlgorithms();
    
    return 0;
}