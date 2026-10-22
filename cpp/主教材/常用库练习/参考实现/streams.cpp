// 阅读注释｜第4章流与格式，PDF124—125；以下为中文概括和适配观察点。
// 格式状态会保留；输入失败后清状态与丢弃坏输入是两步。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

bool readWholeInteger(const std::string& text, int& result) {
    std::istringstream input(text);
    int candidate = 0;
    if (!(input >> candidate)) return false;
    input >> std::ws;
    if (!input.eof()) return false;
    result = candidate;
    return true;
}

void streamCalls() {
    std::ostringstream output;
    output << std::fixed << std::setprecision(2) << 1.234 << ' '
           << std::setfill('_') << std::setw(5) << 7 << ' ' << 8;
    assert(output.str() == "1.23 ____7 8"); // setw only affects the next field.
    std::ostringstream flags;
    flags << std::boolalpha << true << ' ' << std::noboolalpha << true
          << ' ' << std::showpos << 7 << ' ' << std::noshowpos << 7;
    assert(flags.str() == "true 1 +7 7");
    std::ostringstream alignment;
    alignment << std::setfill('_') << std::left << std::setw(3) << 7
              << std::right << std::setw(3) << 7;
    assert(alignment.str() == "7____7");
    std::ostringstream scientific;
    scientific << std::scientific << std::setprecision(2) << 12.0;
    assert(scientific.str().find("1.20e+") == 0);
    std::istringstream lines("Ada Lovelace\n\n");
    std::string line;
    assert(std::getline(lines, line) && line == "Ada Lovelace");
    assert(std::getline(lines, line) && line.empty());
    assert(!std::getline(lines, line));
    std::istringstream chars("ab");
    char c = 0;
    std::ostringstream copied;
    while (chars.get(c)) copied.put(c);
    assert(copied.str() == "ab");
    int value = 99;
    assert(readWholeInteger(" 42 ", value) && value == 42);
    assert(!readWholeInteger("42abc", value) && value == 42);
    assert(!readWholeInteger("", value) && value == 42);
    assert(!readWholeInteger("999999999999999999999", value));
    std::cout << "streams: formatting, reading and strict conversion OK\n";
}
void formatAndStateCalls() {
    std::ostringstream output;
    output << std::showpoint << std::fixed << std::setprecision(0) << 2.0;
    assert(output.str() == "2.");
    std::ostringstream plain;
    plain << std::noshowpoint << std::defaultfloat << 2.0;
    assert(plain.str() == "2");
    std::ostringstream exponent;
    exponent << std::uppercase << std::scientific << 1.0;
    assert(exponent.str().find('E') != std::string::npos);
    exponent.str("");
    exponent << std::nouppercase << 1.0;
    assert(exponent.str().find('e') != std::string::npos);
    std::ostringstream line;
    line << "ok" << std::endl << std::flush;
    assert(line.str() == "ok\n");

    std::istringstream input("bad\n42\n");
    int value = 0;
    assert(!(input >> value) && input.fail());
    input.clear(); // Reset flags, but the offending characters are still there.
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    assert(input >> value);
    assert(value == 42);
    std::cout << "format/state: remaining table switches and recovery OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { streamCalls(); formatAndStateCalls(); return 0; }
#endif
