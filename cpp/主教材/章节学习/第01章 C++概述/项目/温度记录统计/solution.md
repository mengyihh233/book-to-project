# 第1章 项目：温度记录统计 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
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
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `20` / `21.5` / `19` / `END` → 个数 3，平均 20.17，最高 21.50，最低 19.00，极差 2.50
- [ ] 只有一个 `END` → 只输出 `个数 0`，返回 0
- [ ] `-40` / `0` / `100` / `END` → 最低 -40.00，极差 140.00
- [ ] 某行写 `abc` → 返回 2，`stdout` 为空
- [ ] 某行写 `-300` → 返回 2
- [ ] 输入没有 `END` → 返回 2
- [ ] 小数位数固定两位：`20` 要输出成 `20.00`，不是 `20`

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
