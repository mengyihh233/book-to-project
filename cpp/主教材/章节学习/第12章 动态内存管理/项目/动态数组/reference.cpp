// 参考实现：动态数组
// 手写一个只在尾部追加的数组：满时容量翻倍，记录扩容次数。
#include <iostream>

namespace {

class DynArray {
public:
    DynArray() : data_(new int[1]), size_(0), capacity_(1), grows_(0) {}
    ~DynArray() { delete[] data_; }

    DynArray(const DynArray&) = delete;
    DynArray& operator=(const DynArray&) = delete;

    void push(int value) {
        if (size_ == capacity_) grow();
        data_[size_++] = value;
    }

    int size() const { return size_; }
    int grows() const { return grows_; }
    int at(int index) const { return data_[index]; }

private:
    void grow() {
        const int next = capacity_ * 2;
        int* fresh = new int[static_cast<std::size_t>(next)];
        for (int i = 0; i < size_; ++i) fresh[i] = data_[i];
        delete[] data_;
        data_ = fresh;
        capacity_ = next;
        ++grows_;
    }

    int* data_;
    int size_;
    int capacity_;
    int grows_;
};

}  // namespace

int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 1 || n > 100000) {
        std::cerr << "n 必须在 1 到 100000 之间\n";
        return 2;
    }
    DynArray array;
    long long sum = 0;
    int best = 0;
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) {
            std::cerr << "数据不足 " << n << " 个\n";
            return 2;
        }
        if (i == 0 || value > best) best = value;
        sum += value;
        array.push(value);
    }
    std::cout << "个数 " << array.size() << "\n";
    std::cout << "总和 " << sum << "\n";
    std::cout << "最大 " << best << "\n";
    std::cout << "扩容 " << array.grows() << "\n";
    return 0;
}
