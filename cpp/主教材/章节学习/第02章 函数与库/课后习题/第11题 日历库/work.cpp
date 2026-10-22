// 【本题说明开始】
// 第2章习题11：日历库
//
// 题目：输入1..9999的整数年份，输出12个月的英文大写名称和天数。
// 采用公历闰年规则；Month 的合法值为 JANUARY(1) 到 DECEMBER(12)。
//
// 写在哪里：我的作答/calendar.cpp 的 BEGIN 1 到 BEGIN 3 函数体。
// 依次实现 isLeapYear、daysInMonth、monthToString；年份或月份非法时抛异常。
// 对照接口：我的作答/calendar.h 已给出 Month 枚举与声明，无需修改。
// 本文件 work.cpp 是给定主程序，负责读入、遍历月份、输出与错误处理，不用重写。
// 怎么做：先写闰年判断，再复用它处理二月，最后完成英文月份映射。
//
// 怎么检查：先保存库 cpp，直接运行任务“本题：检查作答”，无需切换到本文件。
// 工具自动找到本文件并链接自己的库实现，比对登记的9组输入、输出与退出码。
// 正常返回0；错误说明写到cerr、返回2，cout为空；不要输出“请输入”等提示语。
// 样例输入：2012
// 期望输出：共12行，首行为 JANUARY 31，第二行为 FEBRUARY 29；完整样例见README。
// input.txt 只是手动输入；外层 calendar.cpp 是参考实现，不是作答位置。
// 完整题目与文本格式：README.md。
// 【本题说明结束】
//
// 给定调用入口：请在我的作答目录的库 cpp 内补全函数。
#include "我的作答/calendar.h"
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
