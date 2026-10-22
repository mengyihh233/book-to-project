// 参考实现：汉诺塔定位
// 输入 n 与 k，输出总步数 2^n-1，以及第 k 步移动的是哪个柱到哪个柱。
// 不模拟整个过程：每层递归能直接判断第 k 步落在「搬上面 n-1 个」「搬最大的」「搬回来」哪一段。
#include <iostream>
#include <string>

namespace {

void kthStep(int n, char from, char to, char via, long long k, std::string& out) {
    if (n == 0) return;
    const long long half = (1LL << (n - 1)) - 1;   // 上面 n-1 个搬完需要的步数
    if (k <= half) {
        kthStep(n - 1, from, via, to, k, out);
    } else if (k == half + 1) {
        out = std::string(1, from) + "->" + std::string(1, to);
    } else {
        kthStep(n - 1, via, to, from, k - half - 1, out);
    }
}

}  // namespace

int main() {
    int n = 0;
    long long k = 0;
    if (!(std::cin >> n >> k)) {
        std::cerr << "需要两个整数 n 和 k\n";
        return 2;
    }
    if (n < 1 || n > 16) {
        std::cerr << "n 必须在 1 到 16 之间\n";
        return 2;
    }
    const long long total = (1LL << n) - 1;
    if (k < 1 || k > total) {
        std::cerr << "k 必须在 1 到 " << total << " 之间\n";
        return 2;
    }
    std::string step;
    kthStep(n, 'A', 'C', 'B', k, step);
    std::cout << "步数 " << total << "\n";
    std::cout << "第 " << k << " 步 " << step << "\n";
    return 0;
}
