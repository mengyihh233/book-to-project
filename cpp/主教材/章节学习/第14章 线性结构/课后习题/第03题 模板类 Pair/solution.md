# 第14章 · 习题3：模板类 Pair · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 模板类的成员函数定义就写在类里最省事，省掉 `template` 前缀的重复书写。
- 类型判断：整行两个记号都能被整串解析成整数才算 int，否则按字符串处理。
- 排序用 `std::sort` 配 lambda，比较先看第一项再看第二项。

## 容易错的边界

- 字符串里可能有 `+`、`.`，别用 `stoi` 只解析前缀就当成数字。
- `(a, b)` 的括号和逗号后空格都要有，逐字符比对。
- 空输入行会让读入失败，属于非法。

## 参考实现

```cpp
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
class Pair {
public:
    Pair(T first, T second) : first_(first), second_(second) {}
    T first() const { return first_; }
    T second() const { return second_; }
    std::string toString() const {
        std::ostringstream out;
        out << '(' << first_ << ", " << second_ << ')';
        return out.str();
    }

private:
    T first_;
    T second_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("n 必须在 1 到 1000 之间");
        }
        /* BEGIN 1 */
        std::vector<std::string> firsts(n), seconds(n);
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> firsts[i] >> seconds[i])) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行不完整");
        }
        
        bool allInt = true;
        for (int i = 0; i < n && allInt; ++i) {
            for (const std::string* text : {&firsts[i], &seconds[i]}) {
                std::size_t used = 0;
                try {
                    std::stoll(*text, &used);
                } catch (const std::exception&) {
                    allInt = false;
                    break;
                }
                if (used != text->size()) allInt = false;
            }
        }
        
        if (allInt) {
            std::vector<Pair<long long>> pairs;
            for (int i = 0; i < n; ++i) {
                pairs.emplace_back(std::stoll(firsts[i]), std::stoll(seconds[i]));
            }
            std::sort(pairs.begin(), pairs.end(), [](const Pair<long long>& a, const Pair<long long>& b) {
                return a.first() != b.first() ? a.first() < b.first() : a.second() < b.second();
            });
            for (const auto& p : pairs) std::cout << p.toString() << '\n';
        } else {
            bool anyNumber = false;
            for (int i = 0; i < n; ++i) {
                for (const std::string* text : {&firsts[i], &seconds[i]}) {
                    std::size_t used = 0;
                    try {
                        std::stoll(*text, &used);
                        if (used == text->size()) anyNumber = true;
                    } catch (const std::exception&) {
                    }
                }
            }
            if (anyNumber) throw std::invalid_argument("同一组输入里不能混用数字和字符串");
            std::vector<Pair<std::string>> pairs;
            for (int i = 0; i < n; ++i) pairs.emplace_back(firsts[i], seconds[i]);
            std::sort(pairs.begin(), pairs.end(), [](const Pair<std::string>& a, const Pair<std::string>& b) {
                return a.first() != b.first() ? a.first() < b.first() : a.second() < b.second();
            });
            for (const auto& p : pairs) std::cout << p.toString() << '\n';
        }
        /* END 1 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
