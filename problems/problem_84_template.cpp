#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 84. 柱状图中最大的矩形
难度: Hard
标签: [栈, 数组, 单调栈]
LeetCode链接: https://leetcode.cn/problems/largest-rectangle-in-histogram/

题目描述:
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

示例 1:
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10

示例 2:
输入：heights = [2,4]
输出：4

约束条件:
- 1 <= heights.length <= 10^5
- 0 <= heights[i] <= 10^4

思考要点:
1. 暴力解法：对每个柱子向左右扩展找边界，时间复杂度？
 - O(n²) 时间复杂度，空间复杂度 O(1)
2. 单调栈：如何维护递增栈？时间复杂度？
 - O(n) 时间复杂度，空间复杂度 O(n)
2. 如何快速找到每个柱子的左右边界？
3. 单调栈是什么？如何维护递增栈？
 - 单调栈实际是提前维护一个左边，再不断去找他的右边界
4. 为什么要在数组两端添加0？
5. 如何处理栈中剩余元素？
   - 在处理完所有元素后，栈中可能还有元素，继续计算它们的矩形面积

核心难点:
- 需要找到每个柱子作为高度时的最大矩形面积
- 关键是快速确定左右边界（第一个比当前高度小的位置）
- 单调栈可以在O(n)时间内解决边界问题
*/

class Solution {
public:
    // 方法1: 暴力解法 - O(n²) 时间复杂度
    int largestRectangleAreaBruteForce(vector<int>& heights) {
        // TODO: 实现暴力解法
        // 对每个位置i，向左右扩展找到边界
        int maxArea = 0;
        int n = heights.size();
        
        // 你的代码实现
        for(int i = 0; i < n; i++) {
            int left = i, right = i;
            while (left > 0 && heights[left - 1] >= heights[i]) left--;
            while (right < n - 1 && heights[right + 1] >= heights[i]) right++;
            int width = right - left + 1;
            int area = width * heights[i];
            maxArea = max(maxArea, area);
        }
        
        return maxArea;
    }
    
    // 方法2: 单调栈 - O(n) 时间复杂度 ⭐ 推荐
    int largestRectangleAreaMonotonicStack(vector<int>& heights) {
        // TODO: 实现单调栈解法
        // 维护一个递增的栈，存储下标
        // 当遇到更小元素时，计算之前元素为高度的矩形面积
        
        stack<int> st;
        int maxArea = 0;
        
        // 技巧：在数组两端添加0，简化边界处理
        // 你的代码实现
        heights.insert(heights.begin(), 0);
        heights.push_back(0);

        for(int i=0;i< heights.size();i++) {
            while(!st.empty() && heights[st.top()] > heights[i]){
                int h = heights[st.top()];
                st.pop();
                int w = i -st.top() -1; // 宽度 = 右边界 - 左边界 - 1
                int area = h * w;
                maxArea = max(maxArea,area);
            }
            st.push(i);
        }
        // 处理完所有元素后，栈中可能还有元素
        while(!st.empty()) {
            int h = heights[st.top()];
            st.pop();
            int w = heights.size() - st.top() - 1; // 宽度 = 数组长度 - 左边界 - 1
            int area = h * w;
            maxArea = max(maxArea, area);
        }
        return maxArea;
    }
    
    // 方法3: 分治法 - O(n log n) 平均时间复杂度
    int largestRectangleAreaDivideConquer(vector<int>& heights) {
        // TODO: 实现分治解法（选做）
        // 找到最小高度，分割数组，递归求解
        
        return divideConquer(heights, 0, heights.size() - 1);
    }
    
private:
    int divideConquer(vector<int>& heights, int left, int right) {
        // TODO: 实现分治递归
        if (left > right) return 0; // 边界条件
        if (left == right) return heights[left]; // 只有一个元素
        int mid = left + (right - left) / 2;
        int minHeight = heights[mid];
        int minIndex = mid; // 找到中间位置的最小高度
        for (int i = left; i <= right; i++) {
            if (heights[i] < minHeight) {
                minHeight = heights[i];
                minIndex = i;
            }
        }
        // 计算以最小高度为基准的矩形面积
        int area = minHeight * (right - left + 1);
        // 递归计算左右两边的最大面积
        int leftArea = divideConquer(heights, left, minIndex - 1);
        int rightArea = divideConquer(heights, minIndex + 1, right);
        return max(area, max(leftArea, rightArea));
    }
    
public:
    // 主函数 - 选择你想实现的方法
    int largestRectangleArea(vector<int>& heights) {
        // 推荐先实现单调栈，它是最优解法
        return largestRectangleAreaMonotonicStack(heights);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 84. 柱状图中最大的矩形" << endl;
    cout << "===============================" << endl;
    
    // 测试用例1
    vector<int> heights1 = {2,1,5,6,2,3};
    int result1 = sol.largestRectangleArea(heights1);
    cout << "测试1: [2,1,5,6,2,3]" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: 10" << endl;
    cout << (result1 == 10 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    vector<int> heights2 = {2,4};
    int result2 = sol.largestRectangleArea(heights2);
    cout << "测试2: [2,4]" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: 4" << endl;
    cout << (result2 == 4 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3: 单调递增
    vector<int> heights3 = {1,2,3,4,5};
    int result3 = sol.largestRectangleArea(heights3);
    cout << "测试3: [1,2,3,4,5]" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: 9" << endl;
    cout << (result3 == 9 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 单调递减
    vector<int> heights4 = {5,4,3,2,1};
    int result4 = sol.largestRectangleArea(heights4);
    cout << "测试4: [5,4,3,2,1]" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: 9" << endl;
    cout << (result4 == 9 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 全部相同
    vector<int> heights5 = {3,3,3,3};
    int result5 = sol.largestRectangleArea(heights5);
    cout << "测试5: [3,3,3,3]" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: 12" << endl;
    cout << (result5 == 12 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 单调栈算法演示
void demonstrateMonotonicStack() {
    cout << "\n📚 单调栈算法演示" << endl;
    cout << "=================" << endl;
    
    vector<int> heights = {2,1,5,6,2,3};
    cout << "数组: [";
    for (int i = 0; i < heights.size(); i++) {
        cout << heights[i];
        if (i < heights.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "目标: 找到最大矩形面积" << endl << endl;
    
    cout << "单调栈过程 (栈存储下标，保持对应高度递增):" << endl;
    
    stack<int> st;
    int maxArea = 0;
    
    // 在两端添加0
    heights.insert(heights.begin(), 0);
    heights.push_back(0);
    
    for (int i = 0; i < heights.size(); i++) {
        cout << "\n步骤 " << i << ": 处理 heights[" << i << "] = " << heights[i] << endl;
        
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int w = i - st.top() - 1;
            int area = h * w;
            maxArea = max(maxArea, area);
            
            cout << "  弹出高度 " << h << ", 宽度 " << w << ", 面积 " << area << endl;
        }
        
        st.push(i);
        cout << "  入栈下标: " << i << endl;
        
        cout << "  当前栈: [";
        stack<int> temp = st;
        vector<int> stackElements;
        while (!temp.empty()) {
            stackElements.push_back(temp.top());
            temp.pop();
        }
        reverse(stackElements.begin(), stackElements.end());
        for (int j = 0; j < stackElements.size(); j++) {
            cout << stackElements[j] << "(" << heights[stackElements[j]] << ")";
            if (j < stackElements.size() - 1) cout << ",";
        }
        cout << "]" << endl;
        cout << "  当前最大面积: " << maxArea << endl;
    }
    
    cout << "\n🎯 最终结果: " << maxArea << endl;
}

// 复杂度分析
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 暴力解法:" << endl;
    cout << "   时间复杂度: O(n²)" << endl;
    cout << "   空间复杂度: O(1)" << endl;
    cout << "   适用场景: 小规模数据" << endl << endl;
    
    cout << "2. 单调栈: ⭐ 最优解法" << endl;
    cout << "   时间复杂度: O(n)" << endl;
    cout << "   空间复杂度: O(n)" << endl;
    cout << "   优势: 时间最优，每个元素最多入栈出栈一次" << endl << endl;
    
    cout << "3. 分治法:" << endl;
    cout << "   时间复杂度: O(n log n) 平均, O(n²) 最坏" << endl;
    cout << "   空间复杂度: O(log n)" << endl;
    cout << "   特点: 思路清晰但不是最优解" << endl << endl;
    
    cout << "💡 核心技巧:" << endl;
    cout << "- 在数组两端添加0，简化边界处理" << endl;
    cout << "- 维护递增栈，遇到小元素时弹栈计算" << endl;
    cout << "- 宽度 = 右边界 - 左边界 - 1" << endl;
}

int main() {
    cout << "🚀 LeetCode 84. 柱状图中最大的矩形" << endl;
    cout << "==================================" << endl;
    cout << "🔥 这是单调栈的经典题目！" << endl;
    cout << "💡 重点掌握单调栈的维护和应用" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    runTests();
    demonstrateMonotonicStack();
    complexityAnalysis();
    
    return 0;
}