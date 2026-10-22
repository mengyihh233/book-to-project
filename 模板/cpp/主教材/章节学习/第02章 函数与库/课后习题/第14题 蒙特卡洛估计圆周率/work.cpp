// 【本题说明开始】
// 第2章习题14：蒙特卡洛估计圆周率
//
// 题目：输入 seed。固定10000次投点，每次独立生成[-1,1]中的x、y。输出圆内点数与估计值（4位小数）。输入种子、双列输出为教学约定。
// 实现什么：int countInCircle(int trials, std::mt19937& engine)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "random_tools.h"
#include <iomanip>

int countInCircle(int trials, std::mt19937& engine) {
    /* BEGIN 1：生成二维投点并统计单位圆内的点 */
    // 每轮先后调用两次unitReal(engine)，分别生成x、y，再用2*u-1映射到(-1,1)。
    // trials为投点次数；按 x*x + y*y < 1 判断圆内，最后返回圆内点数。
    // x、y是两次独立抽样，不能用同一次结果，也不能在循环中重新播种。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

// 给定：种子读取、投点总数、圆周率公式和4位小数输出。
int main() {
    try {
        const auto seed = readUnsigned(4294967295ULL);
        requireEnd();
        std::mt19937 engine(seed);
        constexpr int trials = 10000;
        const int inside = countInCircle(trials, engine);
        std::cout << inside << ' ' << std::fixed << std::setprecision(4)
                  << 4.0 * inside / trials << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
