#include <iostream>
#include <stdexcept>
#include <vector>

void mergeSort(int* data, int left, int right, int* buffer) {
    /* BEGIN 1 */
        if (left >= right) return;
    const int mid = left + (right - left) / 2;
    mergeSort(data, left, mid, buffer);
    mergeSort(data, mid + 1, right, buffer);
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) buffer[k++] = data[i++];
        else buffer[k++] = data[j++];
    }
    while (i <= mid) buffer[k++] = data[i++];
    while (j <= right) buffer[k++] = data[j++];
    for (int t = left; t <= right; ++t) data[t] = buffer[t];
    /* END 1 */
}

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100000) {
            throw std::invalid_argument("n 必须在 1 到 100000 之间");
        }
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> data[i])) throw std::invalid_argument("数字个数不足");
        }
        /* BEGIN 2 */
                std::vector<int> buffer(n);
        mergeSort(data.data(), 0, n - 1, buffer.data());
        for (int i = 0; i < n; ++i) {
            if (i) std::cout << ' ';
            std::cout << data[i];
        }
        std::cout << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
