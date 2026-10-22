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
