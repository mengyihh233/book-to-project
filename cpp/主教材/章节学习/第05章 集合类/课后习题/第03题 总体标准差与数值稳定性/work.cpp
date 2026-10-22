// 【本题说明开始】
// 第5章 · 习题3：总体标准差与数值稳定性
//
// 题目：输入协议与第2题相同，输出总体标准差一行：sqrt(sum((x-mean)^2)/n)，分母是n，不是样本标准差的n−1。单元素结果0，空集合拒绝。使用Welford更新避免“大数平
//   方之差”的相消误差，计算中采用long double。
// 实现什么：double stddev(const std::vector<double>& data)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/vector_lesson.h"

// 本题要实现的接口（声明已给出）。
double stddev(const std::vector<double>& data);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto data=numberRecords(std::cin);
        std::cout<<std::setprecision(17)<<stddev(data)<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

double stddev(const std::vector<double>& data) {
    /* BEGIN 1：stddev */
    // 提示：用 Welford 增量更新均值与平方和，避免先平方再相减，最后除以 n 再开方。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
