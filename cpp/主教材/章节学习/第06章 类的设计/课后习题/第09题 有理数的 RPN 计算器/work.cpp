// 【本题说明开始】
// 第6章 · 习题9：有理数的 RPN 计算器
//
// 题目：读入 n 行逆波兰表达式（操作数是整数或分数），用有理数精确求值。
// 实现什么：`evaluate()`（栈式求值 + 错误检查）+ `main` 的整行读取。
// 写在哪里：只补下方 BEGIN 1（evaluate 栈式求值）与 BEGIN 2（整行读取与输出）之间的代码。
// 文本格式：每条一行最简结果；非法表达式返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

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
    /* BEGIN 1 */
    // 1) 用 istringstream 按空白切记号；
    // 2) 含 '/' 或全数字的记号当分数/整数压栈（分母为 0 抛 invalid_argument）；
    // 3) 运算符要栈里至少两个数，弹出 b、a（注意顺序），压回 apply(a,b,op)；
    // 4) 结束时栈里必须正好剩一个数，否则抛 std::invalid_argument。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("表达式条数必须在 1 到 100 之间");
        }
        std::cin.ignore();

        /* BEGIN 2 */
        // 读 n 行（整行读，空行判非法），每行求值后输出最简结果。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
