// 【本题说明开始】
// 第8章 · 习题10：手机键盘记忆术
//
// 题目：读入 n 个数字串（2—9），列出所有可能的字母组合，按字典序输出。
// 实现什么：`collectMnemonics` 的递归 + `main` 的读入、排序与输出。
// 写在哪里：只补下方 BEGIN 1（递归函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每行一个字母组合（字典序）；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 数字 -> 字母表（不是数字就返回空串）。
inline const char* keypad(char digit) {
    switch (digit) {
        case '2': return "ABC";
        case '3': return "DEF";
        case '4': return "GHI";
        case '5': return "JKL";
        case '6': return "MNO";
        case '7': return "PQRS";
        case '8': return "TUV";
        case '9': return "WXYZ";
        default: return "";
    }
}

void collectMnemonics(const std::string& digits, std::size_t index,
                      std::string& current, std::vector<std::string>& out) {
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
