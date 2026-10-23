#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 查找表：字符 -> 数值。只认 I V X L C D M（进来之前已统一成大写）。
int romanToDecimal(const std::string& str) {
    /* BEGIN 1 */
    static const std::string kLetters = "IVXLCDM";
    static const int kValues[] = {1, 5, 10, 50, 100, 500, 1000};
    
    std::vector<int> digits;
    for (char ch : str) {
        const std::size_t where = kLetters.find(ch);
        if (where == std::string::npos) {
            throw std::invalid_argument(std::string("不是罗马数字字符：") + ch);
        }
        digits.push_back(kValues[where]);
    }
    
    int total = 0;
    for (std::size_t i = 0; i < digits.size(); ++i) {
        if (i + 1 < digits.size() && digits[i] < digits[i + 1]) {
            total -= digits[i];
        } else {
            total += digits[i];
        }
    }
    return total;
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("行数必须在 1 到 1000 之间");
        }
        std::string rest;
        std::getline(std::cin, rest);
        /* BEGIN 2 */
        // 先读完 n 行、逐行转成数值并校验（1..3999），全部通过之后再逐行输出。
        std::vector<int> values;
        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行缺失");
            }
            std::size_t first = 0;
            while (first < line.size() && std::isspace(static_cast<unsigned char>(line[first]))) ++first;
            std::size_t last = line.size();
            while (last > first && std::isspace(static_cast<unsigned char>(line[last - 1]))) --last;
            line = line.substr(first, last - first);
            if (line.empty()) throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行是空的");
            for (char& ch : line) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            const int value = romanToDecimal(line);
            if (value < 1 || value > 3999) {
                throw std::invalid_argument("数值必须在 1 到 3999 之间");
            }
            values.push_back(value);
        }
        for (int value : values) std::cout << value << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
