# 第11章 · 习题3：任意进制的整数转换 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 转换用「反复取余、逆序拼接」，注意 0 要输出 `0` 而不是空串。
- 负号只加一次：先把绝对值转成字符串，再决定要不要补 `-`。
- `from` 要逐字符校验：基数 16 时 `G` 非法，基数 2 时 `2` 非法。

## 容易错的边界

- 基数 36 时 `Z` 等于 35，不是 36。
- `to 0 16` 应输出 `0`。
- 别用 `std::stoi` 硬扛 36 进制——它只认到 36 但会把非法字符静默截断。

## 参考实现

```cpp
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

std::string intToString(long long value, int base) {
    /* BEGIN 1 */
        if (base < 2 || base > 36) throw std::invalid_argument("基数必须在 2 到 36 之间");
    const bool negative = value < 0;
    unsigned long long rest = negative ? static_cast<unsigned long long>(-(value + 1)) + 1ULL
                                       : static_cast<unsigned long long>(value);
    std::string digits;
    do {
        digits.push_back("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rest % static_cast<unsigned>(base)]);
        rest /= static_cast<unsigned>(base);
    } while (rest > 0);
    if (negative) digits.push_back('-');
    return std::string(digits.rbegin(), digits.rend());
    /* END 1 */
}

long long stringToInt(const std::string& text, int base) {
    /* BEGIN 2 */
        if (base < 2 || base > 36) throw std::invalid_argument("基数必须在 2 到 36 之间");
    std::size_t i = 0;
    bool negative = false;
    if (i < text.size() && text[i] == '-') { negative = true; ++i; }
    if (i >= text.size()) throw std::invalid_argument("缺少数字");
    long long value = 0;
    for (; i < text.size(); ++i) {
        const char ch = static_cast<char>(std::toupper(static_cast<unsigned char>(text[i])));
        int digit = 0;
        if (ch >= '0' && ch <= '9') digit = ch - '0';
        else if (ch >= 'A' && ch <= 'Z') digit = ch - 'A' + 10;
        else throw std::invalid_argument(std::string("非法数字：") + text[i]);
        if (digit >= base) throw std::invalid_argument(std::string("该进制下不允许：") + text[i]);
        value = value * base + digit;
    }
    return negative ? -value : value;
    /* END 2 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("命令条数必须在 1 到 100 之间");
        }
        for (int i = 0; i < n; ++i) {
            std::string command;
            if (!(std::cin >> command)) throw std::invalid_argument("命令不完整");
            if (command == "to") {
                long long value = 0;
                int base = 0;
                if (!(std::cin >> value >> base)) throw std::invalid_argument("to 缺少参数");
                if (base < 2 || base > 36) throw std::invalid_argument("基数必须在 2 到 36 之间");
                std::cout << intToString(value, base) << '\n';
            } else if (command == "from") {
                std::string text;
                int base = 0;
                if (!(std::cin >> text >> base)) throw std::invalid_argument("from 缺少参数");
                if (base < 2 || base > 36) throw std::invalid_argument("基数必须在 2 到 36 之间");
                std::cout << stringToInt(text, base) << '\n';
            } else {
                throw std::invalid_argument("未知命令：" + command);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
