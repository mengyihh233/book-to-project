#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

// 把 16 个 '0'/'1' 的串校验并组装成 unsigned short。
unsigned short parseBits(const std::string& text) {
    /* BEGIN 1 */
    if (text.size() != 16) {
        throw std::invalid_argument("比特串必须正好 16 个字符，实际 " + std::to_string(text.size()) + " 个");
    }
    
    unsigned short value = 0;
    for (char ch : text) {
        if (ch != '0' && ch != '1') {
            throw std::invalid_argument(std::string("比特串里只能有 0 和 1，出现了：") + ch);
        }
        value = static_cast<unsigned short>((value << 1) | (ch == '1' ? 1 : 0));
    }
    return value;
    /* END 1 */
}

// 把值打印成 16 个比特（高位补 0）。
std::string toBits(unsigned short value) {
    std::string text(16, '0');
    for (int i = 15; i >= 0; --i) {
        text[static_cast<std::size_t>(i)] = (value & 1u) ? '1' : '0';
        value = static_cast<unsigned short>(value >> 1);
    }
    return text;
}

int main() {
    try {
        /* BEGIN 2 */
        // 读两行比特串，先都解析完，再输出五行结果。
        std::string lineX;
        std::string lineY;
        if (!std::getline(std::cin, lineX) || !std::getline(std::cin, lineY)) {
            throw std::invalid_argument("需要两行比特串");
        }
        
        const unsigned short x = parseBits(lineX);
        const unsigned short y = parseBits(lineY);
        const unsigned short notY = static_cast<unsigned short>(~y);
        
        std::cout << "x & y = " << toBits(static_cast<unsigned short>(x & y)) << '\n';
        std::cout << "x | y = " << toBits(static_cast<unsigned short>(x | y)) << '\n';
        std::cout << "x ^ y = " << toBits(static_cast<unsigned short>(x ^ y)) << '\n';
        std::cout << "~y = " << toBits(notY) << '\n';
        std::cout << "x & ~y = " << toBits(static_cast<unsigned short>(x & notY)) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
