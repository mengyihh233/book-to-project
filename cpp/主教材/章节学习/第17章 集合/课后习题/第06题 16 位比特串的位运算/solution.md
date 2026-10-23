# 第17章 · 习题6：16 位比特串的位运算 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 「16 位」就是 `unsigned short` 的位宽，逐字符 `value = value << 1 | bit` 正好组装出一个数。
- 打印回去要从最高位往低位数，`(value >> i) & 1` 取第 i 位，缺的高位补 `0`。
- `~y` 在 `unsigned short` 上是 16 位取反；如果提成 `int` 再取反会多出一堆高位的 1，所以要限定在 16 位里打印。
- 先校验两行都合法再输出——半份结果同样是错的。

## 容易错的边界

- `unsigned short` 参与运算会被整型提升成 `int`，`~y` 拿到的是 32 位结果，打印时只看低 16 位就对了。
- 别用 `std::stoi` 直接转十进制——那是把 `0100` 当十进制一百，不是比特串。
- 长度 15 或 17 都算错，不是「补个 0 就行」。
- `x & ~y` 里的 `~y` 要先截回 16 位，否则高位全 1 会让结果看起来不对。

## 参考实现

```cpp
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
```
