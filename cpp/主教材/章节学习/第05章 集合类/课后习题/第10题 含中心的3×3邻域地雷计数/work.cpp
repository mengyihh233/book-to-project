// 【本题说明开始】
// 第5章 · 习题10：含中心的3×3邻域地雷计数
//
// 题目：输入首行rows cols（0..100），随后逐行输入0/1网格，1代表地雷。输出首行同样形状，再输出每个格子周围3×3区域的地雷总数，越界位置忽略；按原书特别要求，中心格自身也包含
//   在区域内。全1的3×3网格中，中心9、边6、角4。非0/1单元退出2。
// 实现什么：void fixCounts(const IntGrid& mines, IntGrid& counts)
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
void fixCounts(const IntGrid& mines, IntGrid& counts);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto mines=readGrid(std::cin);
        IntGrid counts(0,0);
        fixCounts(mines,counts);
        printGrid(counts,std::cout);
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void fixCounts(const IntGrid& mines, IntGrid& counts) {
    /* BEGIN 1：fixCounts */
    // 提示：对每个格子遍历它周围 3×3 的范围，越界就跳过，统计地雷数写进 counts。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
