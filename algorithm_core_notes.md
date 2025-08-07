# 算法核心逻辑记录

## 239. 滑动窗口最大值 (Hard)

### 核心思想
使用**单调双端队列**维护滑动窗口中的最大值，队列中存储数组下标，保持对应值的递减顺序。

### 关键逻辑
1. **队列维护策略**:
   - 存储下标而非值，便于判断元素是否过期
   - 维护递减序列，队首永远是当前窗口最大值
   
2. **三个核心操作**:
   ```cpp
   // 1. 移除过期元素（超出窗口范围）
   while (!dq.empty() && dq.front() <= i - k) {
       dq.pop_front();
   }
   
   // 2. 维护单调性（移除比当前元素小的所有元素）
   while (!dq.empty() && nums[dq.back()] <= nums[i]) {
       dq.pop_back();
   }
   
   // 3. 添加当前元素
   dq.push_back(i);
   ```

3. **为什么可以移除较小元素？**
   - 如果新元素比队尾元素大，那么在新元素还在窗口内时，队尾元素永远不可能成为最大值
   - 这是贪心思想的体现

### 时间复杂度分析
- **O(n)**: 每个元素最多入队和出队各一次
- 比暴力O(nk)和堆O(n log n)都要优

### 易错点
1. 队列存储下标而非值
2. 过期判断条件是 `dq.front() <= i - k`
3. 单调性维护用 `<=` 还是 `<` (通常用`<=`避免重复值)
4. 窗口满的判断条件 `i >= k - 1`

### 模板代码
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq;  // 存储下标，保持递减顺序
    
    for (int i = 0; i < nums.size(); i++) {
        // 移除过期元素
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // 维护单调性
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // 窗口满时记录结果
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}
```

### 扩展应用
- 滑动窗口最小值 (改为递增队列)
- 滑动窗口中的中位数
- 绝对差不超过限制的最长连续子数组

---

## 155. 最小栈 (Medium)

### 核心思想
使用**双栈法**设计支持O(1)获取最小值的栈，主栈存储所有元素，辅助栈存储对应的最小值。

### 关键逻辑
1. **双栈协同工作**:
   - 主栈：存储所有push的元素
   - 辅助栈：存储到当前位置的最小值
   
2. **四个核心操作**:
   ```cpp
   // push: 主栈总是push，辅助栈按条件push
   void push(int val) {
       mainStack.push(val);
       if (minStack.empty() || val <= minStack.top()) {
           minStack.push(val);  // 注意：<= 不是 <
       }
   }
   
   // pop: 同步维护两个栈
   void pop() {
       if (mainStack.top() == minStack.top()) {
           minStack.pop();
       }
       mainStack.pop();
   }
   
   // top: 直接返回主栈顶
   int top() { return mainStack.top(); }
   
   // getMin: 直接返回辅助栈顶
   int getMin() { return minStack.top(); }
   ```

3. **为什么用<= 而不是< ？**
   - 处理重复最小值的情况
   - 例如：push(1) → push(1) → pop()，两个1都需要在辅助栈中

### 时间复杂度分析
- **所有操作都是O(1)**: push, pop, top, getMin
- **空间复杂度**: O(n) - 最坏情况两个栈都是n

### 易错点
1. 辅助栈push条件：必须是 `<=` 处理重复最小值
2. pop时的同步：只有当主栈顶等于最小值时才pop辅助栈
3. 空栈检查：pop和top前要确保栈非空

### 模板代码
```cpp
class MinStack {
    stack<int> mainStack, minStack;
public:
    void push(int val) {
        mainStack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    int top() { return mainStack.top(); }
    int getMin() { return minStack.top(); }
};
```

### 扩展思考
- 单栈存储差值法：节省空间但实现复杂
- 最大栈问题：类似思路
- 支持多种操作的栈设计

---

## 84. 柱状图中最大的矩形 (Hard)

### 核心思想
使用**单调递增栈**找到每个柱子的左右边界，计算以每个柱子为高度的最大矩形面积。

### 关键逻辑
1. **单调栈维护策略**:
   - 栈中存储下标，保持对应高度递增
   - 当遇到更小元素时，弹栈并计算面积
   
2. **边界处理技巧**:
   ```cpp
   // 在数组两端添加0，简化边界处理
   heights.insert(heights.begin(), 0);
   heights.push_back(0);
   ```

3. **面积计算核心**:
   ```cpp
   while (!st.empty() && heights[st.top()] > heights[i]) {
       int h = heights[st.top()];  // 矩形高度
       st.pop();                   // 弹出，更新左边界
       int w = i - st.top() - 1;   // 矩形宽度
       int area = h * w;           // 计算面积
   }
   ```

4. **为什么先取高度再pop？**
   - 弹栈操作会改变栈顶，影响左边界的确定
   - 弹出后的栈顶正好是当前柱子左边第一个比它小的位置

### 时间复杂度分析
- **O(n)**: 每个元素最多入栈和出栈各一次
- **空间复杂度**: O(n) - 栈的空间

### 易错点
1. 宽度计算：`w = 右边界 - 左边界 - 1`
2. 操作顺序：先取高度，再pop，再计算宽度
3. 边界处理：两端加0避免特殊情况判断
4. 理解弹栈时机：当前元素小于栈顶时

### 模板代码
```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    
    // 边界处理
    heights.insert(heights.begin(), 0);
    heights.push_back(0);
    
    for (int i = 0; i < heights.size(); i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int w = i - st.top() - 1;
            maxArea = max(maxArea, h * w);
        }
        st.push(i);
    }
    return maxArea;
}
```

### 扩展应用
- 42. 接雨水 (单调栈变种)
- 85. 最大矩形 (二维扩展)
- 柱状图相关的最值问题

### 关键洞察
单调栈的本质是**延迟计算**：
- 元素在栈中时，右边界未确定
- 被弹出时，右边界确定，立即计算面积
- 这种策略保证了O(n)的时间复杂度

---

## 42. 接雨水 (Hard)

### 核心思想
使用**单调递减栈**按层计算雨水面积，栈中存储可能形成凹槽的柱子下标。

### 关键逻辑
1. **单调栈维护策略**:
   - 栈中存储下标，保持对应高度递减
   - 当遇到更高柱子时，说明可以接雨水了
   
2. **雨水计算核心**:
   ```cpp
   while (!st.empty() && heights[st.top()] < heights[i]) {
       int bottom = st.top();  // 凹槽底部
       st.pop();
       if (st.empty()) break;  // 没有左边界
       
       int h = min(heights[st.top()], heights[i]) - heights[bottom];
       int w = i - st.top() - 1;
       water += h * w;
   }
   ```

3. **与84题的区别**:
   - 84题：维护递增栈，计算矩形面积
   - 42题：维护递减栈，计算雨水体积

### 直观理解
雨水的形成需要三个要素：
- **左边界**：栈中剩余元素
- **底部**：被弹出的元素  
- **右边界**：当前遍历元素

### 时间复杂度分析
- **O(n)**: 每个元素最多入栈和出栈各一次
- **空间复杂度**: O(n) - 栈的空间

### 模板代码
```cpp
int trap(vector<int>& height) {
    stack<int> st;
    int water = 0;
    
    for (int i = 0; i < height.size(); i++) {
        while (!st.empty() && height[st.top()] < height[i]) {
            int bottom = st.top();
            st.pop();
            if (st.empty()) break;
            
            int h = min(height[st.top()], height[i]) - height[bottom];
            int w = i - st.top() - 1;
            water += h * w;
        }
        st.push(i);
    }
    return water;
}
```

### 扩展思考
- 双指针解法：从两端向中间移动
- 动态规划：预计算左右最大高度
- 单调栈：按层累加雨水面积

---

## 70. 爬楼梯 (Easy)

### 核心思想
动态规划入门经典题，体现了DP的基本思维：**大问题分解为小问题，避免重复计算**。

### 关键逻辑
1. **状态定义**:
   - `dp[i]` = 爬到第i阶的方法数
   
2. **状态转移方程**:
   ```
   dp[i] = dp[i-1] + dp[i-2]
   ```
   逻辑：要到第i阶，只能从第(i-1)阶爬1步，或从第(i-2)阶爬2步

3. **边界条件**:
   ```cpp
   dp[0] = 1  // 0阶有1种方法（不爬）
   dp[1] = 1  // 1阶有1种方法
   dp[2] = 2  // 2阶有2种方法
   ```

4. **本质**: 斐波那契数列的变种

### 四种实现方式

#### 1. 普通递归 (会超时)
```cpp
int climbStairs(int n) {
    if (n <= 1) return 1;
    if (n == 2) return 2;
    return climbStairs(n-1) + climbStairs(n-2);
}
```
**问题**: 重复计算，时间复杂度O(2^n)

#### 2. 记忆化搜索 (自顶向下)
```cpp
int helper(int n, vector<int>& memo) {
    if (n <= 1) return 1;
    if (n == 2) return 2;
    if (memo[n] != -1) return memo[n];
    
    memo[n] = helper(n-1, memo) + helper(n-2, memo);
    return memo[n];
}
```
**优势**: 缓存结果，避免重复计算

#### 3. 动态规划 (自底向上) ⭐
```cpp
int climbStairs(int n) {
    if (n <= 1) return 1;
    vector<int> dp(n + 1);
    dp[0] = 1; dp[1] = 1; dp[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
```

#### 4. 空间优化 (滚动变量)
```cpp
int climbStairs(int n) {
    if (n <= 1) return 1;
    if (n == 2) return 2;
    
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

### 复杂度分析
- **递归**: 时间O(2^n)，空间O(n)
- **记忆化**: 时间O(n)，空间O(n)
- **DP**: 时间O(n)，空间O(n)
- **空间优化**: 时间O(n)，空间O(1)

### DP四要素总结
1. **状态定义**: dp[i]表示什么
2. **转移方程**: 当前状态如何由之前状态推导
3. **边界条件**: 最小子问题的答案
4. **计算顺序**: 确保依赖关系正确

### 关键理解
- **记忆化 vs 普通递归**: 记忆化用专门数组永久缓存，普通递归每次重新计算
- **自顶向下 vs 自底向上**: 记忆化是递归+缓存，DP是循环填表
- **状态转移**: DP的精髓在于找到状态间的数学关系

---

## 198. 打家劫舍 (Medium)

### 核心思想
决策类动态规划经典题，体现了**选择决策**的DP思维：每个状态面临多种选择，选择最优方案。

### 关键逻辑
1. **状态定义**:
   - `dp[i]` = 偷前i+1间房能获得的最大金额
   
2. **决策分析**:
   对于第i间房，小偷面临两种选择：
   - **偷第i间房**: 获得 `nums[i] + dp[i-2]` (不能偷相邻房屋)
   - **不偷第i间房**: 获得 `dp[i-1]` (保持前一状态)

3. **状态转移方程**:
   ```
   dp[i] = max(nums[i] + dp[i-2], dp[i-1])
   ```

4. **边界条件**:
   ```cpp
   dp[0] = nums[0]                    // 只有1间房
   dp[1] = max(nums[0], nums[1])      // 2间房选金额大的
   ```

### 四种实现方式

#### 1. 递归解法 (会超时)
```cpp
int helper(vector<int>& nums, int i) {
    if (i < 0) return 0;
    return max(helper(nums, i-2) + nums[i], helper(nums, i-1));
}
```

#### 2. 记忆化搜索 (自顶向下)
```cpp
int helperMemo(vector<int>& nums, int i, vector<int>& memo) {
    if (i < 0) return 0;
    if (i == 0) return nums[0];
    if (memo[i] != -1) return memo[i];
    
    memo[i] = max(helperMemo(nums,i-2,memo) + nums[i], 
                  helperMemo(nums,i-1,memo));
    return memo[i];
}
```

#### 3. 动态规划 (自底向上) ⭐
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
    }
    return dp[n-1];
}
```

#### 4. 空间优化 (滚动变量)
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        int curr = max(nums[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

### 与70题的关键区别
- **70题爬楼梯**: 递推关系 `f(n) = f(n-1) + f(n-2)` (加法)
- **198题打家劫舍**: 决策关系 `f(n) = max(选择A, 选择B)` (选择)

### 决策类DP特征
1. **多种选择**: 每个状态面临2个或更多选择
2. **约束条件**: 选择之间存在限制关系
3. **最优决策**: 使用max/min函数选择最优方案
4. **状态依赖**: 当前选择影响后续可选方案

### 复杂度分析
- **递归**: 时间O(2^n)，空间O(n)
- **记忆化**: 时间O(n)，空间O(n)
- **DP**: 时间O(n)，空间O(n)
- **空间优化**: 时间O(n)，空间O(1)

### 关键理解
- **约束建模**: 相邻房屋不能同时偷 → 状态转移中体现为i-2而不是i-1
- **决策思维**: 每步都要问"我有哪些选择？哪个更优？"
- **记忆化精髓**: 计算 → 缓存 → 返回，三步缺一不可

### 扩展应用
- 213. 打家劫舍II (环形数组)
- 337. 打家劫舍III (二叉树)
- 01背包问题 (物品选择决策)

---

*记录日期: 2025-08-04*
*掌握程度: 🔥 熟练掌握*