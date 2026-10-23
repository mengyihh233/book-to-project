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
