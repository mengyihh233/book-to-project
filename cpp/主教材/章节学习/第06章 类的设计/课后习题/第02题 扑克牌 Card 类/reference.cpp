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
