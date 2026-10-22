# 第6章 · 习题9：有理数的 RPN 计算器 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 弹栈顺序是 `b = 栈顶`、`a = 次顶`，再算 `a op b`；写反了减法和除法会错。
- 每个数字先判断「有没有斜杠」再决定按分数还是整数解析。
- 结束时栈里剩 1 个数才算成功——剩 0 个或 2 个都说明表达式不完整。

## 容易错的边界

- `1/2 1/3 +` 是 5/6，不是 2/5：先弹出的 1/3 是右操作数。
- `3` 和 `3/1` 是同一个数，构造时会自动约分，不用特判。
- `1/2 +` 只有一个操作数，必须在弹栈前检查 `size() >= 2`。

## 参考实现

```cpp
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// 有理数：构造即规范（分母为正、最简）。
class Rational {
public:
    Rational() : num_(0), den_(1) {}
    Rational(long long num, long long den) : num_(num), den_(den) {
        if (den == 0) throw std::invalid_argument("分母不能为 0");
        if (den < 0) { num = -num; den = -den; }
        const long long g = std::gcd(num < 0 ? -num : num, den);
        num_ = num / g;
        den_ = den / g;
    }
    long long num() const { return num_; }
    long long den() const { return den_; }
    std::string toString() const {
        if (den_ == 1) return std::to_string(num_);
        return std::to_string(num_) + "/" + std::to_string(den_);
    }

private:
    long long num_;
    long long den_;
};

static Rational apply(const Rational& a, const Rational& b, const std::string& op) {
    if (op == "+") return Rational(a.num() * b.den() + b.num() * a.den(), a.den() * b.den());
    if (op == "-") return Rational(a.num() * b.den() - b.num() * a.den(), a.den() * b.den());
    if (op == "*") return Rational(a.num() * b.num(), a.den() * b.den());
    if (op == "/") {
        if (b.num() == 0) throw std::invalid_argument("除数不能为 0");
        return Rational(a.num() * b.den(), a.den() * b.num());
    }
    throw std::invalid_argument("未知运算符：" + op);
}

// 栈式求值：数字压栈，运算符弹出两个数（先弹出的在右边）。
static Rational evaluate(const std::string& line) {
    std::istringstream in(line);
    std::vector<Rational> stack;
    std::string token;
    bool any = false;
    while (in >> token) {
        any = true;
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) throw std::invalid_argument("运算符缺少操作数");
            const Rational b = stack.back();
            stack.pop_back();
            const Rational a = stack.back();
            stack.pop_back();
            stack.push_back(apply(a, b, token));
            continue;
        }
        const std::size_t slash = token.find('/');
        if (slash == std::string::npos) {
            for (char ch : token) {
                if (ch != '-' && !std::isdigit(static_cast<unsigned char>(ch))) {
                    throw std::invalid_argument("无法识别的记号：" + token);
                }
            }
            stack.emplace_back(std::stoll(token), 1);
        } else {
            const long long num = std::stoll(token.substr(0, slash));
            const long long den = std::stoll(token.substr(slash + 1));
            stack.emplace_back(num, den);
        }
    }
    if (!any) throw std::invalid_argument("空表达式");
    if (stack.size() != 1) throw std::invalid_argument("表达式不完整");
    return stack.back();
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
            std::cout << evaluate(line).toString() << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
