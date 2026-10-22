// 【本题说明开始】
// 第5章 · 习题6：埃拉托色尼筛法生成素数
//
// 题目：矩阵行列与图像坐标实操。tests.cpp检查参考接口，不会完成个人work。输出空白保留，不额外打印输入提示到stdout。
// 实现什么：std::vector<int> primesUpTo(int limit)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/grid_lesson.h"
#include <cstdint>

// 本题要实现的接口（声明已给出）。
std::vector<int> primesUpTo(int limit);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::string line,extra;
    try {
        if(!book_input::logicalLine(std::cin,line)||book_input::logicalLine(std::cin,extra)) throw std::invalid_argument("one limit line required");
        auto values=primesUpTo(strictNumber<int>(line));
        for(std::size_t i=0;i<values.size();++i) std::cout<<(i?" ":"")<<values[i];
        std::cout<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::vector<int> primesUpTo(int limit) {
    /* BEGIN 1：primesUpTo */
    // 提示：开一个 N+1 的标记数组，从 2 开始把倍数划掉，最后收集仍被标记的下标；0 和 1 不是素数。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
