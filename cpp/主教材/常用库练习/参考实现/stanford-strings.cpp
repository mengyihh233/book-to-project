// 阅读注释｜第3章strlib表，PDF114；以下为中文概括和适配观察点。
// 本文件调用自编roberts_compat适配；完整转换、失败分类与原始库差异在同组说明里。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
// Calls and independent boundary checks for our teaching adapter only.
#include "../兼容头文件/strlib.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>


namespace {
template <typename Exception, typename Function>
bool raisesStrlib(Function function) {
    try { function(); }
    catch (const Exception&) { return true; }
    catch (const std::exception&) { return false; }
    return false;
}
} // namespace

void stanfordStringCalls() {
    namespace rc = roberts_compat;
    int checked{0};
    const auto check = [&checked](bool passed, const char* label) {
        if (!passed) throw std::runtime_error(std::string("strlib check failed: ") + label);
        ++checked;
    };
    check(rc::integerToString(0) == "0" && rc::integerToString(-42) == "-42", "integer text");
    const int minimum = std::numeric_limits<int>::min();
    const int maximum = std::numeric_limits<int>::max();
    check(rc::stringToInteger(rc::integerToString(minimum)) == minimum &&
          rc::stringToInteger(rc::integerToString(maximum)) == maximum, "int extrema");
    check(rc::stringToInteger(" \t+007\n") == 7, "surrounding ASCII spaces and plus");
    check(raisesStrlib<std::invalid_argument>([] { (void)rc::stringToInteger(" \t"); }), "blank integer");
    check(raisesStrlib<std::invalid_argument>([] { (void)rc::stringToInteger("12px"); }), "integer suffix");
    check(raisesStrlib<std::out_of_range>([maximum] { (void)rc::stringToInteger(rc::integerToString(maximum) + "0"); }) &&
          raisesStrlib<std::out_of_range>([minimum] { (void)rc::stringToInteger(rc::integerToString(minimum) + "0"); }), "signed int overflow");
    check(rc::realToString(23.45) == "23.45" && rc::stringToReal("23.45") == 23.45, "ordinary decimal");
    check(rc::stringToReal(" -1.25e2 ") == -125.0, "scientific notation");
    check(rc::stringToReal("+.5") == 0.5 && rc::stringToReal("1.") == 1.0, "decimal point boundaries");
    const double adjacent = std::nextafter(1.0, 2.0);
    const double largest = std::numeric_limits<double>::max();
    check(rc::stringToReal(rc::realToString(adjacent)) == adjacent &&
          rc::stringToReal(rc::realToString(largest)) == largest, "finite round trip");
    check(raisesStrlib<std::invalid_argument>([] { (void)rc::stringToReal("3.14m"); }), "real suffix");
    bool invalidFormsRejected{true};
    for (const auto* text : {"", "nan", "inf", "0x1p2", "1,5", "1e+"}) {
        invalidFormsRejected = raisesStrlib<std::invalid_argument>([text] { (void)rc::stringToReal(text); }) && invalidFormsRejected;
    }
    check(invalidFormsRejected, "nondecimal or incomplete forms");
    check(raisesStrlib<std::out_of_range>([] { (void)rc::stringToReal("1e9999"); }), "real overflow");
    check(raisesStrlib<std::out_of_range>([] { (void)rc::stringToReal("1e-9999"); }), "real underflow");
    check(raisesStrlib<std::invalid_argument>([] { (void)rc::realToString(std::numeric_limits<double>::infinity()); }) &&
          raisesStrlib<std::invalid_argument>([] { (void)rc::realToString(std::numeric_limits<double>::quiet_NaN()); }), "finite values only");
    const std::string original{"cpp-17"};
    check(rc::toUpperCase(original) == "CPP-17" && original == "cpp-17", "returned copy");
    check(rc::toUpperCase("`az{ AZ09!") == "`AZ{ AZ09!", "ASCII a-z boundaries");
    check(rc::toUpperCase(std::string("\0a", 2)) == std::string("\0A", 2) &&
          rc::toUpperCase("\xC3\xA9z") == "\xC3\xA9Z" && rc::toUpperCase("").empty(), "non-ASCII bytes, zero and empty");
    std::cout << "strlib teaching adapter: " << checked << "/18 checks passed (not original Stanford library)\n";
}

#ifndef BOOK_API_NO_MAIN
int main() {
    try { stanfordStringCalls(); }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
    return 0;
}
#endif
