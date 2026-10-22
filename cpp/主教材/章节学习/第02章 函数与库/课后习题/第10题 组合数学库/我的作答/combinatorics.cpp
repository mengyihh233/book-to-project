// 第2章习题10：自己的组合数学库。
// 题目：../README.md。只补两个 BEGIN / END 区域；头文件和主程序已给定。
// 保存本文件后，直接运行“本题：检查作答”；工具自动找到 ../work.cpp 并链接本库。
#include "combinatorics.h"
#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>

namespace combinatorics {

long long permutations(long long n, long long k) {
    /* BEGIN 1：实现排列数 P(n, k) */
    // 要求 0 <= k <= n <= 1000000；参数非法或结果超出 long long 范围时抛异常。
    // 直接连乘 k 个因子；k 为 0 时结果是 1。乘法前检查溢出。
    // 可复用第9题的思路；完成后删除占位 throw，返回计算结果。
    throw std::logic_error("补全区尚未完成：permutations");
    /* END 1 */
}

long long combinations(long long n, long long k) {
    /* BEGIN 2：实现组合数 C(n, k) */
    // 参数范围和溢出约定与排列数相同；k 为 0 时结果是 1。
    // 利用对称性减少计算，并约分后再乘，避免中间溢出。
    // 不要先算两个阶乘或先求完整排列数；需要约分时可用 std::gcd。
    // 完成后删除占位 throw，返回计算结果。
    throw std::logic_error("补全区尚未完成：combinations");
    /* END 2 */
}

}
