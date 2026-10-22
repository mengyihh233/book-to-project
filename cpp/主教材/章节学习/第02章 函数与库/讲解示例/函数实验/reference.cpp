// 基于Roberts第2章知识点的改编演示，不是原书程序逐字复制。
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

long long factorial(int n, bool trace = false);
long long combinations(int n, int k, bool trace = false);

void incrementCopy(int value) {
    ++value; // 只改变这次调用的局部副本。
    std::cout << "inside copy: " << value << '\n';
}

void incrementReference(int& value) {
    ++value; // 引用绑定调用者的变量。
}

const char* category(int) { return "integer"; }
const char* category(double) { return "floating"; }

double scale(double value, double factor = 1.0) {
    return value * factor;
}

long long factorial(int n, bool trace) {
    if (n < 0 || n > 20) {
        throw std::runtime_error("factorial demo accepts 0..20");
    }
    if (trace) std::cout << "  enter factorial(" << n << ")\n";
    long long product = 1;
    for (int i = 2; i <= n; ++i) product *= i;
    if (trace) std::cout << "  return " << product << '\n';
    return product;
}

long long combinations(int n, int k, bool trace) {
    if (n < 0 || n > 20 || k < 0 || k > n) {
        throw std::runtime_error("require 0 <= k <= n <= 20");
    }
    if (trace) std::cout << "enter combinations(" << n << ", " << k << ")\n";

    // 三条独立语句显式规定追踪顺序，避免假定操作数求值从左到右。
    const auto numerator = factorial(n, trace);
    const auto chosen = factorial(k, trace);
    const auto remaining = factorial(n - k, trace);
    const auto result = numerator / (chosen * remaining);

    if (trace) std::cout << "return combinations = " << result << '\n';
    return result;
}

int main() {
    try {
        std::cout << "[1] value / reference\n";
        int value = 10;
        incrementCopy(value);
        std::cout << "after copy: " << value << '\n';
        assert(value == 10);
        incrementReference(value);
        std::cout << "after reference: " << value << '\n';
        assert(value == 11);

        std::cout << "[2] overload / default argument\n";
        std::cout << category(2) << " / " << category(2.0) << '\n';
        assert(std::string(category(2)) == "integer");
        assert(std::string(category(2.0)) == "floating");
        assert(scale(4) == 4 && scale(4, 2) == 8);
        std::cout << "scale(4)=" << scale(4) << ", scale(4,2)=" << scale(4, 2) << '\n';

        std::cout << "[3] explicit function trace\n";
        const auto ways = combinations(6, 2, true);
        assert(ways == 15);
        assert(factorial(0) == 1);
        assert(combinations(0, 0) == 1);
        assert(combinations(20, 10) == 184756);

        bool rejected = false;
        try { combinations(6, 7); }
        catch (const std::runtime_error&) { rejected = true; }
        assert(rejected);
        rejected = false;
        try { factorial(21); }
        catch (const std::runtime_error&) { rejected = true; }
        assert(rejected);
        std::cout << "PASS: functions, contracts, and trace\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
