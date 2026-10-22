#ifndef BOOK_LEARNING_ROBERTS_COMPAT_STRLIB_HPP
#define BOOK_LEARNING_ROBERTS_COMPAT_STRLIB_HPP

// Self-written C++17 teaching adapter. Not the original Stanford library.
// Error and numeric formatting policies are documented in ../stanford-strings.md.
#include <array>
#include <charconv>
#include <cmath>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

namespace roberts_compat {
namespace detail {
inline bool isAsciiSpace(char ch) noexcept {
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

inline bool isDigit(char ch) noexcept { return ch >= '0' && ch <= '9'; }

inline std::string_view trim(std::string_view text) noexcept {
    while (!text.empty() && isAsciiSpace(text.front())) text.remove_prefix(1);
    while (!text.empty() && isAsciiSpace(text.back())) text.remove_suffix(1);
    return text;
}

inline bool isInteger(std::string_view token) noexcept {
    std::size_t pos{0};
    if (!token.empty() && (token.front() == '+' || token.front() == '-')) ++pos;
    if (pos == token.size()) return false;
    for (; pos < token.size(); ++pos) if (!isDigit(token[pos])) return false;
    return true;
}

inline bool isDecimalReal(std::string_view token) noexcept {
    std::size_t pos{0};
    if (!token.empty() && (token.front() == '+' || token.front() == '-')) ++pos;
    bool hasDigit{false};
    while (pos < token.size() && isDigit(token[pos])) { hasDigit = true; ++pos; }
    if (pos < token.size() && token[pos] == '.') {
        ++pos;
        while (pos < token.size() && isDigit(token[pos])) { hasDigit = true; ++pos; }
    }
    if (!hasDigit) return false;
    if (pos < token.size() && (token[pos] == 'e' || token[pos] == 'E')) {
        ++pos;
        if (pos < token.size() && (token[pos] == '+' || token[pos] == '-')) ++pos;
        const auto exponentStart = pos;
        while (pos < token.size() && isDigit(token[pos])) ++pos;
        if (pos == exponentStart) return false;
    }
    return pos == token.size();
}
} // namespace detail

inline std::string integerToString(int value) { return std::to_string(value); }

inline int stringToInteger(const std::string& text) {
    auto token = detail::trim(text);
    if (!detail::isInteger(token)) throw std::invalid_argument("integer syntax");
    if (token.front() == '+') token.remove_prefix(1);
    int value{0};
    const auto result = std::from_chars(token.data(), token.data() + token.size(), value, 10);
    if (result.ec == std::errc::result_out_of_range) throw std::out_of_range("int range");
    if (result.ec != std::errc{} || result.ptr != token.data() + token.size())
        throw std::invalid_argument("integer syntax");
    return value;
}

inline std::string realToString(double value) {
    if (!std::isfinite(value)) throw std::invalid_argument("finite double required");
    std::array<char, 128> buffer{};
    const auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(),
                                      value, std::chars_format::general);
    if (result.ec != std::errc{}) throw std::length_error("real text buffer");
    std::string text(buffer.data(), result.ptr);
    for (auto& ch : text) if (ch == 'e') ch = 'E';
    return text;
}

inline double stringToReal(const std::string& text) {
    auto token = detail::trim(text);
    if (!detail::isDecimalReal(token)) throw std::invalid_argument("decimal real syntax");
    if (token.front() == '+') token.remove_prefix(1);
    double value{0.0};
    const auto result = std::from_chars(token.data(), token.data() + token.size(),
                                        value, std::chars_format::general);
    if (result.ec == std::errc::result_out_of_range) throw std::out_of_range("double range");
    if (result.ec != std::errc{} || result.ptr != token.data() + token.size() || !std::isfinite(value))
        throw std::invalid_argument("decimal real syntax");
    return value;
}

inline std::string toUpperCase(std::string text) {
    for (auto& ch : text) {
        if (ch >= 'a' && ch <= 'z') ch = static_cast<char>(ch - 'a' + 'A');
    }
    return text;
}
} // namespace roberts_compat

#endif // BOOK_LEARNING_ROBERTS_COMPAT_STRLIB_HPP
