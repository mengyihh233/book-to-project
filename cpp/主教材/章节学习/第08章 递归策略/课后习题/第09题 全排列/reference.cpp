#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

void collectPermutations(std::string s, int start, std::set<std::string>& out) {
    /* BEGIN 1 */
        if (start == static_cast<int>(s.size())) {
        out.insert(s);
        return;
    }
    for (int i = start; i < static_cast<int>(s.size()); ++i) {
        std::swap(s[start], s[i]);
        collectPermutations(s, start + 1, out);
        std::swap(s[start], s[i]);
    }
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 5) {
            throw std::invalid_argument("行数必须在 1 到 5 之间");
        }
        std::cin.ignore();
        /* BEGIN 2 */
                for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) throw std::invalid_argument("行数不足");
            if (line.empty() || line.size() > 7) throw std::invalid_argument("每行 1 到 7 个大写字母");
            for (char ch : line) {
                if (ch < 'A' || ch > 'Z') throw std::invalid_argument("只收大写字母");
            }
            std::set<std::string> out;
            collectPermutations(line, 0, out);
            for (const auto& p : out) std::cout << p << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
