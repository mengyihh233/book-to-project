// 参考实现：温度记录统计
// 逐行读温度，END 结束；输出个数/平均/最高/最低/极差，统一两位小数。
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    bool sawEnd = false;
    int count = 0;
    double sum = 0.0, best = 0.0, worst = 0.0;
    std::string line;

    while (std::getline(std::cin, line)) {
        // Windows 换行会在行尾留下 \r，不去掉会让 "END\r" 匹配不上
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
            line.pop_back();
        if (line == "END") {
            sawEnd = true;
            break;
        }
        if (line.empty()) continue;

        double value = 0.0;
        std::istringstream iss(line);
        std::string rest;
        // 先读一个数，再确认这行没有多余字符：否则 "12a" 会被当成 12
        if (!(iss >> value) || (iss >> rest)) {
            std::cerr << "不是合法温度：" << line << "\n";
            return 2;
        }
        if (value < -273.15) {
            std::cerr << "温度低于绝对零度：" << line << "\n";
            return 2;
        }

        if (count == 0) {
            best = worst = value;
        } else {
            if (value > best) best = value;
            if (value < worst) worst = value;
        }
        sum += value;
        ++count;
    }

    if (!sawEnd) {
        std::cerr << "缺少 END\n";
        return 2;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "个数 " << count << "\n";
    if (count == 0) return 0;
    std::cout << "平均 " << sum / count << "\n";
    std::cout << "最高 " << best << "\n";
    std::cout << "最低 " << worst << "\n";
    std::cout << "极差 " << (best - worst) << "\n";
    return 0;
}
