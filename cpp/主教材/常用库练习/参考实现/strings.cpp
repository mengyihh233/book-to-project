// 阅读注释｜第3章string修改与遗留C字符串，PDF109—110；以下为中文概括和适配观察点。
// string可含零字节，C字符串在第一个零终止；查找失败先检查npos。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

void stringCalls() {
    std::string s = "image_007.png";
    assert(s.size() == 13 && s.length() == 13 && !s.empty());
    assert(s.at(0) == 'i' && s[0] == 'i');
    const auto dot = s.find('.');
    assert(dot != std::string::npos && s.substr(dot) == ".png");
    assert(s.find("missing") == std::string::npos);
    assert(s.substr(s.size()).empty());
    bool rejected = false;
    try { (void)s.at(s.size()); }
    catch (const std::out_of_range&) { rejected = true; }
    assert(rejected);
    s.insert(0, "raw_");
    s.erase(0, 4);
    s.replace(s.find("007"), 3, "008");
    s += ".bak";
    assert(s == "image_008.png.bak");
    const std::string original = "abc";
    std::string copy = original;
    copy[0] = 'A';
    assert(original == "abc" && copy == "Abc");
    assert(std::strlen(original.c_str()) == 3);
    assert(std::strcmp(original.c_str(), "abc") == 0);
    const std::string embedded("a\0b", 3);
    assert(embedded.size() == 3 && std::strlen(embedded.c_str()) == 1);
    std::cout << "string: lookup, edit and boundaries OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { stringCalls(); return 0; }
#endif
