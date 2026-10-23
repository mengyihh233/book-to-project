# 第17章 · 习题1：Set 的读取与并交差 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- `>>` 要整行读（`getline`），因为元素之间可能有空格，用 `in >> token` 会被空格切断。
- 先剥掉首尾空白，再检查 `front() == '{'`、`back() == '}'`，然后取中间那段按逗号切。
- 空集 `{}` 要能正常读成空集合，不能当成缺括号——括号里面只剩空白时直接返回。
- 解析失败抛 `std::invalid_argument`，`main` 的 `catch` 统一返回 2。

## 容易错的边界

- 最后一个元素后面没有逗号，循环要处理「找不到逗号」的情况，别多切出一个空串。
- `{},` 或 `{a,,b}` 里出现的空元素是错误，不是空集。
- 别把重复元素当错误——集合本来就会去重。
- `operator>>` 返回的是流本身（`return in;`），这样 `cin >> a >> b` 才能连着写。

## 参考实现

```cpp
#include <cctype>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

class Set {
public:
    Set() {}
    void insert(const std::string& value) { values_.insert(value); }
    bool contains(const std::string& value) const { return values_.count(value) > 0; }
    const std::set<std::string>& values() const { return values_; }

private:
    std::set<std::string> values_;   // 用 std::set 保证有序、去重
};

std::ostream& operator<<(std::ostream& out, const Set& set) {
    out << '{';
    bool first = true;
    for (const std::string& value : set.values()) {
        if (!first) out << ", ";
        out << value;
        first = false;
    }
    return out << '}';
}

Set operator+(const Set& a, const Set& b) {
    Set result = a;
    for (const std::string& value : b.values()) result.insert(value);
    return result;
}

Set operator*(const Set& a, const Set& b) {
    Set result;
    for (const std::string& value : a.values()) {
        if (b.contains(value)) result.insert(value);
    }
    return result;
}

Set operator-(const Set& a, const Set& b) {
    Set result;
    for (const std::string& value : a.values()) {
        if (!b.contains(value)) result.insert(value);
    }
    return result;
}

std::istream& operator>>(std::istream& in, Set& set) {
    /* BEGIN 1 */
    std::string text;
    if (!std::getline(in, text)) {
        throw std::invalid_argument("集合那一行缺失");
    }
    
    // 去掉首尾空白
    std::size_t first = 0;
    while (first < text.size() && std::isspace(static_cast<unsigned char>(text[first]))) ++first;
    std::size_t last = text.size();
    while (last > first && std::isspace(static_cast<unsigned char>(text[last - 1]))) --last;
    text = text.substr(first, last - first);
    
    if (text.size() < 2 || text.front() != '{' || text.back() != '}') {
        throw std::invalid_argument("集合必须写成 {…}：" + text);
    }
    
    const std::string body = text.substr(1, text.size() - 2);
    if (body.find_first_not_of(" \t") == std::string::npos) return in;   // `{}`：空集
    
    std::size_t at = 0;
    while (true) {
        const std::size_t comma = body.find(',', at);
        std::string piece = body.substr(at, comma == std::string::npos ? std::string::npos : comma - at);
    
        std::size_t head = 0;
        while (head < piece.size() && std::isspace(static_cast<unsigned char>(piece[head]))) ++head;
        std::size_t tail = piece.size();
        while (tail > head && std::isspace(static_cast<unsigned char>(piece[tail - 1]))) --tail;
        piece = piece.substr(head, tail - head);
    
        if (piece.empty()) throw std::invalid_argument("逗号之间是空的");
        if (piece.find_first_of("{},\t ") != std::string::npos) {
            throw std::invalid_argument("元素里不能有空格、逗号或花括号：" + piece);
        }
        set.insert(piece);
    
        if (comma == std::string::npos) break;
        at = comma + 1;
    }
    return in;
    /* END 1 */
}

int main() {
    try {
        /* BEGIN 2 */
        // 读两个集合，输出 并集 / 交集 / 差集 三行。
        Set a;
        Set b;
        std::cin >> a;
        std::cin >> b;
        
        std::cout << "并集 = " << (a + b) << '\n';
        std::cout << "交集 = " << (a * b) << '\n';
        std::cout << "差集 = " << (a - b) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
```
