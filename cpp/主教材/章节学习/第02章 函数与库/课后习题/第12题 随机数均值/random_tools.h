#pragma once
#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
// 教学适配：固定原始引擎到数值的映射，避免不同标准库分布器的序列差异。
inline std::uint32_t readUnsigned(std::uint64_t maximum) {
    std::string text;
    if (!(std::cin >> text) || text.empty() || text.find_first_not_of("0123456789") != std::string::npos)
        throw std::invalid_argument("expected unsigned integer");
    const auto value = std::stoull(text);
    if (value > maximum) throw std::out_of_range("integer out of range");
    return static_cast<std::uint32_t>(value);
}
inline void requireEnd() {
    std::string extra;
    if (std::cin >> extra) throw std::invalid_argument("unexpected extra input");
}
inline double unitReal(std::mt19937& engine) {
    return (static_cast<double>(engine()) + 0.5) / 4294967296.0;
}
inline bool halfEvent(std::mt19937& engine) { return engine() < 2147483648ULL; }
