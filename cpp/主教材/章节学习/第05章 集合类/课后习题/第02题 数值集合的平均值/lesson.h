#pragma once
#include "../../../../教学辅助/vector_lesson.h"
inline double mean(const std::vector<double>& data) {
    validateNumbers(data);long double average=0;std::size_t count=0;
    for(double x:data) {++count;average+=(static_cast<long double>(x)-average)/count;}
    return static_cast<double>(average);
}
