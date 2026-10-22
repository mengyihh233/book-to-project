# 第6章 · 习题6：日期的加减运算 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 日期加减不是「日 + k」，跨月跨年必须走序列日号：`toSerial` 加完再 `fromSerial`。
- 范围检查要在换算之后做：2100-12-31 加 1 天得到 2101 年，必须报错。
- `operator+=` 返回 `*this` 的引用，和标准库风格一致，也方便链式调用。

## 容易错的边界

- 1900 和 2100 都不是闰年（整百但不能被 400 整除），2 月只有 28 天。
- 负数天数是「往前推」，`toSerial` 的结果直接相加即可，不要特判符号。
- 越界是在 `operator+=` 里抛的，`main` 的 try/catch 会接住，别自己再打印一次。

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

// 公历 <-> 序列日号（1970-01-01 为 0），闰年规则已经含在公式里。
long long toSerial(int y, int m, int d);
void fromSerial(long long serial, int& y, int& m, int& d);

class Date {
public:
    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {
        if (year < 1900 || year > 2100) throw std::invalid_argument("年份必须在 1900 到 2100 之间");
        if (month < 1 || month > 12) throw std::invalid_argument("月份必须在 1 到 12 之间");
        static const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int limit = days[month];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) limit = 29;
        if (day < 1 || day > limit) throw std::invalid_argument("日期超出当月天数");
    }

    int year() const { return year_; }
    int month() const { return month_; }
    int day() const { return day_; }

    // 加上（或减去）若干天，结果必须仍在 1900—2100 内，否则抛 out_of_range。
    Date& operator+=(long long days) {
        const long long shifted = toSerial(year_, month_, day_) + days;
        int y = 0, m = 0, d = 0;
        fromSerial(shifted, y, m, d);
        if (y < 1900 || y > 2100) throw std::out_of_range("结果超出 1900—2100");
        year_ = y;
        month_ = m;
        day_ = d;
        return *this;
    }

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
        return w < 0 ? w + 7 : w;
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
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }

        for (int i = 0; i < n; ++i) {
            std::string text;
            long long delta = 0;
            if (!(std::cin >> text >> delta)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行不完整");
            }
            int y = 0, m = 0, d = 0;
            if (!parseIso(text, y, m, d)) {
                throw std::invalid_argument("日期格式应为 YYYY-MM-DD：" + text);
            }
            Date date(y, m, d);
            date += delta;
            std::cout << date.toString() << ' ' << weekdayName(date.weekday()) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}

// —— 下面两个函数已给好，直接用 ——
long long toSerial(int y, int m, int d) {
    y -= m <= 2;
    const long long era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);
    const unsigned doy = static_cast<unsigned>((153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1);
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + static_cast<long long>(doe) - 719468;
}

void fromSerial(long long serial, int& y, int& m, int& d) {
    serial += 719468;
    const long long era = (serial >= 0 ? serial : serial - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(serial - era * 146097);
    const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    y = static_cast<int>(yoe) + static_cast<int>(era * 400);
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const unsigned mp = (5 * doy + 2) / 153;
    d = static_cast<int>(doy) - static_cast<int>((153 * mp + 2) / 5) + 1;
    m = static_cast<int>(mp) + (mp < 10 ? 3 : -9);
    y += (m <= 2);
}
```
