# 第4章 项目：日志分级统计 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
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
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] 三条各一个 → 前三行各 1，第四行是第一条 ERROR 的消息
- [ ] 两条 ERROR → 第四行只取**第一条**
- [ ] 没有 ERROR → 只输出三行，没有第四行
- [ ] `INFO` 后面没有消息 → `INFO` 计数 +1，不报错
- [ ] 完全空输入 → 返回 2，`stdout` 为空
- [ ] 出现 `DEBUG` → 返回 2
- [ ] 消息含空格（`ERROR 连不上 数据库 3306`）→ 第四行完整保留

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
