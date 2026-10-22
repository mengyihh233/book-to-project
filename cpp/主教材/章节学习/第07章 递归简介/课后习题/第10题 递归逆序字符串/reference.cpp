#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string reverseOf(const std::string& s) {
    /* BEGIN 1 */
        if (s.empty()) return std::string();
    return reverseOf(s.substr(1)) + s[0];
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }
        std::cin.ignore();
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                std::vector<std::string> lines;
        for (int i = 0; i < n; ++i) {
            std::string line;
            if (!std::getline(std::cin, line)) throw std::invalid_argument("行数不足");
            if (line.size() > 1000) throw std::invalid_argument("单行超过 1000 字符");
            lines.push_back(line);
        }
        for (const auto& line : lines) std::cout << reverseOf(line) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
