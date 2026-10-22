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
