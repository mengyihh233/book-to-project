// 【本题说明开始】
// 第4章 · 习题8：用流状态机去除注释
//
// 题目：标准输入整段ASCII源文本，标准输出去注释结果，不额外添加换行。//删除至行尾但保留LF；/*…*/删除整个块，包括块内换行，不支持嵌套。按原书允许简化，不识别字符串/字符字面量中的
//   注释标记，也不处理预处理器续行。块未闭合视为错误，退出2且标准输出（cout）为空。它会把int//x拼成intx，因此不能直接充当生产编译器的预处理器。
// 实现什么：void removeComments(std::istream& in, std::ostream& out)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#include <locale>

// 本题要实现的接口（声明已给出）。
void removeComments(std::istream& in, std::ostream& out);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    std::ostringstream output;
    try {
        removeComments(std::cin,output);
        std::cout<<output.str();
    } catch(const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

void removeComments(std::istream& in, std::ostream& out) {
    /* BEGIN 1：removeComments */
    // 提示：用一个状态变量记录当前是正常、行注释还是块注释，进入和退出注释的边界字符都要吃掉。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
