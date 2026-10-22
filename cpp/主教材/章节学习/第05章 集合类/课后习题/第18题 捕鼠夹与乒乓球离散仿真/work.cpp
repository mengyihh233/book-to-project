// 【本题说明开始】
// 第5章习题18：捕鼠夹与乒乓球离散仿真
//
// 题目：两种教学输入：首行trace side，随后每轮一行落点编号，数量必须恰等于本轮空中球数；或首行random side seed，自动生成所有落点且没有后续行。side为1..25，原
//   书规模用25；seed为0..4294967295。位置按行编号0..side²−1，允许重复。固定种子和小网格是教学适配，随机发生器及局限见推导。
// 实现什么：ChainResult simulateChain(std::istream& in)、void printChain(const ChainResult& r, std::ostream& out)
// 写在哪里：只补下方 BEGIN 1、BEGIN 2 之间的函数体。
// 文本格式：只输出答案本身，行末换行；错误说明写 cerr、返回 2。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include "../../../../教学辅助/input_line.h"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// 以下类型、常量与辅助函数已给出，直接使用，不要修改。
// 第18题：整轮落地，整轮生成下一批；不能让新球在本轮继续落地。
struct ChainResult { int rounds=0, triggered=0, peak=1, landings=0, traps=0; };

// 本题要实现的接口（声明已给出）。
ChainResult simulateChain(std::istream& in);
void printChain(const ChainResult& r, std::ostream& out);

// 给定的主程序：读入、调用、输出都已写好。不要重写 main。
int main(){
    try {
        const auto r=simulateChain(std::cin);
        printChain(r,std::cout);
    }catch(const std::exception& e){
        std::cerr<<e.what()<<'\n';
        return 2;
    }
}

// 实现位置：只填写下面 2 个函数体。

ChainResult simulateChain(std::istream& in) {
    /* BEGIN 1：simulateChain */
    // 提示：按轮推进：先让旧球落地，再让新触发的球进入下一轮，直到空中为零。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

void printChain(const ChainResult& r, std::ostream& out) {
    /* BEGIN 2：printChain */
    // 提示：按题目格式逐行输出统计量，注意百分比与峰值的取整方式。
    // 写完删掉下面的占位 throw，返回真实结果。
    throw std::logic_error("补全区尚未完成");
    /* END 2 */
}
