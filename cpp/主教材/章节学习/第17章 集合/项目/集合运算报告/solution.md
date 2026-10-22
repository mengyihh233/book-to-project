# 第17章 项目：集合运算报告 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：集合运算报告
// 用 set 自动去重排序，再求并集、交集、两个差集与子集关系。
#include <iostream>
#include <set>

void print_set(const char* label, const std::set<int>& s) {
    std::cout << label;
    for (int v : s) std::cout << ' ' << v;
    std::cout << "\n";
}

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 100000) {
        std::cerr << "集合 A 的大小不合法\n";
        return 2;
    }
    std::set<int> a;
    for (int i = 0; i < n; ++i) {
        int v = 0;
        if (!(std::cin >> v)) {
            std::cerr << "集合 A 元素不足\n";
            return 2;
        }
        a.insert(v);
    }

    int m = 0;
    if (!(std::cin >> m) || m < 0 || m > 100000) {
        std::cerr << "集合 B 的大小不合法\n";
        return 2;
    }
    std::set<int> b;
    for (int i = 0; i < m; ++i) {
        int v = 0;
        if (!(std::cin >> v)) {
            std::cerr << "集合 B 元素不足\n";
            return 2;
        }
        b.insert(v);
    }

    std::set<int> uni, inter, only_a, only_b;
    for (int v : a) {
        uni.insert(v);
        if (b.count(v)) {
            inter.insert(v);
        } else {
            only_a.insert(v);
        }
    }
    for (int v : b) {
        uni.insert(v);
        if (!a.count(v)) only_b.insert(v);
    }

    // A 是 B 的子集：A 里每个元素都在 B 中（空集算子集）。
    bool subset = true;
    for (int v : a) {
        if (!b.count(v)) {
            subset = false;
            break;
        }
    }

    print_set("并集", uni);
    print_set("交集", inter);
    print_set("仅A", only_a);
    print_set("仅B", only_b);
    std::cout << "子集 " << (subset ? "是" : "否") << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] 上面那组输入 → `并集 3 4 7 9` / `交集 9` / `仅A 3 7` / `仅B 4` / `子集 否`
- [ ] `0` + `3 / 1 2 3` → 并集 `1 2 3`，交集与仅A 只有标签，`子集 是`
- [ ] A = {1,2,2,3}，B = {3,2,1,1} → 并集与交集都是 `1 2 3`，两个差集只有标签
- [ ] 不相交的两个集合 → `交集` 只有标签
- [ ] A = {2,4,6}，B = {1,2,3,4,6} → `子集 是`
- [ ] n = -1 → 返回 2，屏幕无输出
- [ ] m = 3 但只给 2 个数 → 返回 2，屏幕无输出

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
