#include <iostream>
#include <stdexcept>

long long calls = 0;

long long fibCounted(int n) {
    /* BEGIN 1 */
        ++calls;
    if (n < 2) return n;
    return fibCounted(n - 1) + fibCounted(n - 2);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 24) {
            throw std::invalid_argument("n 必须在 0 到 24 之间");
        }
        /* BEGIN 2 */
                const long long value = fibCounted(n);
        std::cout << "n=" << n << " fib=" << value << " calls=" << calls << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
