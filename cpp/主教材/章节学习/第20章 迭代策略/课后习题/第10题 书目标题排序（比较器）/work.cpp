// 【本题说明开始】
// 第20章 · 习题10：书目标题排序（比较器）
//
// 题目：给 `std::sort` 写一个比较器：忽略大小写、忽略除空格外的标点、忽略开头的 a / an / the。
// 实现什么：`normalize()` 的清洗 + `titleComesBefore()` 的两级比较。
// 写在哪里：只补下方 BEGIN 1（规范化标题）与 BEGIN 2（两级比较）之间的代码。
// 文本格式：按规则排序后的原始标题，一行一条；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string normalize(const std::string& title);
bool titleComesBefore(const std::string& a, const std::string& b);

// 转小写、只留字母数字和空格、合并空格、去掉开头的 a / an / the。
std::string normalize(const std::string& title) {
    /* BEGIN 1 */
    // @@1@@
    /* END 1 */
}

// 先比 normalize 的结果；完全相同再比原串（保证顺序唯一）。
bool titleComesBefore(const std::string& a, const std::string& b) {
    /* BEGIN 2 */
    // @@2@@
    /* END 2 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("标题个数必须在 1 到 1000 之间");
        }
        std::string rest;
        std::getline(std::cin, rest);

        std::vector<std::string> titles;
        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) throw std::invalid_argument("标题行数不足");

            std::size_t head = 0;
            while (head < line.size() && std::isspace(static_cast<unsigned char>(line[head]))) ++head;
            std::size_t tail = line.size();
            while (tail > head && std::isspace(static_cast<unsigned char>(line[tail - 1]))) --tail;
            line = line.substr(head, tail - head);

            if (line.empty()) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 条标题是空的");
            if (line.size() > 100) throw std::invalid_argument("标题超过 100 个字符：" + line);
            titles.push_back(line);
        }

        std::sort(titles.begin(), titles.end(), titleComesBefore);
        for (const std::string& title : titles) std::cout << title << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
