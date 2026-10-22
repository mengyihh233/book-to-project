// 阅读注释｜第2章数学库表，PDF55；以下为中文概括和适配观察点。
// 先分清定义域、返回类型和角度单位；floor与ceil对负数方向不同。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <cassert>
#include <cmath>
#include <iostream>

bool near(double a, double b) { return std::abs(a - b) < 1e-9; }

void mathCalls() {
    const double pi = std::acos(-1.0);
    assert(near(std::abs(-2.5), 2.5));
    assert(near(std::sqrt(9.0), 3.0));
    assert(near(std::floor(-1.2), -2.0));
    assert(near(std::ceil(-1.2), -1.0));
    assert(near(std::exp(0.0), 1.0));
    assert(near(std::log(std::exp(2.0)), 2.0));
    assert(near(std::log10(100.0), 2.0));
    assert(near(std::pow(2.0, 3.0), 8.0));
    assert(near(std::sin(pi / 6), 0.5));
    assert(near(std::cos(pi / 3), 0.5));
    assert(near(std::tan(pi / 4), 1.0));
    assert(near(std::atan(1.0), pi / 4));
    assert(near(std::atan2(1.0, -1.0), 3 * pi / 4));
    // Check domains before calling sqrt/log; do not assert a platform-specific NaN.
    std::cout << "math: 13 calls OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { mathCalls(); return 0; }
#endif
