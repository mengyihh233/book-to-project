// 【本题说明开始】
// 第5章 · 习题2：数值集合的平均值
//
// 题目：输入第1行元素个数1..10000，后续每行一个有限double，绝对值≤1e150。输出平均值一行，17位有效数字。空集合的平均值未定义，本区用异常/退出2表示；函数用const引用避免复制容器。
// 实现什么：mean(const std::vector<double>& data)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示，错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/vector_lesson.h"

// 本题要实现的接口（声明已给出）。
double mean(const std::vector<double>& data);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        auto data=numberRecords(std::cin);
        std::cout<<std::setprecision(17)<<mean(data)<<'\n';
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

double mean(const std::vector<double>& data) {
    /* BEGIN 1：mean */
    // 提示：先求和再除以个数；空容器要抛异常，不要返回 0 当作答案。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
