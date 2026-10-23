# 第8章 · 习题10：手机键盘记忆术 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 递归基是「数字用完了」，此时 `current` 就是一个完整组合。
- 每个数字对应 3 或 4 个字母（7 和 9 是 4 个），循环要按实际长度走。
- 回溯时记住 `pop_back()`，否则 `current` 会越来越长。

## 容易错的边界

- 0 和 1 在键盘上没有字母，属于非法输入。
- 长度 6 时有 4⁶ = 4096 种组合，别把它当「随便试试」的数据量。
- 同一个数字串只输出一次，别把重复组合也打出来（本题组合天然不重复，但别手动去重排乱顺序）。

## 参考实现

```cpp
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 数字 -> 字母表（不是数字就返回空串）。
inline const char* keypad(char digit) {
    switch (digit) {
        case '2': return "ABC";
        case '3': return "DEF";
        case '4': return "GHI";
        case '5': return "JKL";
        case '6': return "MNO";
        case '7': return "PQRS";
        case '8': return "TUV";
        case '9': return "WXYZ";
        default: return "";
    }
}

void collectMnemonics(const std::string& digits, std::size_t index,
                      std::string& current, std::vector<std::string>& out) {
    /* BEGIN 1 */
        if (index == digits.size()) {
        out.push_back(current);
        return;
    }
    for (const char* p = keypad(digits[index]); *p; ++p) {
        current.push_back(*p);
        collectMnemonics(digits, index + 1, current, out);
        current.pop_back();
    }
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 5) {
            throw std::invalid_argument("行数必须在 1 到 5 之间");
        }
        std::cin.ignore();
        /* BEGIN 2 */
                for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) throw std::invalid_argument("行数不足");
            if (line.empty() || line.size() > 6) throw std::invalid_argument("每行 1 到 6 个数字");
            for (char ch : line) {
                if (ch < '2' || ch > '9') throw std::invalid_argument("只收 2 到 9 的数字");
            }
            std::vector<std::string> out;
            std::string current;
            collectMnemonics(line, 0, current, out);
            std::sort(out.begin(), out.end());
            for (const auto& item : out) std::cout << item << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
