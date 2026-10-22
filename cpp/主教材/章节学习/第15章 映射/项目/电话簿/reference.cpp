// 参考实现：电话簿
// 用 map 存「名字 → 号码」，按查询顺序输出；重名时后者覆盖前者。
#include <iostream>
#include <map>
#include <string>

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    std::map<std::string, std::string> book;
    for (int i = 0; i < n; ++i) {
        std::string name, number;
        if (!(std::cin >> name >> number)) {
            std::cerr << "第 " << i + 1 << " 条记录不完整\n";
            return 2;
        }
        for (char c : number) {
            if (c < '0' || c > '9') {
                std::cerr << "号码必须是数字：" << number << "\n";
                return 2;
            }
        }
        book[name] = number;      // 重名直接覆盖，符合“最后登记的有效”
    }
    int m = 0;
    if (!(std::cin >> m) || m < 0 || m > 100000) {
        std::cerr << "查询次数不合法\n";
        return 2;
    }
    for (int i = 0; i < m; ++i) {
        std::string name;
        if (!(std::cin >> name)) {
            std::cerr << "查询条数不足\n";
            return 2;
        }
        const auto it = book.find(name);
        std::cout << (it == book.end() ? "未找到" : it->second) << "\n";
    }
    return 0;
}
