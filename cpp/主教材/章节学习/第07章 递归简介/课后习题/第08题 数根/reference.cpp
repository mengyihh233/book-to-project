#include <iostream>
#include <stdexcept>

int digitalRoot(long long x) {
    /* BEGIN 1 */
        if (x < 10) return static_cast<int>(x);
    long long sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return digitalRoot(sum);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("个数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
                for (int i = 0; i < n; ++i) {
            long long v = 0;
            if (!(std::cin >> v) || v < 0) throw std::invalid_argument("每行一个非负整数");
            std::cout << digitalRoot(v) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
