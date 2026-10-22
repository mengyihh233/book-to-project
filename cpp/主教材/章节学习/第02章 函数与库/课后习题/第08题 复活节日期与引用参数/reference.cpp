#include "easter.h"
#include <iostream>
int main() {
    try {
        int year; std::string extra;
        if (!(std::cin >> year) || (std::cin >> extra)) throw std::invalid_argument("expected one integer year");
        std::string month; int day = 0;
        findEaster(year, month, day);
        std::cout << month << ' ' << day << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n'; return 2;
    }
}
