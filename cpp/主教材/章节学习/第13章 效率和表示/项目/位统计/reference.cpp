// 参考实现：位统计
// 对一组非负整数统计：全部按位或、按位与、二进制中 1 的总个数、最大值的最高位位置。
#include <iostream>

namespace {

int bitCount(unsigned value) {
    int count = 0;
    while (value) {
        value &= value - 1;      // 每次消掉最低位的 1
        ++count;
    }
    return count;
}

int highestBit(unsigned value) {
    if (value == 0) return -1;   // 0 没有最高位
    int pos = 0;
    while (value >>= 1) ++pos;
    return pos;
}

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    unsigned bitsOr = 0;
    unsigned bitsAnd = 0xFFFFFFFFu;   // 与运算的单位元是全 1
    long long ones = 0;
    unsigned maxValue = 0;
    for (int i = 0; i < n; ++i) {
        long long raw = 0;
        if (!(std::cin >> raw)) {
            std::cerr << "数据不足 " << n << " 个\n";
            return 2;
        }
        if (raw < 0) {
            std::cerr << "只接受非负整数\n";
            return 2;
        }
        const unsigned value = static_cast<unsigned>(raw);
        bitsOr |= value;
        bitsAnd &= value;
        ones += bitCount(value);
        if (i == 0 || value > maxValue) maxValue = value;
    }
    std::cout << "按位或 " << bitsOr << "\n";
    std::cout << "按位与 " << bitsAnd << "\n";
    std::cout << "1的个数 " << ones << "\n";
    std::cout << "最高位 " << highestBit(maxValue) << "\n";
    return 0;
}
