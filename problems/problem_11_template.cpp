#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 11. 盛最多水的容器
难度: Medium
标签: [数组, 双指针, 贪心]
LeetCode链接: https://leetcode.cn/problems/container-with-most-water/

📊 题目说明: 
本题需要图形化理解，建议先查看LeetCode链接中的图示说明。
图示展示了垂直线如何形成容器，以及如何计算容器面积。

题目描述:
给定一个长度为 n 的整数数组 height，有 n 条垂直线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i])。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。

说明：你不能倾斜容器。

示例 1:
输入：height = [1,8,6,2,5,4,8,3,7]
输出：49

示例 2:
输入：height = [1,1]
输出：1

约束条件:
- n == height.length
- 2 <= n <= 10^5
- 0 <= height[i] <= 10^4

思考要点:
1. 容器面积如何计算？
2. 暴力解法是什么？时间复杂度？
3. 有没有更优的解法？
4. 双指针为什么有效？
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        // TODO: 请在这里实现你的解法
        // 思考：如何计算两条线之间的容器面积？
        // min(height[i], height[j]) * (j - i)
        int left = 0; int right = height.size() - 1;
        int maxArea = 0;
        while(left < right) {
            int currentArea = min(height[left],height[right]) * (right - left);
            maxArea = max(maxArea,currentArea);
            if(height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 11. 盛最多水的容器" << endl;
    cout << "=========================" << endl;
    
    // 测试用例1
    vector<int> height1 = {1,8,6,2,5,4,8,3,7};
    int result1 = sol.maxArea(height1);
    int expected1 = 49;
    cout << "测试1: [1,8,6,2,5,4,8,3,7]" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: " << expected1 << endl;
    cout << (result1 == expected1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> height2 = {1,1};
    int result2 = sol.maxArea(height2);
    int expected2 = 1;
    cout << "测试2: [1,1]" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: " << expected2 << endl;
    cout << (result2 == expected2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    vector<int> height3 = {1,2,3,4,5};
    int result3 = sol.maxArea(height3);
    int expected3 = 6;
    cout << "测试3: [1,2,3,4,5]" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: " << expected3 << endl;
    cout << (result3 == expected3 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

int main() {
    cout << "🚀 LeetCode 11. 盛最多水的容器" << endl;
    cout << "==============================" << endl;
    cout << "请实现 Solution::maxArea 函数" << endl;
    cout << "完成后运行测试查看结果" << endl << endl;
    
    runTests();
    
    return 0;
}