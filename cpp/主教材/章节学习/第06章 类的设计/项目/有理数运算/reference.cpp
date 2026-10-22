// 参考实现：有理数运算
// 输入一行 `a/b 运算符 c/d`，输出最简结果；分母为 1 时只输出整数。
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

namespace {

long long gcdOf(long long a, long long b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

class Fraction {
public:
    Fraction(long long numerator, long long denominator)
        : num_(numerator), den_(denominator) {
        reduce();
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(num_ * other.den_ + other.num_ * den_, den_ * other.den_);
    }
    Fraction operator-(const Fraction& other) const {
        return Fraction(num_ * other.den_ - other.num_ * den_, den_ * other.den_);
    }
    Fraction operator*(const Fraction& other) const {
        return Fraction(num_ * other.num_, den_ * other.den_);
    }
    Fraction operator/(const Fraction& other) const {
        return Fraction(num_ * other.den_, den_ * other.num_);
    }

    std::string str() const {
        if (den_ == 1) return std::to_string(num_);
        return std::to_string(num_) + "/" + std::to_string(den_);
    }

private:
    void reduce() {
        if (den_ < 0) {          // 负号统一放分子，方便比较和输出
            num_ = -num_;
            den_ = -den_;
        }
        const long long g = gcdOf(num_, den_);
        if (g > 1) {
            num_ /= g;
            den_ /= g;
        }
    }
    long long num_;
    long long den_;
};

}  // namespace

int main() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cerr << "缺少输入\n";
        return 2;
    }
    std::istringstream iss(line);
    long long a = 0, b = 0, c = 0, d = 0;
    char s1 = 0, s2 = 0, op = 0;
    if (!(iss >> a >> s1 >> b >> op >> c >> s2 >> d) || s1 != '/' || s2 != '/') {
        std::cerr << "格式应为 a/b 运算符 c/d\n";
        return 2;
    }
    if (b == 0 || d == 0) {
        std::cerr << "分母不能为 0\n";
        return 2;
    }
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        std::cerr << "未知运算符\n";
        return 2;
    }
    if (op == '/' && c == 0) {
        std::cerr << "除数不能为 0\n";
        return 2;
    }

    const Fraction left(a, b), right(c, d);
    Fraction result(0, 1);
    switch (op) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        default: result = left / right; break;
    }
    std::cout << result.str() << "\n";
    return 0;
}
