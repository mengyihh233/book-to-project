# 第7章 · 习题10：递归逆序字符串 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 递归定义：把首字符挪到最后，剩下的继续逆序。
- 用整行读取（getline），不要用 `cin >>`，否则空格会被吃掉。
- 空串是合法的，返回空串即可。

## 容易错的边界

- 读行之前要 `cin.ignore()` 吞掉第一行后面的换行。
- 别用 std::reverse 混过去——这题练递归。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string reverseOf(const std::string& s) {
    /* BEGIN 1 */
        if (s.empty()) return std::string();
    return reverseOf(s.substr(1)) + s[0];
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }
        std::cin.ignore();
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                std::vector<std::string> lines;
        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) throw std::invalid_argument("行数不足");
            if (line.size() > 1000) throw std::invalid_argument("单行超过 1000 字符");
            lines.push_back(line);
        }
        for (const auto& line : lines) std::cout << reverseOf(line) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
