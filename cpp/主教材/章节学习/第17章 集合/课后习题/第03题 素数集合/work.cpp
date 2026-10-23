// 【本题说明开始】
// 第17章 · 习题3：素数集合
//
// 题目：返回 2 到 max 之间所有素数的集合，用「已经找到的素数」当除数，试到平方根就够。
// 实现什么：`createPrimeSet()` 的筛法 + `main` 的读入与输出。
// 写在哪里：只补下方 BEGIN 1（集合的读取 / 位串解析）与 BEGIN 2（主程序的组合与输出）之间的代码。
// 文本格式：一行素数集合；max 越界返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <cstddef>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

// 返回 2 到 max 之间所有素数的集合。
std::set<int> createPrimeSet(int max) {
    /* BEGIN 1 */
    // @@1@@
    /* END 1 */
}

int main() {
    try {
        /* BEGIN 2 */
        // 读 max（2..1000000），调用 createPrimeSet，按 `{2, 3, 5}` 的格式输出。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}
