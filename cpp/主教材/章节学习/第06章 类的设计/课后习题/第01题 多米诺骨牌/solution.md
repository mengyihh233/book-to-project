# 第6章 · 习题1：多米诺骨牌 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 翻转等价要在**构造时**就解决：先把点数排序再存，后面所有比较都不用管方向。
- 去重和排序可以一起交给 `std::set<std::pair<int,int>>`，不要先塞 vector 再手写去重。
- `完整一套` 只要看不同牌数到没到 28：0-0 到 6-6 一共就 28 张。

## 容易错的边界

- 点数 7 或 -1 要抛异常，不能静默改成 0 或 6。
- n 张牌只给了 n-1 行时，`cin >>` 失败要报错，不能拿 0 顶替。
- 抛异常后不要再输出半份报表——`main` 的 try/catch 只保证退出码，输出顺序要自己守。

## 参考实现

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Domino {
public:
    Domino() : low_(0), high_(0) {}

    Domino(int a, int b) {
        if (a < 0 || a > 6 || b < 0 || b > 6) {
            throw std::out_of_range("点数必须在 0 到 6 之间");
        }
        low_ = a < b ? a : b;
        high_ = a < b ? b : a;
    }

    std::string toString() const {
        return std::to_string(low_) + "-" + std::to_string(high_);
    }
    int left() const { return low_; }
    int right() const { return high_; }

private:
    int low_;
    int high_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("骨牌张数必须在 1 到 1000 之间");
        }

        std::set<std::pair<int, int>> cards;
        for (int i = 0; i < n; ++i) {
            int a = 0, b = 0;
            if (!(std::cin >> a >> b)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 张牌读不全");
            }
            Domino d(a, b);
            cards.insert({d.left(), d.right()});
        }

        for (const auto& c : cards) {
            std::cout << c.first << '-' << c.second << '\n';
        }
        std::cout << "不同 " << cards.size() << " 张\n";
        std::cout << "完整一套 " << (cards.size() == 28 ? "是" : "否") << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
