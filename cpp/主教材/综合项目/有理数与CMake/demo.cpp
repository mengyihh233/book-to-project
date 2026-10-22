#include "rational.hpp"
#include <exception>
#include <iostream>
int main() {
    using roberts_lab::Rational;
    try {
        // 原书6.3用分数计算说明表示方式的重要性；先预测精确和，再运行。
        // 此处通过接口调用，用户不需要知道类内部怎样保存与约分。
        const Rational half(1, 2), third(1, 3), sixth(1, 6);
        std::cout << "1/2 + 1/3 + 1/6 = " << half + third + sixth << '\n';
        std::cout << "2/-4 normalizes to " << Rational(2, -4) << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
