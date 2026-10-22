#include <iostream>
#include <stdexcept>

long long gcd(long long x, long long y) {
    /* BEGIN 1 */
        if (y == 0) return x;
    return gcd(y, x % y);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("组数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                for (int i = 0; i < n; ++i) {
            long long x = 0, y = 0;
            if (!(std::cin >> x >> y) || x < 0 || y < 0) throw std::invalid_argument("每行两个非负整数");
            std::cout << gcd(x, y) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
