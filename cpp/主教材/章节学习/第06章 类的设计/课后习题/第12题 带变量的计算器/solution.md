# 第6章 · 习题12：带变量的计算器 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 先判断这一行是不是赋值（第二个记号是 `=`），再决定「存起来」还是「打印」。
- 变量查表要在 `vars` 里做：找不到就抛异常，不要默认成 0。
- 赋值的右边也可能是表达式（`y = x + 1`），直接复用同一个 `evaluate`。

## 容易错的边界

- `x = ` 右边是空的，要判「缺少表达式」，不能当 0。
- 变量名不能是纯数字：`2 = 3` 非法。
- 赋值行不输出，别顺手打印一行“已赋值”。

## 参考实现

```cpp
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

// 变量表：名字 -> 值。赋值语句不输出，只更新表。
static double evaluate(const std::string& expr, const std::map<std::string, double>& vars) {
    std::istringstream in(expr);
    std::string token;
    if (!(in >> token)) throw std::invalid_argument("空表达式");

    auto readOperand = [&](const std::string& text) {
        std::size_t used = 0;
        try {
            const double v = std::stod(text, &used);
            if (used == text.size()) return v;
        } catch (const std::exception&) {
            // 不是数字，走变量名查找
        }
        const auto it = vars.find(text);
        if (it == vars.end()) throw std::invalid_argument("未定义的变量：" + text);
        return it->second;
    };

    double value = readOperand(token);
    std::string op;
    while (in >> op) {
        if (op != "+" && op != "-" && op != "*" && op != "/") {
            throw std::invalid_argument("无法识别的运算符：" + op);
        }
        std::string operand;
        if (!(in >> operand)) throw std::invalid_argument("运算符缺少操作数");
        const double right = readOperand(operand);
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
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }
        std::cin.ignore();
        std::map<std::string, double> vars;

        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行读不到");
            }
            std::istringstream head(line);
            std::string first, second;
            head >> first;
            if (!head) throw std::invalid_argument("空行不是合法输入");
            head >> second;
            if (second == "=") {
                for (char ch : first) {
                    if (!std::isalnum(static_cast<unsigned char>(ch)) && ch != '_') {
                        throw std::invalid_argument("非法的变量名：" + first);
                    }
                }
                std::string rest;
                std::getline(head, rest);
                if (rest.find_first_not_of(" \t") == std::string::npos) {
                    throw std::invalid_argument("赋值缺少表达式");
                }
                vars[first] = evaluate(rest, vars);
            } else {
                std::cout << std::fixed << std::setprecision(2) << evaluate(line, vars) << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
