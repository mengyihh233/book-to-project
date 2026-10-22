#include "../../../../教学辅助/input_line.h"
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#include <locale>
inline double stringToReal(const std::string& text) {
    std::istringstream in(text);in.imbue(std::locale::classic());double value;
    if(!(in>>value) || !std::isfinite(value)) throw std::invalid_argument("invalid real");
    in>>std::ws;
    if(!in.eof()) throw std::invalid_argument("trailing characters");
    return value;
}
inline std::string realToString(double value) {
    if(!std::isfinite(value)) throw std::invalid_argument("non-finite real");
    std::ostringstream out;out.imbue(std::locale::classic());
    out<<std::setprecision(std::numeric_limits<double>::max_digits10)<<value;
    return out.str();
}
