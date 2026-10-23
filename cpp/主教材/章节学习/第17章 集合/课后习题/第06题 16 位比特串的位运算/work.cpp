// 【本题说明开始】
// 第17章 · 习题6：16 位比特串的位运算
//
// 题目：把两个 16 位比特串读成整数，用 &、|、^、~ 算出结果，再按比特串打印回去。
// 实现什么：`parseBits()` 的校验与组装 + `main` 的五个位运算输出。
// 写在哪里：只补下方 BEGIN 1（集合的读取 / 位串解析）与 BEGIN 2（主程序的组合与输出）之间的代码。
// 文本格式：五行 16 位比特；格式非法返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

// 把 16 个 '0'/'1' 的串校验并组装成 unsigned short。
unsigned short parseBits(const std::string& text) {
    /* BEGIN 1 */
    // @@1@@
    /* END 1 */
}

// 把值打印成 16 个比特（高位补 0）。
std::string toBits(unsigned short value) {
    std::string text(16, '0');
    for (int i = 15; i >= 0; --i) {
        text[static_cast<std::size_t>(i)] = (value & 1u) ? '1' : '0';
        value = static_cast<unsigned short>(value >> 1);
    }
    return text;
}

int main() {
    try {
        /* BEGIN 2 */
        // 读两行比特串，先都解析完，再输出五行结果。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
