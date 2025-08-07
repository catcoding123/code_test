#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <cassert>
#include <chrono>
using namespace std;

/*
题目: 3. 无重复字符的最长子串
难度: Medium
标签: [哈希表, 字符串, 滑动窗口]
LeetCode链接: https://leetcode.cn/problems/longest-substring-without-repeating-characters/

题目描述:
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

约束条件:
- 0 <= s.length <= 5 * 10^4
- s 由英文字母、数字、符号和空格组成

思考要点:
1. 什么是滑动窗口？
2. 窗口什么时候扩大？什么时候收缩？
3. 如何快速检测重复字符？
4. 如何更新窗口的左边界？

滑动窗口核心思想:
- 用双指针维护一个窗口 [left, right]
- right指针不断向右扩展窗口
- 当窗口内出现重复字符时，移动left指针收缩窗口
- 在每个有效窗口处更新答案
*/

class Solution {
public:
    // 方法1: 暴力解法 - O(n³) 时间复杂度
    int lengthOfLongestSubstringBruteForce(string s) {
        // TODO: 实现暴力解法 (可选)
        // 枚举所有子串，检查是否包含重复字符
        return 0;
    }
    
    // 方法2: 滑动窗口 + 哈希集合 - O(n) 时间复杂度
    int lengthOfLongestSubstringHashSet(string s) {
        // 用unordered_set检测重复字符
        // 遇到重复字符时，逐个移除左边字符直到无重复
        unordered_set<char> uniq_set;
        int left = 0;
        int right = 0;
        int max_len = 0;
        
        while(right < s.length()) {
            // 如果当前字符已存在，收缩窗口
            while(uniq_set.find(s[right]) != uniq_set.end()) {
                uniq_set.erase(s[left]);
                left++;
            }
            // 添加当前字符到窗口
            uniq_set.insert(s[right]);
            right++;

            // 更新最大长度
            max_len = max(max_len, right - left);
        }
        return max_len;
    }
    
    // 方法3: 滑动窗口 + 哈希表优化 - O(n) 时间复杂度
    int lengthOfLongestSubstringHashMap(string s) {
        // 用unordered_map记录字符最后出现的位置
        // 遇到重复字符时，直接跳转到重复字符的下一个位置
        unordered_map<char, int> char_map;
        int left = 0;
        int result = 0;
        
        for(int right = 0; right < s.length(); right++) {
            // 如果字符已存在，更新左边界
            if(char_map.find(s[right]) != char_map.end()) {
                left = max(left, char_map[s[right]] + 1); // s[right] 这里实际是上一个位置，不是最后的位置
            }
            // 记录字符位置
            char_map[s[right]] = right;
            // 更新结果
            result = max(result, right - left + 1);
        }
        return result;
    }
    
    // 主函数 - 选择你想实现的方法
    int lengthOfLongestSubstring(string s) {
        // 推荐先实现 HashSet 版本，再挑战 HashMap 优化版本
        return lengthOfLongestSubstringHashSet(s);
    }
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 3. 无重复字符的最长子串" << endl;
    cout << "==============================" << endl;
    
    // 测试用例1
    string s1 = "abcabcbb";
    int result1 = sol.lengthOfLongestSubstring(s1);
    int expected1 = 3;
    cout << "测试1: \"abcabcbb\"" << endl;
    cout << "你的结果: " << result1 << endl;
    cout << "期望结果: " << expected1 << " (子串: \"abc\")" << endl;
    cout << (result1 == expected1 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例2
    string s2 = "bbbbb";
    int result2 = sol.lengthOfLongestSubstring(s2);
    int expected2 = 1;
    cout << "测试2: \"bbbbb\"" << endl;
    cout << "你的结果: " << result2 << endl;
    cout << "期望结果: " << expected2 << " (子串: \"b\")" << endl;
    cout << (result2 == expected2 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    string s3 = "pwwkew";
    int result3 = sol.lengthOfLongestSubstring(s3);
    int expected3 = 3;
    cout << "测试3: \"pwwkew\"" << endl;
    cout << "你的结果: " << result3 << endl;
    cout << "期望结果: " << expected3 << " (子串: \"wke\")" << endl;
    cout << (result3 == expected3 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例4: 边界情况
    string s4 = "";
    int result4 = sol.lengthOfLongestSubstring(s4);
    int expected4 = 0;
    cout << "测试4: \"\" (空字符串)" << endl;
    cout << "你的结果: " << result4 << endl;
    cout << "期望结果: " << expected4 << endl;
    cout << (result4 == expected4 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例5: 单字符
    string s5 = "a";
    int result5 = sol.lengthOfLongestSubstring(s5);
    int expected5 = 1;
    cout << "测试5: \"a\"" << endl;
    cout << "你的结果: " << result5 << endl;
    cout << "期望结果: " << expected5 << endl;
    cout << (result5 == expected5 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

// 滑动窗口算法演示
void demonstrateAlgorithm() {
    cout << "\n📚 滑动窗口算法演示" << endl;
    cout << "===================" << endl;
    
    string s = "abcabcbb";
    cout << "字符串: \"" << s << "\"" << endl;
    cout << "目标: 找到最长无重复子串" << endl << endl;
    
    unordered_set<char> window;
    int left = 0, maxLen = 0;
    
    cout << "滑动窗口过程:" << endl;
    for (int right = 0; right < s.length(); right++) {
        cout << "步骤 " << (right + 1) << ": 尝试加入 '" << s[right] << "'" << endl;
        
        // 收缩窗口直到无重复字符
        while (window.find(s[right]) != window.end()) {
            cout << "  发现重复，移除 '" << s[left] << "'，left=" << left+1 << endl;
            window.erase(s[left]);
            left++;
        }
        
        // 扩展窗口
        window.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
        
        cout << "  当前窗口: [" << left << "," << right << "] = \"";
        for (int i = left; i <= right; i++) {
            cout << s[i];
        }
        cout << "\" (长度=" << (right - left + 1) << ")" << endl;
        cout << "  当前最长: " << maxLen << endl << endl;
    }
    
    cout << "🎯 最终答案: " << maxLen << endl;
}

// 滑动窗口通用模板
void showTemplate() {
    cout << "\n📖 滑动窗口通用模板" << endl;
    cout << "===================" << endl;
    cout << R"(
// 滑动窗口基本框架
int slidingWindow(string s) {
    unordered_map<char, int> window;  // 窗口内字符统计
    int left = 0, right = 0;          // 左右指针
    int result = 0;                   // 结果
    
    while (right < s.length()) {
        char c = s[right];            // 即将进入窗口的字符
        right++;                      // 扩大窗口
        
        // 更新窗口内数据
        window[c]++;
        
        // 判断左侧窗口是否需要收缩
        while (窗口需要收缩的条件) {
            char d = s[left];         // 即将移出窗口的字符
            left++;                   // 收缩窗口
            
            // 更新窗口内数据
            window[d]--;
        }
        
        // 在这里更新答案 (根据题目要求)
        result = max(result, right - left);
    }
    
    return result;
}
)" << endl;
}

int main() {
    cout << "🚀 LeetCode 3. 无重复字符的最长子串" << endl;
    cout << "====================================" << endl;
    cout << "🎯 这是滑动窗口的经典入门题目！" << endl;
    cout << "💡 重点理解窗口的扩展和收缩机制" << endl << endl;
    
    runTests();
    demonstrateAlgorithm();
    showTemplate();
    
    return 0;
}