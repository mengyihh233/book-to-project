// 【本题说明开始】
// 第6章 · 习题8：有理数的四则运算
//
// 题目：读入 n 个分数运算式，按最简分数输出结果（分母恒正、分母为 1 时只写整数）。
// 实现什么：`Rational` 的构造函数（规范化 + 约分）+ `combine()` 的四则运算。
// 写在哪里：只补下方 BEGIN 1（Rational 构造函数）与 BEGIN 2（combine 四则运算）之间的代码。
// 文本格式：每条一行最简结果（`-1/2`、`2`）；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

// 有理数：内部恒为「最简、分母为正」。
class Rational {
public:
    Rational() : num_(0), den_(1) {}

    Rational(long long num, long long den) : num_(num), den_(den) {
        /* BEGIN 1 */
        // 1) 分母为 0 抛 std::invalid_argument；
        // 2) 把符号收到分子（分母恒正）；
        // 3) 用 std::gcd 约分（0 要写成 0/1）。
        throw std::logic_error("补全区尚未完成");
        /* END 1 */
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

// 四则运算统一走这里：op 是 '+' '-' '*' '/' 之一。
static Rational combine(const Rational& a, const Rational& b, char op) {
    /* BEGIN 2 */
    // 自己定分子分母怎么写，最后 return Rational(分子, 分母) —— 约分交给构造函数。
    // 除法要单独判 b 的分子为 0；未知运算符抛 std::invalid_argument。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
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
