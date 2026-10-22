#include "rational.hpp"
#include <exception>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
namespace {
int passed{0};
void check(bool value, const char* label) {
    if (!value) throw std::runtime_error(label);
    ++passed;
}
template<class Exception, class Function> bool raises(Function function) {
    try { function(); } catch (const Exception&) { return true; }
    catch (const std::exception&) { return false; }
    return false;
}
}
int main() {
    using roberts_lab::Rational;
    try {
        check(Rational().numerator() == 0 && Rational().denominator() == 1, "default zero");
        check(Rational(7) == Rational(7, 1), "integer constructor");
        check(Rational(2, 4) == Rational(1, 2), "reduction");
        check(Rational(2, -4) == Rational(-1, 2), "negative denominator");
        check(Rational(-2, -4) == Rational(1, 2), "two negative signs");
        check(Rational(0, -7).denominator() == 1, "canonical zero");
        check(Rational(1, 2) + Rational(1, 3) == Rational(5, 6), "addition");
        check(Rational(1, 2) - Rational(2, 3) == Rational(-1, 6), "subtraction");
        check(Rational(-2, 3) * Rational(9, 4) == Rational(-3, 2), "multiplication");
        check(Rational(2, 3) / Rational(-4, 5) == Rational(-5, 6), "division");
        check(Rational(1, 2) + Rational(1, 3) + Rational(1, 6) == Rational(1), "exact sum");
        const Rational original(1, 2); const auto sum = original + Rational(1, 3);
        check(original == Rational(1, 2) && sum == Rational(5, 6), "const operands preserved");
        std::ostringstream out; out << Rational(-4, 6);
        check(out.str() == "-2/3", "stream insertion");
        check(raises<std::invalid_argument>([] { (void)Rational(1, 0); }), "zero denominator rejected");
        check(raises<std::invalid_argument>([] { (void)(Rational(1) / Rational()); }), "zero division rejected");
        constexpr auto lo = std::numeric_limits<std::int32_t>::min();
        constexpr auto hi = std::numeric_limits<std::int32_t>::max();
        check(Rational(lo, lo) == Rational(1), "minimum reduction");
        check(Rational(lo) / Rational(lo) == Rational(1), "minimum reciprocal operation");
        check(Rational(1, hi) + Rational(hi - 1, hi) == Rational(1), "reduce before narrowing");
        check(raises<std::out_of_range>([hi] { (void)(Rational(hi) + Rational(1)); }), "numerator overflow");
        check(raises<std::out_of_range>([lo] { (void)Rational(lo, -1); }), "sign normalization overflow");
        check(raises<std::out_of_range>([lo] { (void)Rational(1, lo); }), "denominator overflow");
        check(raises<std::out_of_range>([hi] { (void)(Rational(1, hi) * Rational(1, hi)); }), "result denominator range");
        std::cout << passed << "/22 rational checks passed\n";
    } catch (const std::exception& error) {
        std::cerr << "Failed after " << passed << " checks: " << error.what() << '\n';
        return 1;
    }
}
