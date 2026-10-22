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
