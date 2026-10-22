#pragma once
#include <string>
#include <stdexcept>
// 原书 PDF95 图2-18，只接受18、19世纪年份。
inline void findEaster(int year, std::string& month, int& day) {
    if (year < 1700 || year > 1899) throw std::out_of_range("book range: 1700..1899");
    const int a = year % 19;
    const int b = year % 4;
    const int c = year % 7;
    const int d = (19 * a + 23) % 30;
    const int e = (2 * b + 4 * c + 6 * d + (year < 1800 ? 3 : 4)) % 7;
    month = d + e <= 9 ? "March" : "April";
    day = d + e <= 9 ? 22 + d + e : d + e - 9;
}
// 自主扩展：公历计算规则；不代表各国历史采纳日历的日期。
// USNO Oudin算法，工作区显式限定1583..4099；C++整数除法向零截断。
inline void findEasterGregorian(int year, std::string& month, int& day) {
    if (year < 1583 || year > 4099) throw std::out_of_range("extension range: 1583..4099");
    const int c = year / 100;
    const int n = year - 19 * (year / 19);
    const int k = (c - 17) / 25;
    int i = c - c / 4 - (c - k) / 3 + 19 * n + 15;
    i -= 30 * (i / 30);
    i -= (i / 28) * (1 - (i / 28) * (29 / (i + 1)) * ((21 - n) / 11));
    int j = year + year / 4 + i + 2 - c + c / 4;
    j -= 7 * (j / 7);
    const int l = i - j;
    const int m = 3 + (l + 40) / 44;
    month = m == 3 ? "March" : "April";
    day = l + 28 - 31 * (m / 4);
}
