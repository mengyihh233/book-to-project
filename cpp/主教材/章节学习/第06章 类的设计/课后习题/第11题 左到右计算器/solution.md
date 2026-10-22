# 第6章 · 习题11：左到右计算器 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 左结合的关键是「读一个运算符就立刻算掉」，不要先收集再按优先级算。
- 用 `std::stod` 的 `pos` 参数检查整个记号是否都是数字，`12x` 要判非法。
- 输出用 `std::fixed << std::setprecision(2)`，否则 60 会打成 `60`。

## 容易错的边界

- `12 + 3 * 4` 的答案是 60，写成 24 就是按优先级算了。
- `5 / 0` 要抛异常（`std::domain_error`），不能输出 inf。
- 空行是非法表达式，`in >> token` 失败就要报错。

## 参考实现

```cpp
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
```
