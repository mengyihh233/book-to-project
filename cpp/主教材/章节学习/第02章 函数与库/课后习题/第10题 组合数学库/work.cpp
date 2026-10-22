// 【本题说明开始】
// 第2章习题10：组合数学库
//
// 题目：输入 P/C n k，分别计算排列数或组合数；0 <= k <= n <= 1000000。
// 结果须能用 long long 表示；k 为 0 时结果为 1。参数非法或结果溢出时抛异常。
//
// 写在哪里：我的作答/combinatorics.cpp 的 BEGIN 1、BEGIN 2 函数体。
// 对照接口：我的作答/combinatorics.h 已给出声明，无需修改。
// 本文件 work.cpp 是给定主程序，负责读入、调用、输出与错误处理，不用重写。
// 怎么做：先完成排列，再实现不会中间溢出的组合数；具体要求见 README.md。
//
// 怎么检查：先保存库 cpp，直接运行任务“本题：检查作答”，无需切换到本文件。
// 工具自动找到本文件并链接自己的库实现，比对登记的13组输入、输出与退出码。
// 正常返回0；错误说明写到cerr、返回2，cout为空；不要输出“请输入”等提示语。
// 样例输入：P 52 2
// 期望输出：2652
// input.txt 只是手动输入；外层 combinatorics.cpp 是参考实现，不是作答位置。
// 完整题目与文本格式：README.md。
// 【本题说明结束】
//
// 给定调用入口：请在我的作答目录的库 cpp 内补全函数。
#include "我的作答/combinatorics.h"
#include <exception>
#include <iostream>
#include <stdexcept>
int main() {
    try {
        char operation;
        long long n, k;
        if (!(std::cin >> operation >> n >> k)) throw std::runtime_error("use P/C n k");
        std::cin >> std::ws;
        if (!std::cin.eof()) throw std::runtime_error("unexpected input");
        if (operation == 'P') std::cout << combinatorics::permutations(n, k) << '\n';
        else if (operation == 'C') std::cout << combinatorics::combinations(n, k) << '\n';
        else throw std::runtime_error("operation must be P or C");
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
