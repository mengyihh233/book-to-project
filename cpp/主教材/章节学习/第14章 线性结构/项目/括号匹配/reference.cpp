// 参考实现：括号匹配
// 用栈检查三种括号是否配对，同时记录最大嵌套深度。
#include <iostream>
#include <string>

namespace {

char matchOf(char open) {
    if (open == '(') return ')';
    if (open == '[') return ']';
    return '}';
}

bool isOpen(char c) { return c == '(' || c == '[' || c == '{'; }
bool isClose(char c) { return c == ')' || c == ']' || c == '}'; }

}  // namespace

int main() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cerr << "缺少输入\n";
        return 2;
    }
    if (!line.empty() && line.back() == '\r') line.pop_back();

    std::string stack;          // 用 string 当栈，push_back / pop_back
    int depth = 0;
    for (char c : line) {
        if (c == ' ' || c == '\t') continue;
        if (isOpen(c)) {
            stack.push_back(c);
            if (static_cast<int>(stack.size()) > depth) depth = static_cast<int>(stack.size());
        } else if (isClose(c)) {
            if (stack.empty() || matchOf(stack.back()) != c) {
                std::cout << "匹配 否\n深度 0\n";
                return 0;
            }
            stack.pop_back();
        } else {
            std::cerr << "出现非法字符：" << c << "\n";
            return 2;
        }
    }
    if (!stack.empty()) {
        std::cout << "匹配 否\n深度 0\n";
        return 0;
    }
    std::cout << "匹配 是\n深度 " << depth << "\n";
    return 0;
}
