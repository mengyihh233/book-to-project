#include "easter.h"
#include <iostream>
#include <cassert>
int main() {
    for (int y = 1583; y <= 4099; ++y) {
        std::string month; int day = 0;
        findEasterGregorian(y, month, day);
        std::cout << "G " << y << ' ' << month << ' ' << day << '\n';
        if (y >= 1700 && y <= 1899) {
            findEaster(y, month, day);
            std::cout << "B " << y << ' ' << month << ' ' << day << '\n';
        }
    }
    for (int year : {1699,1900}) {
        std::string month = "unchanged"; int day = -1; bool rejected = false;
        try { findEaster(year, month, day); } catch (const std::out_of_range&) { rejected = true; }
        assert(rejected && month == "unchanged" && day == -1);
    }
    for (int year : {1582,4100}) {
        std::string month = "unchanged"; int day = -1; bool rejected = false;
        try { findEasterGregorian(year, month, day); } catch (const std::out_of_range&) { rejected = true; }
        assert(rejected && month == "unchanged" && day == -1);
    }
}
