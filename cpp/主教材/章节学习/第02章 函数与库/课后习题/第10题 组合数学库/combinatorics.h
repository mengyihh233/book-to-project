#ifndef LEARNING_COMBINATORICS_H
#define LEARNING_COMBINATORICS_H
// 原书第2章习题10：接口与实现分离。结果使用signed 64-bit。
namespace combinatorics {
// 要求0<=k<=n<=1000000；参数非法或结果越界时抛异常。
long long permutations(long long n, long long k);
long long combinations(long long n, long long k);
}
#endif
