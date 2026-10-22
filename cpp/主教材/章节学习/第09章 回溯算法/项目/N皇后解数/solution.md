# 第9章 项目：N 皇后解数 · 参考实现

> **先自己写完再看。** 这份文件是给「已经交过一遍」的人对照用的：先想清楚自己卡在哪一步，再读代码。整段抄过去，这道题就白做了。

## 参考实现

```cpp
// 参考实现：N 皇后解数
// 逐行放皇后，回溯；用「已放列」和「两条对角线」剪枝。
#include <cstdlib>
#include <iostream>
#include <vector>

namespace {

class Solver {
public:
    explicit Solver(int n) : n_(n), count_(0), col_(static_cast<std::size_t>(n), 0) {}

    long long run() {
        place(0);
        return count_;
    }

private:
    void place(int row) {
        if (row == n_) {
            ++count_;
            return;
        }
        for (int col = 0; col < n_; ++col) {
            bool ok = true;
            for (int r = 0; r < row; ++r) {
                // 同列，或同一条斜线（行差等于列差）
                if (col_[r] == col || std::abs(col_[r] - col) == row - r) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;
            col_[row] = col;      // 做选择
            place(row + 1);       // 递归
            // 撤销选择：col_[row] 会被下一次覆盖，这里不需要显式清理
        }
    }

    int n_;
    long long count_;
    std::vector<int> col_;
};

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        std::cerr << "需要一个整数 n\n";
        return 2;
    }
    if (n < 1 || n > 10) {
        std::cerr << "n 必须在 1 到 10 之间\n";
        return 2;
    }
    Solver solver(n);
    std::cout << "解数 " << solver.run() << "\n";
    return 0;
}
```

## 自查清单

下面这些是 `README.md` 第 4 节的验收项，对照自己的程序逐条过一遍：

- [ ] `1` → `解数 1`
- [ ] `4` → `解数 2`
- [ ] `8` → `解数 92`
- [ ] `10` → `解数 724`
- [ ] `2` → `解数 0`（返回 0，不是 2）
- [ ] `0` → 返回 2
- [ ] `11` → 返回 2

## 还没想明白就回去看

- `README.md` 的「做完的标准」：那几道思考题答不上来，说明这题只是碰巧过了。
- `README.md` 的边界表：自动判分只覆盖 7 组输入，边界是自己要守的。
