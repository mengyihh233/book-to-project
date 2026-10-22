#include "calendar.h"
#include <iostream>
#include <stdexcept>
void check(bool ok) { if (!ok) throw std::runtime_error("calendar contract failed"); }
template<class F> void rejects(F f) {
    bool rejected = false;
    try { f(); } catch (const std::invalid_argument&) { rejected = true; }
    check(rejected);
}
int main() {
    try {
        check(!calendar::isLeapYear(1900));
        check(calendar::isLeapYear(2000));
        check(!calendar::isLeapYear(2100));
        check(calendar::isLeapYear(2024));
        check(calendar::daysInMonth(calendar::FEBRUARY, 2000) == 29);
        check(calendar::daysInMonth(calendar::FEBRUARY, 1900) == 28);
        for (int year = 2000; year < 2400; ++year) {
            int total = 0;
            for (int m = 1; m <= 12; ++m) {
                auto month = static_cast<calendar::Month>(m);
                total += calendar::daysInMonth(month, year);
                check(!calendar::monthToString(month).empty());
            }
            check(total == (calendar::isLeapYear(year) ? 366 : 365));
        }
        rejects([] { calendar::daysInMonth(static_cast<calendar::Month>(0), 2024); });
        rejects([] { calendar::monthToString(static_cast<calendar::Month>(13)); });
        rejects([] { calendar::isLeapYear(0); });
        rejects([] { calendar::isLeapYear(10000); });
        std::cout << "PASS: calendar contracts, 400-year totals, invalid values\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
