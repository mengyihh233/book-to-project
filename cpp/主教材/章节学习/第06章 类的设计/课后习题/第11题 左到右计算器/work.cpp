// 【本题说明开始】
// 第6章 · 习题11：左到右计算器
//
// 题目：读入 n 行四则表达式，按**从左到右**（不考虑优先级）求值，输出两位小数。
// 实现什么：`evaluate()`（左结合求值 + 错误检查）+ `main` 的读取与格式化输出。
// 写在哪里：只补下方 BEGIN 1（evaluate 左到右求值）与 BEGIN 2（读取与输出）之间的代码。
// 文本格式：每行固定两位小数；非法表达式返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// 从左到右求值（不考虑优先级）：`12 + 3 * 4` 得 60，不是 24。
static double evaluate(const std::string& line) {
    /* BEGIN 1 */
    // 1) 用 istringstream 切记号，第一个记号必须是数；
    // 2) 之后每次读「运算符 + 数」，立刻用左边累计值算掉（左结合）；
    // 3) 除数为 0 抛 std::domain_error；记号不是运算符/数字、缺少操作数都抛
    //    std::invalid_argument；结尾多出东西也算非法。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("表达式条数必须在 1 到 100 之间");
        }
        std::cin.ignore();

        /* BEGIN 2 */
        // 读 n 行，每行求值后输出固定两位小数（例如 60.00）。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
