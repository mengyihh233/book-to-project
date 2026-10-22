// 【本题说明开始】
// 第2章习题15：连续三次正面
//
// 题目：输入 seed。逐行输出HEADS/TAILS，第一次连续3次正面时停止，最后输出TOTAL与次数。以引擎值小于2^31为正面；种子、英文输出和1000000次保护上限为教学约定。
// 实现什么：int tossUntilThreeHeads(std::mt19937& engine)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "random_tools.h"

int tossUntilThreeHeads(std::mt19937& engine) {
    /* BEGIN 1：模拟抛硬币，首次连续三次正面时停止 */
    // 用两个计数：flips记录总次数，streak记录“当前连续正面数”。
    // 每次调用一次halfEvent(engine)，true输出HEADS，false输出TAILS，各占一行。
    // 反面会打断连续记录；停止后返回总次数。最多1000000次，达到仍未结束则抛异常。
    // 本函数输出逐次结果；最后一行TOTAL由main输出，不要重复输出。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// 给定：种子读取、输入校验、随机引擎和最终TOTAL行。
int main() {
    try {
        const auto seed = readUnsigned(4294967295ULL);
        requireEnd();
        std::mt19937 engine(seed);
        const int flips = tossUntilThreeHeads(engine);
        std::cout << "TOTAL " << flips << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
