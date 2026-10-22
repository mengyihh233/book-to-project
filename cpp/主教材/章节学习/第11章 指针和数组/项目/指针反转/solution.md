# 第11章 项目：指针反转 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：指针反转
// 用两个指针从两端向中间交换，全程不用下标运算符。
#include <iostream>

namespace {

void reverseInPlace(int* first, int* last) {   // [first, last)
    while (first < last) {
        --last;
        if (first >= last) break;
        const int t = *first;
        *first = *last;
        *last = t;
        ++first;
    }
}

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    int* data = new int[static_cast<std::size_t>(n)];
    for (int* p = data; p < data + n; ++p) {
        if (!(std::cin >> *p)) {
            std::cerr << "数据不足 " << n << " 个\n";
            delete[] data;
            return 2;
        }
    }
    reverseInPlace(data, data + n);
    for (int* p = data; p < data + n; ++p) {
        if (p != data) std::cout << ' ';
        std::cout << *p;
    }
    std::cout << '\n';
    delete[] data;
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `5` + `1 2 3 4 5` → `5 4 3 2 1`
- [ ] `1` + `7` → `7`
- [ ] `4` + `-1 0 1 2` → `2 1 0 -1`
- [ ] `6` + `1 1 2 2 3 3` → `3 3 2 2 1 1`
- [ ] `2` + `10 -10` → `-10 10`
- [ ] `0` → 返回 2
- [ ] `3` + 只有两个数 → 返回 2
- [ ] 输出是 `5 4 3 2 1`，**末尾没有多余空格**

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
