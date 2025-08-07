# Problems 目录

## 📁 目录结构
这个目录包含所有LeetCode题目的C++实现和测试文件。

### 文件命名规则
- `problem_[题号]_[题目名].cpp` - 完整实现版本
- `problem_[题号]_template.cpp` - 空白模板版本  
- `test_environment.cpp` - 通用测试环境
- `template_generator.cpp` - 题目模板生成器

### 🔗 LeetCode链接规范
每个题目文件都包含：
- **LeetCode中文链接**: https://leetcode.cn/problems/[problem-slug]/
- **图形说明提示**: 对需要图示理解的题目特别标注
- **直接访问**: 点击链接查看原题图示和详细说明

### 编译和运行
```bash
# 编译单个题目
g++ -std=c++17 problem_11_template.cpp -o problem_11

# 运行测试
./problem_11

# 或者一步到位
g++ -std=c++17 problem_11_template.cpp -o problem_11 && ./problem_11
```

### 文件说明
- **template版本**: 用于你自己实现，包含题目描述和测试框架
- **完整版本**: 参考答案，包含多种解法和详细分析
- **test_environment**: 验证C++环境的通用测试文件

## 📋 已完成题目列表
- [ ] 11. 盛最多水的容器 (Medium) - 进行中

## 🎯 使用流程
1. 打开对应的template文件
2. 在Solution类中实现你的解法
3. 编译运行查看测试结果
4. 如果通过，更新进度追踪文件