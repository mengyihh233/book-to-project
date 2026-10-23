#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 数字 -> 字母表（不是数字就返回空串）。
inline const char* keypad(char digit) {
    switch (digit) {
        case '2': return "ABC";
        case '3': return "DEF";
        case '4': return "GHI";
        case '5': return "JKL";
        case '6': return "MNO";
        case '7': return "PQRS";
        case '8': return "TUV";
        case '9': return "WXYZ";
        default: return "";
    }
}

void collectMnemonics(const std::string& digits, std::size_t index,
                      std::string& current, std::vector<std::string>& out) {
    /* BEGIN 1 */
        if (index == digits.size()) {
        out.push_back(current);
        return;
    }
    for (const char* p = keypad(digits[index]); *p; ++p) {
        current.push_back(*p);
        collectMnemonics(digits, index + 1, current, out);
        current.pop_back();
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
            if (line.empty() || line.size() > 6) throw std::invalid_argument("每行 1 到 6 个数字");
            for (char ch : line) {
                if (ch < '2' || ch > '9') throw std::invalid_argument("只收 2 到 9 的数字");
            }
            std::vector<std::string> out;
            std::string current;
            collectMnemonics(line, 0, current, out);
            std::sort(out.begin(), out.end());
            for (const auto& item : out) std::cout << item << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
