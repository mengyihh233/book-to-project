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
