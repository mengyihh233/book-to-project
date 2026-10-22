// 【本题说明开始】
// 第5章习题16：各自队列与最短队列选择
//
// 题目：每个收银员一条等待队列；新顾客选择等待人数最少者，并列选小编号，之后不换队。服务中的人不计队长。
// 实现什么：QueueResult simulateSeparate(const QueueTrace& trace)
// 写在哪里：只补下方 BEGIN 1 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/queue_trace.h"

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
inline std::size_t findShortestQueue(const std::vector<std::queue<QueueCustomer>>& queues) {
    if(queues.empty())throw std::invalid_argument("cashier queue vector is empty");
    std::size_t shortest=0;
    for(std::size_t i=1;i<queues.size();++i)if(queues[i].size()<queues[shortest].size())shortest=i;
    return shortest;
}

// 本题要实现的接口（声明已给出）。
QueueResult simulateSeparate(const QueueTrace& trace);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main() {
    try {
        const auto trace=readQueueTrace(std::cin);
        printQueueResult(simulateSeparate(trace),trace.services.size(),std::cout);
    } catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 1 个函数体。

QueueResult simulateSeparate(const QueueTrace& trace) {
    /* BEGIN 1：simulateSeparate */
    // 提示：维护一组队列和各自长度，每次挑等待人数最少且编号最小的那个。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}
