#include <iostream>
#include <stack>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 155. 最小栈
难度: Medium
标签: [栈, 设计]
LeetCode链接: https://leetcode.cn/problems/min-stack/

题目描述:
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:
- MinStack() 初始化堆栈对象。
- void push(int val) 将元素val推入堆栈。
- void pop() 删除堆栈顶部的元素。
- int top() 获取堆栈顶部的元素。
- int getMin() 获取堆栈中的最小元素。

示例 1:
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); --> 返回 -3.
minStack.pop();
minStack.top();    --> 返回 0.
minStack.getMin(); --> 返回 -2.

约束条件:
- -2^31 <= val <= 2^31 - 1
- pop、top 和 getMin 操作总是在非空栈上调用
- push, pop, top, and getMin 最多被调用 3 * 10^4 次

思考要点:
1. 如何在O(1)时间内获取最小值？
2. 当最小元素被pop时，如何快速找到下一个最小值？
3. 辅助栈的作用是什么？
4. 能否用一个栈实现？如何优化空间？
5. 边界情况：空栈、单元素、重复最小值

核心难点:
- 需要同时维护栈的基本操作和最小值查询
- 最小值可能随着pop操作而变化
- 必须保证所有操作都是O(1)时间复杂度
*/

class MinStack {
private:
    stack<int> mainStack;    // 主栈：存储所有元素
    stack<int> minStack;     // 辅助栈：存储对应的最小值
    
public:
    // 方法1: 双栈法 ⭐ 推荐 - 最直观易懂
    MinStack() {
        // 栈会自动初始化为空
    }
    
    void push(int val) {
        // 主栈总是push新元素
        mainStack.push(val);
        
        // 辅助栈：如果为空或新元素不大于当前最小值，则push
        if (minStack.empty() || val <= minStack.top()) { // 注意是小于等于
            minStack.push(val);
        }
    }
    
    void pop() {
        // 如果主栈顶元素等于最小值，辅助栈也要pop
        if (!mainStack.empty() && mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

// 方法2: 单栈存储差值法 (高级解法)
class MinStackOptimized {
private:
    stack<long long> st;  // 存储差值
    long long minVal;     // 当前最小值
    
public:
    MinStackOptimized() {
        // TODO: 实现优化版本
        // 核心思想：栈中存储val - minVal的差值
        // 当差值为负时，说明新元素是最小值
        minVal = 0;  // 初始化最小值
        st = stack<long long>();  // 初始化栈
    }
    
    void push(int val) {
        // TODO: 实现
        // 如果栈为空，直接设置最小值
        // 否则计算差值并根据情况更新最小值
        if (st.empty()) {
            minVal = val;  // 初始化最小值
            st.push(0);    // 第一个元素差值为0
        } else {
            st.push(val - minVal);  // 存储当前值与最小值的差
            if (val < minVal) {
                minVal = val;  // 更新最小值
            }
        }
    }
    
    void pop() {
        // TODO: 实现
        // 如果栈顶差值为负，需要恢复之前的最小值
        if (st.empty()) return;  // 栈为空时不操作
        long long topDiff = st.top();
        st.pop();
        if (topDiff < 0) {
            minVal -= topDiff;  // 恢复最小值
        }
    }

    int top() {
        // TODO: 实现
        // 根据差值和最小值计算真实的栈顶值
        if (st.empty()) return 0;  // 栈为空时返回0（或抛出异常）
        long long topDiff = st.top();
        if (topDiff >= 0) {
            return minVal + topDiff;  // 返回当前栈顶值
        } else {
            return minVal;  // 如果差值为负，说明栈顶就是最小值
        }   
    }
    
    int getMin() {
        return minVal;
    }
};

// 测试框架
void runTests() {
    cout << "🧪 测试 155. 最小栈" << endl;
    cout << "==================" << endl;
    
    // 测试用例1: 基本功能测试
    cout << "测试1: 基本操作" << endl;
    MinStack minStack;
    
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    
    cout << "push(-2), push(0), push(-3)" << endl;
    cout << "getMin(): " << minStack.getMin() << " (期望: -3)" << endl;
    
    minStack.pop();
    cout << "pop() 后:" << endl;
    cout << "top(): " << minStack.top() << " (期望: 0)" << endl;
    cout << "getMin(): " << minStack.getMin() << " (期望: -2)" << endl;
    cout << endl;
    
    // 测试用例2: 重复最小值
    cout << "测试2: 重复最小值" << endl;
    MinStack minStack2;
    
    minStack2.push(1);
    minStack2.push(1);
    minStack2.push(1);
    cout << "push(1), push(1), push(1)" << endl;
    cout << "getMin(): " << minStack2.getMin() << " (期望: 1)" << endl;
    
    minStack2.pop();
    cout << "pop() 后 getMin(): " << minStack2.getMin() << " (期望: 1)" << endl;
    cout << endl;
    
    // 测试用例3: 边界情况
    cout << "测试3: 单元素栈" << endl;
    MinStack minStack3;
    minStack3.push(42);
    cout << "push(42)" << endl;
    cout << "top(): " << minStack3.top() << " (期望: 42)" << endl;
    cout << "getMin(): " << minStack3.getMin() << " (期望: 42)" << endl;
}

// 算法演示
void demonstrateMinStack() {
    cout << "\n📚 最小栈算法演示" << endl;
    cout << "=================" << endl;
    
    cout << "双栈法核心思想:" << endl;
    cout << "1. 主栈：存储所有元素" << endl;
    cout << "2. 辅助栈：存储对应的最小值" << endl;
    cout << "3. 两个栈同步变化" << endl << endl;
    
    MinStack ms;
    cout << "操作序列演示:" << endl;
    
    cout << "push(-2)" << endl;
    ms.push(-2);
    cout << "  当前栈: [-2], 最小值: " << ms.getMin() << endl;
    
    cout << "push(0)" << endl;
    ms.push(0);
    cout << "  当前栈: [-2, 0], 最小值: " << ms.getMin() << endl;
    
    cout << "push(-3)" << endl;
    ms.push(-3);
    cout << "  当前栈: [-2, 0, -3], 最小值: " << ms.getMin() << endl;
    
    cout << "pop()" << endl;
    ms.pop();
    cout << "  当前栈: [-2, 0], 最小值: " << ms.getMin() << endl;
    
    cout << "top(): " << ms.top() << endl;
}

// 复杂度分析
void complexityAnalysis() {
    cout << "\n⚡ 复杂度分析" << endl;
    cout << "============" << endl;
    
    cout << "方法对比:" << endl;
    cout << "1. 双栈法:" << endl;
    cout << "   时间复杂度: 所有操作 O(1)" << endl;
    cout << "   空间复杂度: O(n) - 最坏情况需要两个n大小的栈" << endl;
    cout << "   优势: 实现简单直观" << endl << endl;
    
    cout << "2. 单栈存储差值法:" << endl;
    cout << "   时间复杂度: 所有操作 O(1)" << endl;
    cout << "   空间复杂度: O(n) - 只需一个栈" << endl;
    cout << "   优势: 空间优化，但实现复杂" << endl << endl;
    
    cout << "3. 单栈存储pair法:" << endl;
    cout << "   时间复杂度: 所有操作 O(1)" << endl;
    cout << "   空间复杂度: O(n) - 每个元素存储值和最小值" << endl;
    cout << "   优势: 实现简单，空间使用稳定" << endl << endl;
    
    cout << "💡 推荐: 面试时选择双栈法，清晰易懂" << endl;
}

int main() {
    cout << "🚀 LeetCode 155. 最小栈" << endl;
    cout << "=======================" << endl;
    cout << "🔥 这是栈设计的经典题目！" << endl;
    cout << "💡 重点掌握辅助栈的思想" << endl;
    cout << "📊 建议先查看LeetCode链接理解题意" << endl << endl;
    
    runTests();
    demonstrateMinStack();
    complexityAnalysis();
    
    return 0;
}