# 第17章 · 习题3：素数集合 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 判断 N 是否为素数时，除数只需要试到 `d * d <= N`——再大就一定配成对出现过。
- 除数从**已找到的素数集合**里取，比用 2、3、4、5… 一个个试快得多。
- `d * d` 用 `long long` 算，别在 int 上溢出。

## 容易错的边界

- 2 本身是素数，循环的下界别从 3 开始。
- `max = 2` 也要输出 `{2}`，不是空集合。
- 把「没找到除数」直接当素数之前，要确认循环是被 sqrt 条件停下的，而不是被 `break` 停下的。

## 参考实现

```cpp
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
```
