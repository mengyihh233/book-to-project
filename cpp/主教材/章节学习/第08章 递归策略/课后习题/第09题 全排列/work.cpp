// 【本题说明开始】
// 第8章 · 习题9：全排列
//
// 题目：读入 n 个只含大写字母的字符串，递归列出每个字符串的**全部唯一排列**，按字典序输出。
// 实现什么：`collectPermutations`（交换法递归）+ `main` 的读入与输出。
// 写在哪里：只补下方 BEGIN 1（递归函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每个排列一行（字典序）；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

void collectPermutations(std::string s, int start, std::set<std::string>& out) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 5) {
            throw std::invalid_argument("行数必须在 1 到 5 之间");
        }
        std::cin.ignore();
        /* BEGIN 2 */
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
