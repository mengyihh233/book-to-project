#include <iostream>
#include <stdexcept>

long long power(long long base, int exp) {
    /* BEGIN 1 */
        if (exp == 0) return 1;
    return base * power(base, exp - 1);
    /* END 1 */
}

int main() {
    try {
        long long base = 0;
        int exp = 0;
        if (!(std::cin >> base >> exp) || base < -10 || base > 10 || exp < 0 || exp > 18) {
            throw std::invalid_argument("底数要在 -10..10，指数要在 0..18");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                std::cout << power(base, exp) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
