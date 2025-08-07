/*
通用题目模板生成器

使用方法:
为每个新题目创建统一格式的模板，包含LeetCode链接和标准结构。

标准格式:
1. 题目基本信息 + LeetCode链接
2. 图形说明提示(如果需要)
3. 题目描述和示例
4. 思考要点
5. Solution类模板
6. 测试框架
*/

#include <iostream>
#include <string>
using namespace std;

void generateTemplate(int problemNum, string title, string difficulty, string tags, bool needsVisualization = false) {
    cout << "#include <iostream>" << endl;
    cout << "#include <vector>" << endl;
    cout << "#include <algorithm>" << endl;
    cout << "#include <cassert>" << endl;
    cout << "using namespace std;" << endl << endl;
    
    cout << "/*" << endl;
    cout << "题目: " << problemNum << ". " << title << endl;
    cout << "难度: " << difficulty << endl;
    cout << "标签: " << tags << endl;
    cout << "LeetCode链接: https://leetcode.cn/problems/[problem-slug]/" << endl;
    
    if (needsVisualization) {
        cout << endl;
        cout << "📊 题目说明: " << endl;
        cout << "本题需要图形化理解，建议先查看LeetCode链接中的图示说明。" << endl;
    }
    
    cout << endl;
    cout << "题目描述:" << endl;
    cout << "// TODO: 添加题目描述" << endl;
    cout << "*/" << endl << endl;
    
    cout << "class Solution {" << endl;
    cout << "public:" << endl;
    cout << "    // TODO: 请在这里实现你的解法" << endl;
    cout << "    auto solve() {" << endl;
    cout << "        return 0;" << endl;
    cout << "    }" << endl;
    cout << "};" << endl;
}

// 示例使用
int main() {
    cout << "// 示例：生成题目11的模板" << endl;
    generateTemplate(11, "盛最多水的容器", "Medium", "[数组, 双指针, 贪心]", true);
    return 0;
}