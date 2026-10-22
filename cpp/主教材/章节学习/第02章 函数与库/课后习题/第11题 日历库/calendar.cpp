#include "calendar.h"
#include <stdexcept>
namespace calendar {
namespace {
void validateYear(int year) {
    if (year < 1 || year > 9999) throw std::invalid_argument("year must be 1..9999");
}
int index(Month month) {
    const int value = static_cast<int>(month);
    if (value < 1 || value > 12) throw std::invalid_argument("invalid month");
    return value - 1;
}
}
bool isLeapYear(int year) {
    validateYear(year);
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}
int daysInMonth(Month month, int year) {
    validateYear(year);
    const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    const int i = index(month);
    if (month == FEBRUARY && isLeapYear(year)) return 29;
    return days[i];
}
std::string monthToString(Month month) {
    const char* names[] = {"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE",
                          "JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
    return names[index(month)];
}
}
