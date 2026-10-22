#ifndef LEARNING_CALENDAR_H
#define LEARNING_CALENDAR_H
#include <string>
namespace calendar {
enum Month : int {
    JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
    JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};
// 本学习区约定：1..9999年，前推公历；不处理历史历法切换。
bool isLeapYear(int year);
int daysInMonth(Month month, int year);
std::string monthToString(Month month);
}
#endif
