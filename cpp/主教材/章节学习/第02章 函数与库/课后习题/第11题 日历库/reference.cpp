#include "calendar.h"
#include <iostream>
#include <stdexcept>
int main() {
    try {
        int year;
        if (!(std::cin >> year)) throw std::runtime_error("integer year required");
        std::cin >> std::ws;
        if (!std::cin.eof()) throw std::runtime_error("unexpected input");
        calendar::isLeapYear(year); // 在输出任何正常结果前完成校验。
        for (int m = 1; m <= 12; ++m) {
            const auto month = static_cast<calendar::Month>(m);
            std::cout << calendar::monthToString(month) << ' '
                      << calendar::daysInMonth(month, year) << '\n';
        }
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 2; }
}
