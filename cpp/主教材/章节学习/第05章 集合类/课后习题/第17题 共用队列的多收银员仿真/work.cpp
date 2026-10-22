// 【本题说明开始】
// 第5章习题17：共用队列的多收银员仿真
//
// 题目：所有顾客按到达顺序进入同一条FIFO等待队列，空闲收银员按编号顺序从队首接人。
// 实现什么：QueueResult simulateShared(const QueueTrace& trace)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/queue_trace.h"

// 本题要实现的接口（声明已给出）。
QueueResult simulateShared(const QueueTrace& trace);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto trace=readQueueTrace(std::cin);
        printQueueResult(simulateShared(trace),trace.services.size(),std::cout);
    } catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

QueueResult simulateShared(const QueueTrace& trace) {
    /* BEGIN 1：simulateShared */
    // 提示：所有顾客进同一条队列，空闲的收银员按编号顺序从队首接人。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
