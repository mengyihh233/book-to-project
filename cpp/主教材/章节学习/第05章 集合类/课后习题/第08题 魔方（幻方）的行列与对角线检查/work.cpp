// 【本题说明开始】
// 第5章 · 习题8：魔方（幻方）的行列与对角线检查
//
// 题目：第1行rows cols（各0..100），随后每行对应一个矩阵行，各列用空白分隔；任一维为0时不再有数据行。输出true/false。非空且行列数相等，并且各行、各列、两条对角线之和
//   相等时为true；不额外要求1..n²或数字互不重复。非正方形与空Grid返回false，格式错误则退出2。
// 实现什么：bool isMagicSquare(const IntGrid& grid)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/grid_lesson.h"
#include <cstdint>

// 本题要实现的接口（声明已给出）。
bool isMagicSquare(const IntGrid& grid);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto grid=readGrid(std::cin);
        std::cout<<(isMagicSquare(grid)?"true":"false")<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

bool isMagicSquare(const IntGrid& grid) {
    /* BEGIN 1：isMagicSquare */
    // 提示：先确认是方阵，用第一行的和作基准，再逐行、逐列、两条对角线比对。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
