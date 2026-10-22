# 第6章 · 习题7：编号生成器 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 「同一前缀连续编号」要靠状态：把下一个编号存在 `map<string,int>` 里，别用局部变量。
- `counters_[prefix]` 会在键不存在时插入 0，正好是「第一次从 0 开始」。
- 先输出再加一：`return prefix + std::to_string(counter++)`。

## 容易错的边界

- 不同前缀不能共用计数器，`Figure` 和 `P` 要各自从 0 开始。
- 同一个前缀分两行出现时要接着数，第二行不能又从 0 开始。
- 个数为 0 判非法（题目要求 1—1000），不要当成「什么都不输出」放过去。

## 参考实现

```cpp
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <stdexcept>
#include <string>

class LabelGenerator {
public:
    std::string next(const std::string& prefix) {
        int& counter = counters_[prefix];
        return prefix + std::to_string(counter++);
    }

private:
    std::map<std::string, int> counters_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 100) {
            throw std::invalid_argument("行数必须在 1 到 100 之间");
        }
        std::vector<std::pair<std::string, int>> requests;
        for (int i = 0; i < n; ++i) {
            std::string prefix;
            int count = 0;
            if (!(std::cin >> prefix >> count)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行不完整");
            }
            if (prefix.empty() || prefix.size() > 20) {
                throw std::invalid_argument("前缀长度必须在 1 到 20 之间");
            }
            if (count < 1 || count > 1000) {
                throw std::invalid_argument("每行个数必须在 1 到 1000 之间");
            }
            requests.emplace_back(prefix, count);
        }

        LabelGenerator generator;
        for (const auto& request : requests) {
            for (int k = 0; k < request.second; ++k) {
                std::cout << generator.next(request.first) << '\n';
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
