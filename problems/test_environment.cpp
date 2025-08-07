#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <climits>
#include <cassert>
#include <chrono>
using namespace std;

// 测试题目: 1. 两数之和
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (mp.find(complement) != mp.end()) {
                return {mp[complement], i};
            }
            mp[nums[i]] = i;
        }
        return {};
    }
};

// 测试框架
void runBasicTests() {
    Solution sol;
    
    cout << "🧪 开始基本功能测试..." << endl;
    
    // 测试用例1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = sol.twoSum(nums1, target1);
    vector<int> expected1 = {0, 1};
    assert(result1 == expected1);
    cout << "✅ 测试1通过: [2,7,11,15], target=9 -> [0,1]" << endl;
    
    // 测试用例2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = sol.twoSum(nums2, target2);
    vector<int> expected2 = {1, 2};
    assert(result2 == expected2);
    cout << "✅ 测试2通过: [3,2,4], target=6 -> [1,2]" << endl;
    
    // 测试用例3
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> result3 = sol.twoSum(nums3, target3);
    vector<int> expected3 = {0, 1};
    assert(result3 == expected3);
    cout << "✅ 测试3通过: [3,3], target=6 -> [0,1]" << endl;
    
    cout << "🎉 所有基本测试通过!" << endl;
}

// 性能测试
void runPerformanceTest() {
    Solution sol;
    
    cout << "\n⚡ 开始性能测试..." << endl;
    
    // 生成大数据量测试
    vector<int> largeNums;
    int size = 10000;
    for (int i = 0; i < size; i++) {
        largeNums.push_back(i);
    }
    int target = size - 3; // 确保有解
    
    auto start = chrono::high_resolution_clock::now();
    vector<int> result = sol.twoSum(largeNums, target);
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    assert(result.size() == 2);
    assert(largeNums[result[0]] + largeNums[result[1]] == target);
    
    cout << "✅ 大数据测试通过 (数组大小: " << size << ")" << endl;
    cout << "⏱️  执行时间: " << duration.count() << " 微秒" << endl;
    cout << "📊 时间复杂度: O(n)" << endl;
    cout << "💾 空间复杂度: O(n)" << endl;
}

// STL功能测试
void testSTLFeatures() {
    cout << "\n🔧 STL功能测试..." << endl;
    
    // vector测试
    vector<int> vec = {3, 1, 4, 1, 5};
    sort(vec.begin(), vec.end());
    cout << "✅ vector排序: ";
    for (int x : vec) cout << x << " ";
    cout << endl;
    
    // unordered_map测试
    unordered_map<string, int> mp;
    mp["hello"] = 1;
    mp["world"] = 2;
    cout << "✅ unordered_map: hello=" << mp["hello"] << ", world=" << mp["world"] << endl;
    
    // priority_queue测试
    priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(4);
    cout << "✅ priority_queue最大值: " << pq.top() << endl;
    
    // stack和queue测试
    stack<int> stk;
    queue<int> q;
    stk.push(42);
    q.push(42);
    cout << "✅ stack和queue功能正常" << endl;
}

// 辅助函数测试
void testHelperFunctions() {
    cout << "\n🛠️  辅助函数测试..." << endl;
    
    vector<int> arr = {5, 2, 8, 1, 9};
    
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    
    cout << "✅ 数组 [5,2,8,1,9]" << endl;
    cout << "   最大值: " << maxVal << endl;
    cout << "   最小值: " << minVal << endl;
    
    // 二分查找测试
    sort(arr.begin(), arr.end());
    bool found = binary_search(arr.begin(), arr.end(), 5);
    cout << "✅ 二分查找5: " << (found ? "找到" : "未找到") << endl;
}

int main() {
    cout << "🚀 C++ LeetCode 刷题环境测试" << endl;
    cout << "================================" << endl;
    
    try {
        runBasicTests();
        runPerformanceTest();
        testSTLFeatures();
        testHelperFunctions();
        
        cout << "\n🎯 环境测试完成!" << endl;
        cout << "✨ C++环境配置正确，可以开始刷题了!" << endl;
        cout << "\n📝 使用方法:" << endl;
        cout << "1. 修改Solution类中的函数实现" << endl;
        cout << "2. 添加测试用例到runBasicTests()" << endl;
        cout << "3. 运行: g++ -std=c++17 test_environment.cpp -o test && ./test" << endl;
        
    } catch (const exception& e) {
        cout << "❌ 测试失败: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}