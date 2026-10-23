#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 模板函数：对任意能用 < 比较的类型做插入排序。
template <class T>
void sortValues(std::vector<T>& data) {
    /* BEGIN 1 */
    for (std::size_t i = 1; i < data.size(); ++i) {
        T key = data[i];
        std::size_t j = i;
        while (j > 0 && data[j - 1] > key) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = key;
    }
    /* END 1 */
}

int main() {
    try {
        std::string type;
        int n = 0;
        if (!(std::cin >> type >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("n 必须在 1 到 1000 之间");
        }
        /* BEGIN 2 */
        // 按 type 读入 int 或 string 的 n 个值，排序后空格分隔输出。
        if (type == "int") {
            std::vector<long long> values(static_cast<std::size_t>(n));
            for (int i = 0; i < n; ++i) {
                if (!(std::cin >> values[static_cast<std::size_t>(i)])) throw std::invalid_argument("整数个数不足");
            }
            sortValues(values);
            for (int i = 0; i < n; ++i) {
                if (i) std::cout << ' ';
                std::cout << values[static_cast<std::size_t>(i)];
            }
            std::cout << '\n';
        } else if (type == "string") {
            std::vector<std::string> values(static_cast<std::size_t>(n));
            for (int i = 0; i < n; ++i) {
                if (!(std::cin >> values[static_cast<std::size_t>(i)])) throw std::invalid_argument("字符串个数不足");
            }
            sortValues(values);
            for (int i = 0; i < n; ++i) {
                if (i) std::cout << ' ';
                std::cout << values[static_cast<std::size_t>(i)];
            }
            std::cout << '\n';
        } else {
            throw std::invalid_argument("type 只能是 int 或 string");
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
