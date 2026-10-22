# 第6章 · 习题5：Date 类的构造与星期 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 先判年份范围，再判月份，最后按「当月天数」判日——顺序错了会出现 13 月 32 日这种漏网。
- 闰年写成 `(y%4==0 && y%100!=0) || y%400==0`；只写 `y%4==0` 会把 1900 判成闰年。
- 星期和格式化都已经给好，`Date` 只要能构造出正确的年月日，输出自然对。

## 容易错的边界

- 1900 年不是闰年（整百但不能被 400 整除），2100 年也不是。
- `2023-2-3` 这种不补零的输入格式不合法，本区只收 `YYYY-MM-DD`。
- 日期非法是在构造函数里抛的，`main` 已经包了 try/catch，别自己再吞掉异常。

## 参考实现

```cpp
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

inline const char* weekdayName(int w) {
    static const char* names[7] = {"星期日", "星期一", "星期二", "星期三",
                                   "星期四", "星期五", "星期六"};
    return names[w];
}

inline bool parseIso(const std::string& text, int& year, int& month, int& day) {
    if (text.size() != 10 || text[4] != '-' || text[7] != '-') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(text[i]))) return false;
    }
    year = std::stoi(text.substr(0, 4));
    month = std::stoi(text.substr(5, 2));
    day = std::stoi(text.substr(8, 2));
    return true;
}

class Date {
public:
    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {
        if (year < 1900 || year > 2100) {
            throw std::invalid_argument("年份必须在 1900 到 2100 之间");
        }
        if (month < 1 || month > 12) {
            throw std::invalid_argument("月份必须在 1 到 12 之间");
        }
        static const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int limit = days[month];
        const bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
        if (month == 2 && leap) limit = 29;
        if (day < 1 || day > limit) {
            throw std::invalid_argument("日期超出当月天数");
        }
    }

    int year() const { return year_; }
    int month() const { return month_; }
    int day() const { return day_; }

    std::string toString() const {
        static const char* months[13] = {"",    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                         "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
        return std::to_string(day_) + '-' + months[month_] + '-' + std::to_string(year_);
    }

    int weekday() const {
        static const int shift[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int y = year_;
        if (month_ < 3) --y;
        int w = (y + y / 4 - y / 100 + y / 400 + shift[month_ - 1] + day_) % 7;
        if (w < 0) w += 7;
        return w;
    }

private:
    int year_;
    int month_;
    int day_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("日期条数必须在 1 到 100 之间");
        }
        for (int i = 0; i < n; ++i) {
            std::string text;
            if (!(std::cin >> text)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 条日期读不到");
            }
            int y = 0, m = 0, d = 0;
            if (!parseIso(text, y, m, d)) {
                throw std::invalid_argument("日期格式应为 YYYY-MM-DD：" + text);
            }
            const Date date(y, m, d);
            std::cout << date.toString() << ' ' << weekdayName(date.weekday()) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
