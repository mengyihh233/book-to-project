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
