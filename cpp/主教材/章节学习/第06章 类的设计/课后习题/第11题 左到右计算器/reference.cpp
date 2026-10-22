#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// 从左到右求值（不考虑优先级）：`12 + 3 * 4` 得 60，不是 24。
static double evaluate(const std::string& line) {
    std::istringstream in(line);
    std::string token;
    if (!(in >> token)) throw std::invalid_argument("空表达式");

    double value = 0.0;
    std::size_t used = 0;
    value = std::stod(token, &used);
    if (used != token.size()) throw std::invalid_argument("无法识别的记号：" + token);

    std::string op;
    while (in >> op) {
        if (op != "+" && op != "-" && op != "*" && op != "/") {
            throw std::invalid_argument("无法识别的运算符：" + op);
        }
        std::string operand;
        if (!(in >> operand)) throw std::invalid_argument("运算符缺少操作数");
        std::size_t n = 0;
        const double right = std::stod(operand, &n);
        if (n != operand.size()) throw std::invalid_argument("无法识别的记号：" + operand);
        if (op == "+") value += right;
        else if (op == "-") value -= right;
        else if (op == "*") value *= right;
        else {
            if (right == 0.0) throw std::domain_error("除数不能为 0");
            value /= right;
        }
    }
    return value;
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("表达式条数必须在 1 到 100 之间");
        }
        std::cin.ignore();

        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 条表达式读不到");
            }
            std::cout << std::fixed << std::setprecision(2) << evaluate(line) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
