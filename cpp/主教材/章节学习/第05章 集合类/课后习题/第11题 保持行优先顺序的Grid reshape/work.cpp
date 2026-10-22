// 【本题说明开始】
// 第5章 · 习题11：保持行优先顺序的Grid reshape
//
// 题目：输入首行旧rows cols（0..100），随后旧矩阵逐行数据，最后一行newRows newCols（0..100）。按行优先序保留前min(旧容量,新容量)个值，变小丢弃尾部，变
//   大在尾部补0。输出新形状及逐行矩阵；任一维为0时不读取/输出数据行，仍保留形状。它与清空数据的resize、把行列对换的transpose不同。
// 实现什么：void reshape(IntGrid& grid, int newRows, int newCols)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/grid_lesson.h"

// 参考实现里 main 之外的小工具，原样给出。
inline void printGrid(const IntGrid& grid,std::ostream& out) {
    out<<grid.rows()<<' '<<grid.cols()<<'\n';
    if(grid.cols()) for(int r=0;r<grid.rows();++r) {
        for(int c=0;c<grid.cols();++c) out<<(c?" ":"")<<grid.at(r,c);
        out<<'\n';
    }
}

// 本题要实现的接口（声明已给出）。
void reshape(IntGrid& grid, int newRows, int newCols);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto grid=readGridShape(std::cin);
        std::string line;
        if(grid.cols()) for(int r=0;r<grid.rows();++r) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing row");
            std::istringstream row(line);
            for(int c=0;c<grid.cols();++c) if(!(row>>grid.at(r,c))) throw std::invalid_argument("invalid cell");
            row>>std::ws;
            if(!row.eof()) throw std::invalid_argument("extra cell");
        }
        auto shape=readGridShape(std::cin);
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra input");
        reshape(grid,shape.rows(),shape.cols());
        printGrid(grid,std::cout);
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void reshape(IntGrid& grid, int newRows, int newCols) {
    /* BEGIN 1：reshape */
    // 提示：把旧值按行优先读成一维序列，再按新尺寸逐行填回，不足的补 0。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
