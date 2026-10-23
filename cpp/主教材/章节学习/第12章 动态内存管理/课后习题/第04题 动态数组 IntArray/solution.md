# 第12章 · 习题4：动态数组 IntArray · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 三件套（析构、拷贝构造、拷贝赋值）少一个就会二次释放或浅拷贝。
- `resize` 保留 `min(旧长度, 新长度)` 个元素，新增的位置填 0。
- 越界是 `throw std::out_of_range`，由 `main` 的 try/catch 转成退出码 2。

## 容易错的边界

- 拷贝赋值要处理自赋值（`a = a`），先判 `this != &other`。
- `delete[]` 与 `new[]` 必须配对，别写成 `delete`。
- `deepcopy` 输出的是**原数组**的和，浅拷贝会把它改成 99 + 其余元素。

## 参考实现

```cpp
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

class IntArray {
public:
    explicit IntArray(int size);
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);
    ~IntArray();

    int size() const { return size_; }
    int get(int index) const;
    void set(int index, int value);
    void resize(int newSize);
    long long sum() const;

private:
    int* data_;
    int size_;
};

/* BEGIN 1 */
// 这里放上面 7 个成员函数的实现（构造、拷贝构造、拷贝赋值、析构、get、set、resize、sum）。
IntArray::IntArray(int size) : data_(nullptr), size_(size) {
    if (size < 1) throw std::invalid_argument("长度必须大于 0");
    data_ = new int[static_cast<std::size_t>(size)]();
}

IntArray::IntArray(const IntArray& other) : data_(nullptr), size_(other.size_) {
    data_ = new int[static_cast<std::size_t>(size_)];
    std::copy(other.data_, other.data_ + size_, data_);
}

IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        int* fresh = new int[static_cast<std::size_t>(other.size_)];
        std::copy(other.data_, other.data_ + other.size_, fresh);
        delete[] data_;
        data_ = fresh;
        size_ = other.size_;
    }
    return *this;
}

IntArray::~IntArray() { delete[] data_; }

int IntArray::get(int index) const {
    if (index < 0 || index >= size_) throw std::out_of_range("下标越界");
    return data_[index];
}

void IntArray::set(int index, int value) {
    if (index < 0 || index >= size_) throw std::out_of_range("下标越界");
    data_[index] = value;
}

void IntArray::resize(int newSize) {
    if (newSize < 1) throw std::invalid_argument("长度必须大于 0");
    int* fresh = new int[static_cast<std::size_t>(newSize)]();
    std::copy(data_, data_ + std::min(size_, newSize), fresh);
    delete[] data_;
    data_ = fresh;
    size_ = newSize;
}

long long IntArray::sum() const {
    long long total = 0;
    for (int i = 0; i < size_; ++i) total += data_[i];
    return total;
}
/* END 1 */

int main() {
    try {
        int commands = 0;
        if (!(std::cin >> commands) || commands < 0 || commands > 100) {
            throw std::invalid_argument("命令条数必须在 0 到 100 之间");
        }
        int size = 0;
        if (!(std::cin >> size) || size < 1 || size > 1000) {
            throw std::invalid_argument("数组长度必须在 1 到 1000 之间");
        }
        IntArray array(size);

        /* BEGIN 2 */
        // 读 commands 条命令并执行：
        // set i v / get i / size / sum / resize k / deepcopy
        // get、size、sum、deepcopy 要输出；未知命令抛 invalid_argument。
        for (int k = 0; k < commands; ++k) {
            std::string command;
            if (!(std::cin >> command)) throw std::invalid_argument("命令不完整");
            if (command == "set") {
                int index = 0, value = 0;
                if (!(std::cin >> index >> value)) throw std::invalid_argument("set 缺少参数");
                array.set(index, value);
            } else if (command == "get") {
                int index = 0;
                if (!(std::cin >> index)) throw std::invalid_argument("get 缺少参数");
                std::cout << array.get(index) << '\n';
            } else if (command == "size") {
                std::cout << array.size() << '\n';
            } else if (command == "sum") {
                std::cout << array.sum() << '\n';
            } else if (command == "resize") {
                int newSize = 0;
                if (!(std::cin >> newSize)) throw std::invalid_argument("resize 缺少参数");
                array.resize(newSize);
            } else if (command == "deepcopy") {
                IntArray copy(array);
                if (copy.size() > 0) copy.set(0, 99);
                std::cout << array.sum() << '\n';
            } else {
                throw std::invalid_argument("未知命令：" + command);
            }
        }
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
