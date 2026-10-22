// 【本题说明开始】
// 第6章 · 习题12：带变量的计算器
//
// 题目：读入 n 行，支持 `名字 = 表达式` 赋值和表达式求值（都按从左到右），表达式可引用已定义的变量。
// 实现什么：`evaluate()`（数字/变量 + 左结合）+ `main` 的赋值与输出分支。
// 写在哪里：只补下方 BEGIN 1（evaluate 求值）与 BEGIN 2（解析行、赋值与输出）之间的代码。
// 文本格式：表达式行输出两位小数，赋值行不输出；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

// 变量表：名字 -> 值。赋值语句不输出，只更新表。
static double evaluate(const std::string& expr, const std::map<std::string, double>& vars) {
    /* BEGIN 1 */
    // 1) 按空白切记号，第一个记号必须是数或已定义的变量名；
    // 2) 之后每次读「运算符 + 操作数」，左结合立刻算掉；
    // 3) 未定义变量、非法记号、缺操作数抛 std::invalid_argument；
    //    除数为 0 抛 std::domain_error。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }
        std::cin.ignore();
        std::map<std::string, double> vars;

        /* BEGIN 2 */
        // 每行两种形式：
        //   `名字 = 表达式`  —— 求值后写进 vars，不输出；
        //   `表达式`          —— 求值后输出两位小数。
        // 名字只能由字母/数字/下划线组成，且不能是纯数字。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
