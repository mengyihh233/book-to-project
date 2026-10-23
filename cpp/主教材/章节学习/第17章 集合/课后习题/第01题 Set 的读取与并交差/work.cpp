// 【本题说明开始】
// 第17章 · 习题1：Set 的读取与并交差
//
// 题目：给集合类写一个能读 `{a, b, c}` 的输入运算符，再用它读两个集合并输出并、交、差。
// 实现什么：`operator>>` 的解析 + `main` 里的两次读入与三行输出。
// 写在哪里：只补下方 BEGIN 1（集合的读取 / 位串解析）与 BEGIN 2（主程序的组合与输出）之间的代码。
// 文本格式：三行集合；格式非法返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

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
    // @@1@@
    /* END 1 */
}

int main() {
    try {
        /* BEGIN 2 */
        // 读两个集合，输出 并集 / 交集 / 差集 三行。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
