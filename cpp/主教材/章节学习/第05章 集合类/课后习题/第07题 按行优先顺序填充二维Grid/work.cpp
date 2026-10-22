// 【本题说明开始】
// 第5章 · 习题7：按行优先顺序填充二维Grid
//
// 题目：第1行rows cols（各0..100）；第2行元素个数N（0..10000）；随后N行，每行一个int32。N必须恰好等于rows*cols，按行优先填充，不足或多余均报错。输出先
//   列rows cols，再逐行输出矩阵元素，空格分隔；任一维为0时只输出形状行。函数先检查长度，错误时不改目标Grid。
// 实现什么：void fillGrid(IntGrid& grid, const std::vector<int>& values)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/grid_lesson.h"
#include <cstdint>

// 本题要实现的接口（声明已给出）。
void fillGrid(IntGrid& grid, const std::vector<int>& values);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        IntGrid grid=readGridShape(std::cin);
        std::string line;
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing count");
        int count=strictNumber<int>(line);
        if(count<0||count>10000) throw std::out_of_range("value count");
        std::vector<int> values;
        for(int i=0;i<count;++i) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing value");
            values.push_back(strictNumber<int>(line));
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra input");
        fillGrid(grid,values);
        std::ostringstream out;
        out<<grid.rows()<<' '<<grid.cols()<<'\n';
        if(grid.cols()!=0) for(int row=0;row<grid.rows();++row) {
            for(int col=0;col<grid.cols();++col) out<<(col?" ":"")<<grid.at(row,col);
            out<<'\n';
        }
        std::cout<<out.str();
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void fillGrid(IntGrid& grid, const std::vector<int>& values) {
    /* BEGIN 1：fillGrid */
    // 提示：先确认 values 的个数正好等于 rows*cols，再按行优先逐个填入。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
