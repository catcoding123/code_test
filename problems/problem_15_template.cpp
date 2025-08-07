#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
using namespace std;

/*
题目: 15. 三数之和
难度: Medium
标签: [数组, 双指针, 排序]
LeetCode链接: https://leetcode.cn/problems/3sum/

题目描述:
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
同时还满足 nums[i] + nums[j] + nums[k] == 0 。

请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1:
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。

示例 2:
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。

示例 3:
输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。

约束条件:
- 3 <= nums.length <= 3000
- -10^5 <= nums[i] <= 10^5

思考要点:
1. 这题与"两数之和"有什么关系？
2. 如何避免重复的三元组？
3. 暴力解法是O(n³)，能否优化到O(n²)？
4. 排序对解题有什么帮助？
5. 双指针在这里如何应用？

核心难点:
- 去重：如何确保结果中没有重复的三元组？
- 优化：如何从O(n³)优化到O(n²)？
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // TODO: 请在这里实现你的解法
        // 思考：
        // 1. 是否需要先排序？为什么？
        // 2. 固定一个数，剩下两个数如何快速找到？
        // 3. 如何跳过重复元素？
        vector<vector<int>> result;
        // 你的代码实现
        std::sort(nums.begin(),nums.end());
        for(int i = 0; i < nums.size(); i++) {
            if(i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int left = i + 1; left = i + 1 // 是为了确保三元组下标互不相同，并且只在 i 后面找剩下两个数，避免重复和错误组合
            int right = nums.size() - 1;
            while(left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if(sum == 0) {
                    result.push_back({nums[i],nums[left],nums[right]});
                    while(left < right && nums[left] == nums[left+1]) {
                        left++;
                    }
                    while(left < right && nums[right] == nums[right-1]) { // 注意这里是right-1，因为right已经指向了最后一个元素
                        right--;
                    }
                    left++;
                    right--;
                } else if(sum <0) {
                    left++;
                } else {
                    right--;
                }
            }
        }  
        return result;
    }
    
};

// 测试框架
void runTests() {
    Solution sol;
    
    cout << "🧪 测试 15. 三数之和" << endl;
    cout << "==================" << endl;
    
    // 测试用例1
    vector<int> nums1 = {-1,0,1,2,-1,-4};
    vector<vector<int>> result1 = sol.threeSum(nums1);
    cout << "测试1: [-1,0,1,2,-1,-4]" << endl;
    cout << "你的结果: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "," << result1[i][2] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望结果: [[-1,-1,2],[-1,0,1]]" << endl;
    
    // 简单验证 (顺序可能不同，这里只检查数量)
    cout << "结果数量: " << result1.size() << " (期望: 2)" << endl;
    cout << (result1.size() == 2 ? "✅ 数量正确" : "❌ 数量不正确") << endl << endl;
    
    // 测试用例2
    vector<int> nums2 = {0,1,1};
    vector<vector<int>> result2 = sol.threeSum(nums2);
    cout << "测试2: [0,1,1]" << endl;
    cout << "你的结果: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "," << result2[i][2] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望结果: []" << endl;
    cout << (result2.size() == 0 ? "✅ 通过" : "❌ 失败") << endl << endl;
    
    // 测试用例3
    vector<int> nums3 = {0,0,0};
    vector<vector<int>> result3 = sol.threeSum(nums3);
    cout << "测试3: [0,0,0]" << endl;
    cout << "你的结果: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << "[" << result3[i][0] << "," << result3[i][1] << "," << result3[i][2] << "]";
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "期望结果: [[0,0,0]]" << endl;
    cout << (result3.size() == 1 ? "✅ 通过" : "❌ 失败") << endl << endl;
}

int main() {
    cout << "🚀 LeetCode 15. 三数之和" << endl;
    cout << "========================" << endl;
    cout << "请实现 Solution::threeSum 函数" << endl;
    cout << "这题比较复杂，重点考虑去重和优化" << endl << endl;
    
    runTests();
    
    return 0;
}