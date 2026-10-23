// 【本题说明开始】
// 第11章 · 习题3：任意进制的整数转换
//
// 题目：实现带基数的整数转字符串、字符串转整数：支持 2—36 进制，10 以上用大写字母。
// 实现什么：`intToString` / `stringToInt` 两个函数 + `main` 的分派。
// 写在哪里：只补下方 BEGIN 1（要实现的函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每条命令一行结果；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

std::string intToString(long long value, int base) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

long long stringToInt(const std::string& text, int base) {
    /* BEGIN 2 */
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("命令条数必须在 1 到 100 之间");
        }
        for (int i = 0; i < n; ++i) {
            std::string command;
            if (!(std::cin >> command)) throw std::invalid_argument("命令不完整");
            if (command == "to") {
                long long value = 0;
                int base = 0;
                if (!(std::cin >> value >> base)) throw std::invalid_argument("to 缺少参数");
                if (base < 2 || base > 36) throw std::invalid_argument("基数必须在 2 到 36 之间");
                std::cout << intToString(value, base) << '\n';
            } else if (command == "from") {
                std::string text;
                int base = 0;
                if (!(std::cin >> text >> base)) throw std::invalid_argument("from 缺少参数");
                if (base < 2 || base > 36) throw std::invalid_argument("基数必须在 2 到 36 之间");
                std::cout << stringToInt(text, base) << '\n';
            } else {
                throw std::invalid_argument("未知命令：" + command);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
