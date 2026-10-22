# 第15章 项目：电话簿 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
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
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] 3 条记录 + 查 `alice` / `dave` → `123` / `未找到`
- [ ] 2 条记录 + `m=0` → **无输出**，返回 0
- [ ] 重名 `tom 111` 后 `tom 222`，查 `tom` → `222`
- [ ] 查 `zed` 和 `ZED` → 前一个命中，后一个 `未找到`
- [ ] `n=0` → 返回 2
- [ ] `m=100001` → 返回 2
- [ ] 号码 `12x` → 返回 2

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
