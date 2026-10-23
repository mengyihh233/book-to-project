# 第8章 · 习题9：全排列 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 递归基：`start` 到了字符串末尾，说明这一支已经排好，收进结果。
- 交换 → 递归 → **换回来**，三步缺一不可，否则后面的分支会拿到被改乱的串。
- 用 `std::set<string>` 收结果，天然去重 + 排序；题目说不关心顺序，本区要求字典序好判分。

## 容易错的边界

- `AAB` 若不去重会输出 6 行，正确答案只有 3 行。
- 只对 `start` 之后的字符交换，前缀不能再动，否则会漏排列。
- 长度 8 的串有 40320 个排列，题目把上限定在 7。

## 参考实现

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

void collectPermutations(std::string s, int start, std::set<std::string>& out) {
    /* BEGIN 1 */
        if (start == static_cast<int>(s.size())) {
        out.insert(s);
        return;
    }
    for (int i = start; i < static_cast<int>(s.size()); ++i) {
        std::swap(s[start], s[i]);
        collectPermutations(s, start + 1, out);
        std::swap(s[start], s[i]);
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
            if (line.empty() || line.size() > 7) throw std::invalid_argument("每行 1 到 7 个大写字母");
            for (char ch : line) {
                if (ch < 'A' || ch > 'Z') throw std::invalid_argument("只收大写字母");
            }
            std::set<std::string> out;
            collectPermutations(line, 0, out);
            for (const auto& p : out) std::cout << p << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
