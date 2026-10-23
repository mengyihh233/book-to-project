# 第14章 · 习题2：模板排序接口 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 模板要写在头文件语境里（这里就写在 main 之前），编译器才能对用到的类型实例化。
- `template <class T>` 里的 T 用完就丢，函数体只依赖 `<` 比较，整数和 string 都能用。
- 插入排序的第二层循环写 `j > 0 && data[j-1] > key`，相等时不交换才稳定。

## 容易错的边界

- 别对 `std::string` 用 `-` 或 `>` 以外的算术语义，它只保证字典序比较。
- n=1000 的插入排序是 10⁶ 次比较，够快；但别在循环里复制整个 vector。
- 输出末尾不要多打空格。

## 参考实现

```cpp
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
```
