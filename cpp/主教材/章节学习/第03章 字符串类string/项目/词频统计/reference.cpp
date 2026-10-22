// 参考实现：词频统计
// 第 1 行是停用词（空格分隔，可为空行），其后全部是正文。
// 输出词频最高的前 10 个词，每行「词 次数」；频次相同按字典序升序。
#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::string stopLine;
    if (!std::getline(std::cin, stopLine)) {
        std::cerr << "缺少停用词行\n";
        return 2;
    }

    std::set<std::string> stop;
    std::string token;
    for (char ch : stopLine) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            token += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else if (!token.empty()) {
            stop.insert(token);
            token.clear();
        }
    }
    if (!token.empty()) stop.insert(token);

    std::vector<std::pair<std::string, int>> counts;
    auto bump = [&counts](const std::string& word) {
        for (auto& item : counts) {
            if (item.first == word) {
                item.second += 1;
                return;
            }
        }
        counts.emplace_back(word, 1);
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        std::string word;
        for (char ch : line) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            } else if (!word.empty()) {
                if (!stop.count(word)) bump(word);
                word.clear();
            }
        }
        if (!word.empty()) {
            if (!stop.count(word)) bump(word);
        }
    }

    std::sort(counts.begin(), counts.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    if (counts.size() > 10) counts.resize(10);
    for (const auto& item : counts) {
        std::cout << item.first << ' ' << item.second << '\n';
    }
    return 0;
}
