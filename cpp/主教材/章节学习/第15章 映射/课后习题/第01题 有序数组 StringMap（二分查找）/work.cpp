// 【本题说明开始】
// 第15章 · 习题1：有序数组 StringMap（二分查找）
//
// 题目：用「始终按 key 升序的键值对数组」实现一个字符串映射表，查找走二分而不是从头扫。
// 实现什么：`StringMap` 的成员函数（含二分 `findKey`）+ `main` 的命令校验与分派。
// 写在哪里：只补下方 BEGIN 1（数据结构的实现）与 BEGIN 2（读入、校验与输出）之间的代码。
// 文本格式：按命令输出；非法命令返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// 按空白切一行；空行返回空 vector。
std::vector<std::string> splitTokens(const std::string& line) {
    std::vector<std::string> tokens;
    std::size_t at = 0;
    while (at < line.size()) {
        while (at < line.size() && std::isspace(static_cast<unsigned char>(line[at]))) ++at;
        const std::size_t start = at;
        while (at < line.size() && !std::isspace(static_cast<unsigned char>(line[at]))) ++at;
        if (at > start) tokens.push_back(line.substr(start, at - start));
    }
    return tokens;
}

// 有序数组实现的字符串映射表：entries_ 始终按 key 升序，查找走二分。
class StringMap {
public:
    StringMap() {}

    int size() const;
    bool isEmpty() const;
    bool containsKey(const std::string& key) const;
    std::string get(const std::string& key) const;   // 找不到返回空串，配 containsKey 用
    void put(const std::string& key, const std::string& value);
    void remove(const std::string& key);
    void clear();
    void dump() const;                                // 按 key 升序输出 key=value

private:
    int findKey(const std::string& key) const;        // 二分：找到返回下标，找不到返回 -1
    std::vector<std::pair<std::string, std::string>> entries_;
};

/* BEGIN 1 */
// @@1@@
/* END 1 */

int main() {
    try {
        int m = 0;
        if (!(std::cin >> m) || m < 0 || m > 1000) {
            throw std::invalid_argument("命令条数必须在 0 到 1000 之间");
        }
        std::string rest;
        std::getline(std::cin, rest);
        /* BEGIN 2 */
        // 1) 读 m 行，用 splitTokens 切开，逐条校验命令名和参数个数；
        // 2) 全部合法之后再逐条执行，get 找不到输出 (none)。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
