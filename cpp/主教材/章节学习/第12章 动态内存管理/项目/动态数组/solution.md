# 第12章 项目：动态数组 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：动态数组
// 手写一个只在尾部追加的数组：满时容量翻倍，记录扩容次数。
#include <iostream>

namespace {

class DynArray {
public:
    DynArray() : data_(new int[1]), size_(0), capacity_(1), grows_(0) {}
    ~DynArray() { delete[] data_; }

    DynArray(const DynArray&) = delete;
    DynArray& operator=(const DynArray&) = delete;

    void push(int value) {
        if (size_ == capacity_) grow();
        data_[size_++] = value;
    }

    int size() const { return size_; }
    int grows() const { return grows_; }
    int at(int index) const { return data_[index]; }

private:
    void grow() {
        const int next = capacity_ * 2;
        int* fresh = new int[static_cast<std::size_t>(next)];
        for (int i = 0; i < size_; ++i) fresh[i] = data_[i];
        delete[] data_;
        data_ = fresh;
        capacity_ = next;
        ++grows_;
    }

    int* data_;
    int size_;
    int capacity_;
    int grows_;
};

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    DynArray array;
    long long sum = 0;
    int best = 0;
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) {
            std::cerr << "数据不足 " << n << " 个\n";
            return 2;
        }
        if (i == 0 || value > best) best = value;
        sum += value;
        array.push(value);
    }
    std::cout << "个数 " << array.size() << "\n";
    std::cout << "总和 " << sum << "\n";
    std::cout << "最大 " << best << "\n";
    std::cout << "扩容 " << array.grows() << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `5` + `1 2 3 4 5` → 个数 5，总和 15，最大 5，扩容 **3**
- [ ] `1` + `7` → 个数 1，总和 7，最大 7，扩容 **0**
- [ ] `2` + `3 1` → 最大 3，扩容 **1**
- [ ] `8` + 1..8 → 扩容 **3**（8 正好装满，不再扩容）
- [ ] `9` + 1..9 → 扩容 **4**
- [ ] `0` → 返回 2
- [ ] `3` + 只有两个数 → 返回 2

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
