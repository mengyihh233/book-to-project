// 【本题说明开始】
// 第5章 · 习题4：0到100分的文字直方图
//
// 题目：输入第1行分数个数0..10000，后续每行一个0..100整数。输出11行，标签字段右对齐宽4，再跟:和一个空格，再按频数打印星号。0s到90s分别代表十个区间，100单独一行；负数
//   、大于100或小数均拒绝。空集合输出全零直方图。
// 实现什么：std::array<std::size_t,11> histogram(const std::vector<int>& scores)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/vector_lesson.h"

// 本题要实现的接口（声明已给出）。
std::array<std::size_t,11> histogram(const std::vector<int>& scores);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        std::string line;
        if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing count");
        int n=strictNumber<int>(line);
        if(n<0 || n>10000) throw std::out_of_range("record count");
        std::vector<int> data;
        for(int i=0;i<n;++i) {
            if(!book_input::logicalLine(std::cin,line)) throw std::invalid_argument("missing score");
            data.push_back(strictNumber<int>(line));
        }
        if(book_input::logicalLine(std::cin,line)||std::cin.bad()) throw std::invalid_argument("extra data");
        auto counts=histogram(data);
        std::ostringstream out;
        for(int i=0;i<11;++i) out<<std::setw(4)<<(i==10?"100":std::to_string(i*10)+"s")<<": "<<std::string(counts[i],'*')<<'\n';
        std::cout<<out.str();
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

std::array<std::size_t,11> histogram(const std::vector<int>& scores) {
    /* BEGIN 1：histogram */
    // 提示：先把每个分数归到 11 个桶里，再按题目要求右对齐标签、逐个打印星号。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
