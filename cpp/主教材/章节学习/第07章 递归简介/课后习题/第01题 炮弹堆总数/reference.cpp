#include <iostream>
#include <stdexcept>

// 金字塔高度 n 的炮弹总数：1*1 + 2*2 + ... + n*n
long long cannonball(int n) {
    /* BEGIN 1 */
        if (n == 1) return 1;
    return static_cast<long long>(n) * n + cannonball(n - 1);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("高度必须在 1 到 1000 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                std::cout << cannonball(n) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
