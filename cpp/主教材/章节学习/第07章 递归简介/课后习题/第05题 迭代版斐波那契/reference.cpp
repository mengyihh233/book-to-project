#include <iostream>
#include <stdexcept>

long long fib(int n) {
    /* BEGIN 1 */
        if (n < 2) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        const long long c = a + b;
        a = b;
        b = c;
    }
    return b;
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 90) {
            throw std::invalid_argument("n 必须在 0 到 90 之间");
        }
        /* BEGIN 2 */
                std::cout << fib(n) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
