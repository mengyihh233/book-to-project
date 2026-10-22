// 【本题说明开始】
// 第2章习题13：放射性衰变
//
// 题目：输入 seed。固定从10000个原子开始，每年每个尚存原子独立以50%概率衰变，输出 year remaining，包含初始第0年，直到0。初始行、种子和1000年保护上限为教学约定
//   。
// 实现什么：int survivorsAfterYear(int atoms, std::mt19937& engine)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "random_tools.h"

// 给定：种子读取、逐年循环、输出和终止保护。只补一次“过一年”的模拟。
int survivorsAfterYear(int atoms, std::mt19937& engine) {
    /* BEGIN 1：逐个原子模拟，返回本年存活数 */
    // atoms 为本年开始时的存量。每个原子恰好调用一次 halfEvent(engine)。
    // halfEvent 返回 true 表示“衰变”；统计没有衰变的原子并返回。
    // 这是逐个随机试验，不能直接返回 atoms / 2，也不能边循环边修改 atoms。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        const auto seed = readUnsigned(4294967295ULL);
        requireEnd();
        std::mt19937 engine(seed);
        int atoms = 10000;
        std::cout << "0 " << atoms << '\n';
        for (int year = 1; atoms > 0; ++year) {
            if (year > 1000) throw std::runtime_error("simulation limit reached");
            atoms = survivorsAfterYear(atoms, engine);
            std::cout << year << ' ' << atoms << '\n';
        }
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
