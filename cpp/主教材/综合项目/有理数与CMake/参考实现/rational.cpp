#include "rational.hpp"
// 第6章6.3配套：构造与运算都汇入normalized，以统一方式维护不变量。
// 这是自编C++17适配；原书定位PDF206—211，详细差异见README。
#include <limits>
#include <numeric>
#include <stdexcept>

namespace roberts_lab {
Rational Rational::normalized(std::int64_t numerator, std::int64_t denominator) {
    if (denominator == 0) throw std::invalid_argument("zero denominator");
    // All callers use products/sums of normalized int32 values. See solution.md.
    if (denominator < 0) { numerator = -numerator; denominator = -denominator; }
    // 先统一符号，再约分；numerator为0时gcd会让结果自然变成0/1。
    const auto divisor = std::gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
    if (numerator < std::numeric_limits<std::int32_t>::min() ||
        numerator > std::numeric_limits<std::int32_t>::max() ||
        denominator > std::numeric_limits<std::int32_t>::max())
        throw std::out_of_range("normalized rational outside int32 storage");
    Rational result;
    result.numerator_ = static_cast<std::int32_t>(numerator);
    result.denominator_ = static_cast<std::int32_t>(denominator);
    return result;
}

Rational::Rational(std::int32_t numerator, std::int32_t denominator) {
    *this = normalized(numerator, denominator);
}
Rational Rational::operator+(const Rational& other) const {
    const std::int64_t left = numerator_;
    const std::int64_t right = other.numerator_;
    return normalized(left * other.denominator_ + right * denominator_,
                      std::int64_t{denominator_} * other.denominator_);
}
Rational Rational::operator-(const Rational& other) const {
    const std::int64_t left = numerator_;
    const std::int64_t right = other.numerator_;
    return normalized(left * other.denominator_ - right * denominator_,
                      std::int64_t{denominator_} * other.denominator_);
}
Rational Rational::operator*(const Rational& other) const {
    return normalized(std::int64_t{numerator_} * other.numerator_,
                      std::int64_t{denominator_} * other.denominator_);
}
Rational Rational::operator/(const Rational& other) const {
    if (other.numerator_ == 0) throw std::invalid_argument("division by zero rational");
    return normalized(std::int64_t{numerator_} * other.denominator_,
                      std::int64_t{denominator_} * other.numerator_);
}
} // namespace roberts_lab
