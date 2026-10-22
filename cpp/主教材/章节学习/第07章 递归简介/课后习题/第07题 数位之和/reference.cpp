#include <iostream>
#include <stdexcept>

long long digitSum(long long x) {
    /* BEGIN 1 */
        if (x < 10) return x;
    return x % 10 + digitSum(x / 10);
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("个数必须在 1 到 100 之间");
        }
        /* BEGIN 2 */
        // 先把 n 行全部读进来（缺行、超长都算非法），全部读完之后再逐行逆序输出，
        // 否则非法输入会吐出半份结果。
                for (int i = 0; i < n; ++i) {
            long long v = 0;
            if (!(std::cin >> v) || v < 0) throw std::invalid_argument("每行一个非负整数");
            std::cout << digitSum(v) << '\n';
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
