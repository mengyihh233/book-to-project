# 第6章 · 习题2：扑克牌 Card 类 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 先把最后一个字符当花色、前面当等级拆开，再分别校验——顺序反了会越界。
- `10` 占两个字符，别按「等级只有一个字符」硬写。
- 大小写用 `std::toupper` 统一处理，别只认大写输入。

## 容易错的边界

- `1S` 不合法（1 点写作 `A`），`11H` 也不合法（11 写作 `J`）。
- `AX` 是花色非法，要在构造时就报错，不能默认成 CLUBS。
- 短串长度小于 2 时直接判非法，否则 `shortName.back()` 取不到字符。

## 参考实现

```cpp
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

inline const char* suitName(int suit) {
    static const char* names[4] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    return names[suit];
}

class Card {
public:
    Card() : rank_(1), suit_(0) {}

    Card(const std::string& shortName) : rank_(1), suit_(0) {
        if (shortName.size() < 2) {
            throw std::invalid_argument("牌面太短：" + shortName);
        }
        const char suitChar = static_cast<char>(
            std::toupper(static_cast<unsigned char>(shortName.back())));
        const int suit = std::string("CDHS").find(suitChar);
        if (suit == std::string::npos) {
            throw std::invalid_argument("花色只能是 C/D/H/S：" + shortName);
        }

        std::string rankText = shortName.substr(0, shortName.size() - 1);
        for (char& ch : rankText) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));

        int rank = 0;
        if (rankText == "A") rank = 1;
        else if (rankText == "J") rank = 11;
        else if (rankText == "Q") rank = 12;
        else if (rankText == "K") rank = 13;
        else if (rankText == "10") rank = 10;
        else if (rankText.size() == 1 && rankText[0] >= '2' && rankText[0] <= '9') {
            rank = rankText[0] - '0';
        } else {
            throw std::invalid_argument("等级只能是 A、2..10、J、Q、K：" + shortName);
        }

        rank_ = rank;
        suit_ = suit;
    }

    int rank() const { return rank_; }
    int suit() const { return suit_; }

    std::string toString() const {
        static const char* ranks[14] = {"",    "A", "2", "3", "4", "5", "6", "7",
                                        "8", "9", "10", "J", "Q", "K"};
        static const char suits[5] = "CDHS";
        return std::string(ranks[rank_]) + suits[suit_];
    }

private:
    int rank_;
    int suit_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 52) {
            throw std::invalid_argument("牌数必须在 1 到 52 之间");
        }
        for (int i = 0; i < n; ++i) {
            std::string text;
            if (!(std::cin >> text)) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 张牌读不到");
            }
            Card card(text);
            std::cout << card.toString() << ' ' << card.rank() << ' '
                      << suitName(card.suit()) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
