// 【本题说明开始】
// 第6章 · 习题2：扑克牌 Card 类
//
// 题目：读入 n 张扑克牌（短串如 `10S`、`JD`、`ac`），输出规范短串、等级数值与花色全名。
// 实现什么：`Card` 的短串构造函数（拆等级与花色、大小写归一、非法即抛）+ `main` 的读入输出。
// 写在哪里：只补下方 BEGIN 1（Card 的短串构造函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每张一行「短串 等级 花色名」；非法牌返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

// 花色编号：0=CLUBS 1=DIAMONDS 2=HEARTS 3=SPADES
inline const char* suitName(int suit) {
    static const char* names[4] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    return names[suit];
}

class Card {
public:
    Card() : rank_(1), suit_(0) {}

    // shortName 形如 "AC"、"10s"、"jd"：前面是等级，最后一个字符是花色。
    Card(const std::string& shortName) : rank_(1), suit_(0) {
        /* BEGIN 1 */
        // 1) 长度小于 2 直接抛 std::invalid_argument；
        // 2) 最后一个字符是花色（C/D/H/S，大小写都收），前面是等级
        //    （A、2..10、J、Q、K，大小写都收）；
        // 3) 等级写进 rank_（A=1，J=11，Q=12，K=13），花色写进 suit_（0..3）。
        throw std::logic_error("补全区尚未完成");
        /* END 1 */
    }

    int rank() const { return rank_; }
    int suit() const { return suit_; }

    // 规范短串：等级用 A/2..10/J/Q/K，花色用大写字母。
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

        /* BEGIN 2 */
        // 读 n 张牌（每行一个短串），构造 Card 并逐张输出：
        // 「规范短串 等级 花色名」，例如 10S 10 SPADES。
        // 读不全就抛 std::invalid_argument。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
