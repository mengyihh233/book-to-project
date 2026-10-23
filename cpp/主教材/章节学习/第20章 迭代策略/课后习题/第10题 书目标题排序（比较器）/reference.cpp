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
    std::string text;
    for (char ch : title) {
        const unsigned char code = static_cast<unsigned char>(ch);
        if (std::isalnum(code)) {
            text += static_cast<char>(std::tolower(code));
        } else if (ch == ' ') {
            text += ' ';
        }
    }
    
    // 合并连续空格，去掉首尾空格
    std::string cleaned;
    for (char ch : text) {
        if (ch == ' ' && (cleaned.empty() || cleaned.back() == ' ')) continue;
        cleaned += ch;
    }
    while (!cleaned.empty() && cleaned.back() == ' ') cleaned.pop_back();
    
    // 只去掉一个开头的冠词，且必须是整词（前缀带空格）
    for (const std::string article : {"the ", "an ", "a "}) {
        if (cleaned.compare(0, article.size(), article) == 0) {
            cleaned = cleaned.substr(article.size());
            break;
        }
    }
    return cleaned;
    /* END 1 */
}

// 先比 normalize 的结果；完全相同再比原串（保证顺序唯一）。
bool titleComesBefore(const std::string& a, const std::string& b) {
    /* BEGIN 2 */
    const std::string left = normalize(a);
    const std::string right = normalize(b);
    if (left != right) return left < right;
    return a < b;   // 规范化后相同：按原串定序，保证顺序唯一
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
