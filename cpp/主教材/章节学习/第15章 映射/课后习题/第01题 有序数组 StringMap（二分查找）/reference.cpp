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
int StringMap::size() const {
    return static_cast<int>(entries_.size());
}

bool StringMap::isEmpty() const {
    return entries_.empty();
}

int StringMap::findKey(const std::string& key) const {
    int low = 0;
    int high = static_cast<int>(entries_.size()) - 1;
    while (low <= high) {
        const int mid = low + (high - low) / 2;
        const std::string& here = entries_[static_cast<std::size_t>(mid)].first;
        if (here == key) return mid;
        if (here < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

bool StringMap::containsKey(const std::string& key) const {
    return findKey(key) >= 0;
}

std::string StringMap::get(const std::string& key) const {
    const int index = findKey(key);
    if (index < 0) return std::string();
    return entries_[static_cast<std::size_t>(index)].second;
}

void StringMap::put(const std::string& key, const std::string& value) {
    const int index = findKey(key);
    if (index >= 0) {
        entries_[static_cast<std::size_t>(index)].second = value;
        return;
    }
    std::size_t where = 0;
    while (where < entries_.size() && entries_[where].first < key) ++where;
    const auto position = entries_.begin() + static_cast<std::ptrdiff_t>(where);
    entries_.insert(position, std::make_pair(key, value));
}

void StringMap::remove(const std::string& key) {
    const int index = findKey(key);
    if (index >= 0) entries_.erase(entries_.begin() + index);
}

void StringMap::clear() {
    entries_.clear();
}

void StringMap::dump() const {
    for (const auto& entry : entries_) {
        std::cout << entry.first << '=' << entry.second << '\n';
    }
}
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
        std::vector<std::vector<std::string>> commands;
        for (int i = 0; i < m; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 条命令缺失");
            }
            std::vector<std::string> tokens = splitTokens(line);
            if (tokens.empty()) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 条命令是空的");
            const std::string& name = tokens[0];
            const int need = name == "put" ? 2
                           : (name == "get" || name == "remove" || name == "containsKey") ? 1
                           : (name == "size" || name == "isEmpty" || name == "clear" || name == "dump") ? 0
                           : -1;
            if (need < 0) throw std::invalid_argument("未知命令：" + name);
            if (static_cast<int>(tokens.size()) - 1 != need) {
                throw std::invalid_argument("命令参数个数不对：" + name);
            }
            commands.push_back(tokens);
        }
        
        StringMap map;
        for (const auto& tokens : commands) {
            const std::string& name = tokens[0];
            if (name == "put") {
                map.put(tokens[1], tokens[2]);
            } else if (name == "get") {
                std::cout << (map.containsKey(tokens[1]) ? map.get(tokens[1]) : std::string("(none)")) << '\n';
            } else if (name == "remove") {
                map.remove(tokens[1]);
            } else if (name == "containsKey") {
                std::cout << (map.containsKey(tokens[1]) ? "yes" : "no") << '\n';
            } else if (name == "size") {
                std::cout << map.size() << '\n';
            } else if (name == "isEmpty") {
                std::cout << (map.isEmpty() ? "yes" : "no") << '\n';
            } else if (name == "clear") {
                map.clear();
            } else if (name == "dump") {
                map.dump();
            }
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
