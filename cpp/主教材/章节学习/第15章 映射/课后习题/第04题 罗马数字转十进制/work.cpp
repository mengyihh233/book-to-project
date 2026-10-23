// 【本题说明开始】
// 第15章 · 习题4：罗马数字转十进制
//
// 题目：把罗马数字串翻译成十进制数：逐字符查表得到数值，比右边小的减、否则加。
// 实现什么：`romanToDecimal()` 的查找表与累加规则 + `main` 的读入与输出。
// 写在哪里：只补下方 BEGIN 1（数据结构的实现）与 BEGIN 2（读入、校验与输出）之间的代码。
// 文本格式：每行一个十进制数；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 查找表：字符 -> 数值。只认 I V X L C D M（进来之前已统一成大写）。
int romanToDecimal(const std::string& str) {
    /* BEGIN 1 */
    // @@1@@
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("行数必须在 1 到 1000 之间");
        }
        std::string rest;
        std::getline(std::cin, rest);
        /* BEGIN 2 */
        // 先读完 n 行、逐行转成数值并校验（1..3999），全部通过之后再逐行输出。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
