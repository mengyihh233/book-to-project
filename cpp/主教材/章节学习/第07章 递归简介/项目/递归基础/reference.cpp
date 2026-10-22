// 参考实现：递归基础
// 第一行两个整数求最大公约数（辗转相除，递归）；第二行 n 求 n!（递归）。
#include <cstdlib>
#include <iostream>

namespace {

long long gcdOf(long long a, long long b) {
    a = std::llabs(a);
    b = std::llabs(b);
    if (b == 0) return a;          // 基准情形：余数为 0 时，另一个数就是答案
    return gcdOf(b, a % b);
}

long long factorial(int n) {
    if (n <= 1) return 1;          // 基准情形不能漏，否则递归不收敛
    return n * factorial(n - 1);
}

}  // namespace

int main() {
    long long a = 0, b = 0;
    int n = 0;
    if (!(std::cin >> a >> b)) {
        std::cerr << "第一行需要两个整数\n";
        return 2;
    }
    if (!(std::cin >> n)) {
        std::cerr << "第二行需要一个整数\n";
        return 2;
    }
    if (a == 0 && b == 0) {
        std::cerr << "gcd(0,0) 没有定义\n";
        return 2;
    }
    if (n < 0 || n > 20) {
        std::cerr << "n 必须在 0 到 20 之间\n";
        return 2;
    }
    std::cout << "gcd " << gcdOf(a, b) << "\n";
    std::cout << "阶乘 " << factorial(n) << "\n";
    return 0;
}
