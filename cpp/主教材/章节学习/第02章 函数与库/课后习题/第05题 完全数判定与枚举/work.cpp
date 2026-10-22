// 【本题说明开始】
// 第2章习题5：完全数判定与枚举
//
// 题目：完全数是一个正整数，其所有小于自身的正因子之和等于自身，例如6=1+2+3。实现isPerfect(n)，用循环枚举1到9999中的完全数。main不读输入，按从小到大输出一行，以空格
//   分隔；不要将整组答案写死。
// 实现什么：bool isPerfect(int n)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

// 函数声明已给出；本题只补下方BEGIN / END之间的函数体。
bool isPerfect(int n);
double readFinite();
long long readInteger();
void ensureEnd();

// 给定主程序：负责读入、调用和输出，不加“请输入”等提示语。
int main() {
    try {
        std::cout << std::setprecision(12);
        
        ensureEnd();
        bool first = true;
        for (int n = 1; n <= 9999; ++n) {
            if (isPerfect(n)) {
                if (!first) std::cout << " ";
                std::cout << n;
                first = false;
            }
        }
        std::cout << "\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 2;
    }
}

// 实现位置：只填写这个函数体，不重复定义main或函数签名。
bool isPerfect(int n) {
    /* BEGIN 1：实现isPerfect */
    // 累计小于n的正因子，判断因子和是否等于n。
    // 正确处理n≤1，返回true或false；枚举与输出已由main完成。
    // 完成后删除下面的占位throw，并按函数返回类型返回结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// #region 给定的输入检查辅助：本题不用修改
double readFinite() {
    double value;
    if (!(std::cin >> value) || !std::isfinite(value))
        throw std::invalid_argument("输入应为有限实数");
    return value;
}

long long readInteger() {
    long long value;
    if (!(std::cin >> value))
        throw std::invalid_argument("输入应为整数");
    return value;
}

void ensureEnd() {
    std::cin >> std::ws;
    if (!std::cin.eof())
        throw std::invalid_argument("输入含多余数据");
}
// #endregion
