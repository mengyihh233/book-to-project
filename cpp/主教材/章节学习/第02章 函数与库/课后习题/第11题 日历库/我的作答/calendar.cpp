// 第2章习题11：自己的日历库。
// 题目：../README.md。只补三个 BEGIN / END 区域；头文件和主程序已给定。
// 保存本文件后，直接运行“本题：检查作答”；工具自动找到 ../work.cpp 并链接本库。
#include "calendar.h"
#include <stdexcept>

namespace calendar {

bool isLeapYear(int year) {
    /* BEGIN 1：判断闰年 */
    // 先校验年份在 1..9999 内，否则抛异常。
    // 采用公历规则：能被400整除，或能被4整除但不能被100整除。
    // 完成后删除占位 throw，返回 true 或 false。
    throw std::logic_error("补全区尚未完成：isLeapYear");
    /* END 1 */
}

int daysInMonth(Month month, int year) {
    /* BEGIN 2：返回本月天数 */
    // 校验年份和月份；Month 的合法值是 JANUARY(1) 到 DECEMBER(12)。
    // 大月31天、小月30天；二月复用 isLeapYear，返回28或29。
    // 完成后删除占位 throw，返回天数。
    throw std::logic_error("补全区尚未完成：daysInMonth");
    /* END 2 */
}

std::string monthToString(Month month) {
    /* BEGIN 3：把月份枚举转换成英文名称 */
    // 合法值1..12依次对应 JANUARY 到 DECEMBER；非法月份抛异常。
    // 可用 switch 或名称表；若用数组，注意月份从1开始、下标从0开始。
    // 完成后删除占位 throw，返回英文大写月份名。
    throw std::logic_error("补全区尚未完成：monthToString");
    /* END 3 */
}

}
