// 阅读注释｜第3章字符库，PDF108；以下为中文概括和适配观察点。
// 分类可以重叠；结果判断非零即可，输入须转换成unsigned char。
// 对应work为调用/实现练习；先预测再看参考，不用抄到其他章节。
#include <cassert>
#include <cctype>
#include <iostream>

void characterCalls() {
    // ASCII inputs only. cctype predicates return nonzero, not necessarily 1.
    const unsigned char a = 'A', digit = '7', space = ' ', punct = '!';
    assert(std::isalpha(a) != 0);
    assert(std::isupper(a) != 0);
    assert(std::islower(static_cast<unsigned char>('a')) != 0);
    assert(std::isdigit(digit) != 0);
    assert(std::isxdigit(static_cast<unsigned char>('F')) != 0);
    assert(std::isalnum(punct) == 0);
    assert(std::ispunct(punct) != 0);
    assert(std::isspace(space) != 0);
    assert(std::isprint(space) != 0);
    assert(std::toupper(static_cast<unsigned char>('a')) == 'A');
    assert(std::tolower(a) == 'a');
    assert(std::isspace(static_cast<unsigned char>('\n')) != 0);
    assert(std::isprint(static_cast<unsigned char>('\n')) == 0);
    std::cout << "cctype: 11 interfaces OK\n";
}

#ifndef BOOK_API_NO_MAIN
int main() { characterCalls(); return 0; }
#endif
