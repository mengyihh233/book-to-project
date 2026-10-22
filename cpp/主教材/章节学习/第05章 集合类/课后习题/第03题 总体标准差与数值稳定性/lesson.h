#pragma once
#include "../../../../教学辅助/vector_lesson.h"
inline double stddev(const std::vector<double>& data) {
    validateNumbers(data);long double average=0,m2=0;std::size_t count=0;
    for(double x:data) {
        ++count;long double delta=static_cast<long double>(x)-average;
        average+=delta/count;m2+=delta*(static_cast<long double>(x)-average);
    }
    return static_cast<double>(std::sqrt(std::max(0.0L,m2/data.size())));
}
