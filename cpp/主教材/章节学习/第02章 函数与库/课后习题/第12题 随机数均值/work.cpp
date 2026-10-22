// 【本题说明开始】
// 第2章习题12：随机数均值
//
// 题目：输入 count seed，count 为1..1000000，seed 为0..4294967295。输出均值（10位小数）。原题让用户指定样本数量；seed、范围与输出精度为可复现
//   实验约定。
// 实现什么：double sampleMean(std::uint32_t count, std::mt19937& engine)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "random_tools.h"
#include <iomanip>

// 给定：读取 count 和 seed、校验范围、固定随机序列、按10位小数输出。
// 只补下面的函数体；不要重写 main 或修改 random_tools.h。
double sampleMean(std::uint32_t count, std::mt19937& engine) {
    /* BEGIN 1：累加随机数并计算均值 */
    // count 已保证为1..1000000。每次调用 unitReal(engine) 取得一个(0,1)样本。
    // 累加 count 次抽样，再返回平均值；累加器使用 double。
    // engine 按引用传入：每次抽样都推进同一个引擎，不能在循环里重新播种。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        const auto count = readUnsigned(1000000);
        const auto seed = readUnsigned(4294967295ULL);
        requireEnd();
        if (count == 0) throw std::invalid_argument("count must be positive");
        std::mt19937 engine(seed);
        const double mean = sampleMean(count, engine);
        std::cout << std::fixed << std::setprecision(10) << mean << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}
