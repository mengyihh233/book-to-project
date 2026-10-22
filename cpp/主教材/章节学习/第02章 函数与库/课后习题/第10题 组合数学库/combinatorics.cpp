#include "combinatorics.h"
#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>
namespace combinatorics {
namespace {
void validate(long long n, long long k) {
    if (n < 0 || n > 1000000 || k < 0 || k > n) {
        throw std::invalid_argument("require 0 <= k <= n <= 1000000");
    }
}
long long multiply(long long x, long long y) {
    if (y != 0 && x > std::numeric_limits<long long>::max() / y) {
        throw std::overflow_error("result exceeds signed 64-bit range");
    }
    return x * y;
}
}
long long permutations(long long n, long long k) {
    validate(n, k);
    long long value = 1;
    for (long long i = 0; i < k; ++i) value = multiply(value, n - i);
    return value;
}
long long combinations(long long n, long long k) {
    validate(n, k);
    k = std::min(k, n - k);
    long long value = 1;
    for (long long i = 1; i <= k; ++i) {
        long long numerator = n - k + i;
        long long denominator = i;
        const auto a = std::gcd(numerator, denominator);
        numerator /= a;
        denominator /= a;
        const auto b = std::gcd(value, denominator);
        value /= b;
        denominator /= b;
        if (denominator != 1) throw std::logic_error("cancellation invariant");
        value = multiply(value, numerator);
    }
    return value;
}
}
