# 第15章 · 习题4：罗马数字转十进制 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 查找表就是「字符 → 数值」的对应，用 `std::string::find` 拿下标再查数组最快，也最不容易写错。
- 判断减法看的是**下一位**，所以循环里要先确认 `i + 1 < size()` 再比较，末尾那位永远加。
- 先把 n 行全部读完、全部转成数值并校验，最后统一输出——非法输入才不会吐出半份结果。

## 容易错的边界

- `MMMCMXCIX` 是 3999，`MMMM` 就超范围了，边界要卡在 1—3999。
- 别把「前一位比当前位小」写成减法判断——方向反了 `MCMLXIX` 会算成别的数。
- 读 n 之后要用 `getline` 吃掉行尾，否则第一行读到空串。
- 空行不是「0」，直接算非法。

## 参考实现

```cpp
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 查找表：字符 -> 数值。只认 I V X L C D M（进来之前已统一成大写）。
int romanToDecimal(const std::string& str) {
    /* BEGIN 1 */
    static const std::string kLetters = "IVXLCDM";
    static const int kValues[] = {1, 5, 10, 50, 100, 500, 1000};
    
    std::vector<int> digits;
    for (char ch : str) {
        const std::size_t where = kLetters.find(ch);
        if (where == std::string::npos) {
            throw std::invalid_argument(std::string("不是罗马数字字符：") + ch);
        }
        digits.push_back(kValues[where]);
    }
    
    int total = 0;
    for (std::size_t i = 0; i < digits.size(); ++i) {
        if (i + 1 < digits.size() && digits[i] < digits[i + 1]) {
            total -= digits[i];
        } else {
            total += digits[i];
        }
    }
    return total;
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("行数必须在 1 到 1000 之间");
        }
        std::string rest;
        std::getline(std::cin, rest);
        /* BEGIN 2 */
        // 先读完 n 行、逐行转成数值并校验（1..3999），全部通过之后再逐行输出。
        std::vector<int> values;
        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行缺失");
            }
            std::size_t first = 0;
            while (first < line.size() && std::isspace(static_cast<unsigned char>(line[first]))) ++first;
            std::size_t last = line.size();
            while (last > first && std::isspace(static_cast<unsigned char>(line[last - 1]))) --last;
            line = line.substr(first, last - first);
            if (line.empty()) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行是空的");
            for (char& ch : line) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            const int value = romanToDecimal(line);
            if (value < 1 || value > 3999) {
                throw std::invalid_argument("数值必须在 1 到 3999 之间");
            }
            values.push_back(value);
        }
        for (int value : values) std::cout << value << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
