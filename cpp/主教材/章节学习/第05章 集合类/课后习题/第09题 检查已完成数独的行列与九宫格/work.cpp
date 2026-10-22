// 【本题说明开始】
// 第5章 · 习题9：检查已完成数独的行列与九宫格
//
// 题目：输入首行rows cols，随后每行一行整数矩阵。必须为9×9，否则退出2；单元须为int32，完整读取后检查是否恰好由1..9组成且每行、每列、每个3×3宫内不重复，输出true/f
//   alse。0、负数、10等是无效解，返回false；本题只检查完成的解，不求解空白数独。
// 实现什么：bool checkSudokuSolution(const IntGrid& puzzle)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/grid_lesson.h"

// 本题要实现的接口（声明已给出）。
bool checkSudokuSolution(const IntGrid& puzzle);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto grid=readGrid(std::cin);
        std::cout<<(checkSudokuSolution(grid)?"true":"false")<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

bool checkSudokuSolution(const IntGrid& puzzle) {
    /* BEGIN 1：checkSudokuSolution */
    // 提示：用计数数组检查每行、每列、每个 3×3 宫是否恰好出现 1 到 9 各一次。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
