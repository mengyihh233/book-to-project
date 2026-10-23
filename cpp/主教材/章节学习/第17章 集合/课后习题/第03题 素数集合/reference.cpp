#include <cstddef>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

// 返回 2 到 max 之间所有素数的集合。
std::set<int> createPrimeSet(int max) {
    /* BEGIN 1 */
    std::set<int> primes;
    for (int n = 2; n <= max; ++n) {
        bool isPrime = true;
        for (int prime : primes) {
            if (static_cast<long long>(prime) * prime > n) break;
            if (n % prime == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) primes.insert(n);
    }
    return primes;
    /* END 1 */
}

int main() {
    try {
        /* BEGIN 2 */
        // 读 max（2..1000000），调用 createPrimeSet，按 `{2, 3, 5}` 的格式输出。
        int max = 0;
        if (!(std::cin >> max) || max < 2 || max > 1000000) {
            throw std::invalid_argument("max 必须在 2 到 1000000 之间");
        }
        
        const std::set<int> primes = createPrimeSet(max);
        
        std::cout << '{';
        bool first = true;
        for (int prime : primes) {
            if (!first) std::cout << ", ";
            std::cout << prime;
            first = false;
        }
        std::cout << "}\n";
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
