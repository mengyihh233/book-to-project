// 参考实现：日志分级统计
// 每行以 INFO/WARN/ERROR 开头，其余是消息；按固定顺序输出三行计数，
// 有 ERROR 时再输出第一条错误的消息。
#include <iostream>
#include <string>

namespace {

bool takeLevel(const std::string& line, std::string& level, std::string& message) {
    // 不能用 cin >> level >> message：消息里有空格，会被截成第一个词
    std::size_t begin = line.find_first_not_of(" \t");
    if (begin == std::string::npos) return false;          // 空行
    std::size_t end = line.find_first_of(" \t", begin);
    if (end == std::string::npos) {
        level = line.substr(begin);
        message.clear();
        return true;
    }
    level = line.substr(begin, end - begin);
    std::size_t msg = line.find_first_not_of(" \t", end);
    message = (msg == std::string::npos) ? std::string() : line.substr(msg);
    return true;
}

}  // namespace

int main() {
    int info = 0, warn = 0, error = 0;
    bool sawError = false;
    std::string firstError;
    bool sawAnyLine = false;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        std::string level, message;
        if (!takeLevel(line, level, message)) continue;    // 空行跳过
        sawAnyLine = true;
        if (level == "INFO") {
            ++info;
        } else if (level == "WARN") {
            ++warn;
        } else if (level == "ERROR") {
            ++error;
            if (!sawError) {
                sawError = true;
                firstError = message;
            }
        } else {
            std::cerr << "未知级别：" << level << "\n";
            return 2;
        }
    }

    if (!sawAnyLine) {
        std::cerr << "输入为空\n";
        return 2;
    }

    std::cout << "INFO " << info << "\n";
    std::cout << "WARN " << warn << "\n";
    std::cout << "ERROR " << error << "\n";
    if (sawError) std::cout << "首条错误 " << firstError << "\n";
    return 0;
}
