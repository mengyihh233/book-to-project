#include "combinatorics.h"
#include <iostream>
#include <stdexcept>
using combinatorics::combinations;
using combinatorics::permutations;
void check(bool ok) { if (!ok) throw std::runtime_error("contract test failed"); }
template<class F> void rejects(F f) {
    bool rejected = false;
    try { f(); } catch (const std::invalid_argument&) { rejected = true; }
    catch (const std::overflow_error&) { rejected = true; }
    check(rejected);
}
int main() {
    try {
        check(permutations(52, 2) == 2652);
        check(combinations(52, 2) == 1326);
        check(combinations(66, 33) == 7219428434016265740LL);
        for (int n = 0; n <= 20; ++n) {
            check(combinations(n, 0) == 1);
            check(combinations(n, n) == 1);
            for (int k = 0; k <= n; ++k) {
                check(combinations(n, k) == combinations(n, n-k));
                if (k > 0 && k < n) {
                    check(combinations(n, k) == combinations(n-1, k-1) + combinations(n-1, k));
                }
            }
        }
        rejects([] { combinations(5, 6); });
        rejects([] { permutations(-1, 0); });
        rejects([] { permutations(21, 21); });
        rejects([] { combinations(67, 33); });
        std::cout << "PASS: combinatorics contracts, symmetry, Pascal identity, overflow\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
