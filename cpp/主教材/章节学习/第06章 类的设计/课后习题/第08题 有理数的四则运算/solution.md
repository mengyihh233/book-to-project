# 第6章 · 习题8：有理数的四则运算 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 约分放在构造函数里做一次，所有运算就不用各写一遍。
- 分母的负号要收到分子上：`1/-2` 必须变成 `-1/2`。
- 除法要先看除数是不是 0，再交叉相乘，否则会构造出分母为 0 的对象。

## 容易错的边界

- `0` 要写成 `0`（0/1），不是 `0/0`。
- 分子为 0 时 gcd(0, d) = d，能正常约掉，不用特判。
- `a`、`b` 到 10⁹ 时交叉相乘到 10¹⁸，`int` 会溢出，必须用 `long long`。

## 参考实现

```cpp
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

class Rational {
public:
    Rational() : num_(0), den_(1) {}

    Rational(long long num, long long den) : num_(num), den_(den) {
        if (den == 0) throw std::invalid_argument("分母不能为 0");
        if (den < 0) {          // 符号一律收到分子
            num = -num;
            den = -den;
        }
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

static Rational combine(const Rational& a, const Rational& b, char op) {
    long long num = 0, den = 1;
    if (op == '+') {
        num = a.num() * b.den() + b.num() * a.den();
        den = a.den() * b.den();
    } else if (op == '-') {
        num = a.num() * b.den() - b.num() * a.den();
        den = a.den() * b.den();
    } else if (op == '*') {
        num = a.num() * b.num();
        den = a.den() * b.den();
    } else if (op == '/') {
        if (b.num() == 0) throw std::invalid_argument("除数不能为 0");
        num = a.num() * b.den();
        den = a.den() * b.num();
    } else {
        throw std::invalid_argument(std::string("未知运算符：") + op);
    }
    return Rational(num, den);
}

static Rational add(const Rational& a, const Rational& b) { return combine(a, b, '+'); }
static Rational sub(const Rational& a, const Rational& b) { return combine(a, b, '-'); }
static Rational mul(const Rational& a, const Rational& b) { return combine(a, b, '*'); }
static Rational divide(const Rational& a, const Rational& b) { return combine(a, b, '/'); }

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("表达式条数必须在 1 到 100 之间");
        }
        for (int i = 0; i < n; ++i) {
            long long a = 0, b = 0, c = 0, d = 0;
            char op = 0;
            if (!(std::cin >> a >> b >> op >> c >> d)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 条表达式不完整");
            }
            const Rational left(a, b), right(c, d);
            Rational result;
            if (op == '+') result = add(left, right);
            else if (op == '-') result = sub(left, right);
            else if (op == '*') result = mul(left, right);
            else if (op == '/') result = divide(left, right);
            else throw std::invalid_argument(std::string("未知运算符：") + op);
            std::cout << result.toString() << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
