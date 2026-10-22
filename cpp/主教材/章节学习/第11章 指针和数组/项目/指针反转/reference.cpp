// 参考实现：指针反转
// 用两个指针从两端向中间交换，全程不用下标运算符。
#include <iostream>

namespace {

void reverseInPlace(int* first, int* last) {   // [first, last)
    while (first < last) {
        --last;
        if (first >= last) break;
        const int t = *first;
        *first = *last;
        *last = t;
        ++first;
    }
}

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    int* data = new int[static_cast<std::size_t>(n)];
    for (int* p = data; p < data + n; ++p) {
        if (!(std::cin >> *p)) {
            std::cerr << "数据不足 " << n << " 个\n";
            delete[] data;
            return 2;
        }
    }
    reverseInPlace(data, data + n);
    for (int* p = data; p < data + n; ++p) {
        if (p != data) std::cout << ' ';
        std::cout << *p;
    }
    std::cout << '\n';
    delete[] data;
    return 0;
}
