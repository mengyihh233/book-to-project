// 【本题说明开始】
// 第6章 · 习题1：多米诺骨牌
//
// 题目：读入一组多米诺骨牌，每张写成规范形式、去重、排序，最后判断是不是完整的一套。
// 实现什么：`Domino` 的两参构造函数（校验 + 规范）+ `main` 里的读入、去重与输出。
// 写在哪里：只补下方 BEGIN 1（Domino 构造函数）与 BEGIN 2（读入、去重与输出）之间的代码。
// 文本格式：每张牌一行 `a-b`，末尾两行「不同 k 张」「完整一套 是/否」；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// 骨牌：两个点数在构造时规范成「小-大」，翻转后是同一张牌。
class Domino {
public:
    Domino() : low_(0), high_(0) {}

    Domino(int a, int b) {
        /* BEGIN 1 */
        // 1) a、b 必须在 0..6，否则抛 std::out_of_range；
        // 2) 小的存 low_，大的存 high_（翻转等价就靠这一步）。
        throw std::logic_error("补全区尚未完成");
        /* END 1 */
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

        /* BEGIN 2 */
        // 读 n 张牌（每行两个整数），构造 Domino；读不全就抛 std::invalid_argument。
        // 去重（翻转算同一张）、按 left 再 right 升序输出，每张一行。
        // 最后两行：不同 k 张 / 完整一套 是|否（0-0..6-6 共 28 张齐全才是「是」）。
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
