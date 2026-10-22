#ifndef ROBERTS_LAB_RATIONAL_HPP
#define ROBERTS_LAB_RATIONAL_HPP
#include <cstdint>
#include <ostream>

namespace roberts_lab {
// Teaching adaptation: normalized signed 32-bit numerator, positive 32-bit denominator.
class Rational {
public:
    Rational() = default;
    explicit Rational(std::int32_t value) : Rational(value, 1) {}
    Rational(std::int32_t numerator, std::int32_t denominator);
    std::int32_t numerator() const noexcept { return numerator_; }
    std::int32_t denominator() const noexcept { return denominator_; }
    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;
    bool operator==(const Rational& other) const noexcept {
        return numerator_ == other.numerator_ && denominator_ == other.denominator_;
    }
private:
    static Rational normalized(std::int64_t numerator, std::int64_t denominator);
    std::int32_t numerator_{0};
    std::int32_t denominator_{1};
};
inline std::ostream& operator<<(std::ostream& out, const Rational& value) {
    return out << value.numerator() << '/' << value.denominator();
}
} // namespace roberts_lab
#endif
