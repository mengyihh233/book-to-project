// 【本题说明开始】
// 第6章 · 习题5：Date 类的构造与星期
//
// 题目：读入 n 个 ISO 日期（`YYYY-MM-DD`），校验后输出 `dd-MMM-yyyy` 与星期几。
// 实现什么：`Date` 的构造函数（年/月/日校验，含闰年）+ `main` 的解析与输出循环。
// 写在哪里：只补下方 BEGIN 1（Date 构造函数）与 BEGIN 2（读入、构造与输出）之间的代码。
// 文本格式：每行 `dd-MMM-yyyy 星期X`；非法日期返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

inline const char* weekdayName(int w) {
    static const char* names[7] = {"星期日", "星期一", "星期二", "星期三",
                                   "星期四", "星期五", "星期六"};
    return names[w];
}

// 解析 "YYYY-MM-DD"；格式不对返回 false。
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
        /* BEGIN 1 */
        // 校验：1900 ≤ 年 ≤ 2100、1 ≤ 月 ≤ 12、日不超过当月天数
        //（闰年规则：能被 4 整除，但整百年必须能被 400 整除）。
        // 合法就存进 year_/month_/day_；非法抛 std::invalid_argument。
        throw std::logic_error("补全区尚未完成");
        /* END 1 */
    }

    int year() const { return year_; }
    int month() const { return month_; }
    int day() const { return day_; }

    // dd-MMM-yyyy，例如 20-JUL-1969；日不补零。
    std::string toString() const {
        static const char* months[13] = {"",    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                         "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
        return std::to_string(day_) + '-' + months[month_] + '-' + std::to_string(year_);
    }

    // 0=星期日 … 6=星期六（坂本算法）。
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

        /* BEGIN 2 */
        // 每条读一个 "YYYY-MM-DD"：解析失败抛 std::invalid_argument；
        // 构造 Date（非法日期由构造函数抛），再输出「dd-MMM-yyyy 星期X」。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
