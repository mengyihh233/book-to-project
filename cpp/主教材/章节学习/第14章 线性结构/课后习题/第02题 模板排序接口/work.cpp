// 【本题说明开始】
// 第14章 · 习题2：模板排序接口
//
// 题目：写一个模板函数把任意可比较的元素排好序：同一份代码同时服务整数和字符串。
// 实现什么：`sortValues<T>` 模板 + `main` 的类型分派。
// 写在哪里：只补下方 BEGIN 1（模板实现）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行升序结果；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 模板函数：对任意能用 < 比较的类型做插入排序。
template <class T>
void sortValues(std::vector<T>& data) {
    /* BEGIN 1 */
    // @@1@@
    /* END 1 */
}

int main() {
    try {
        std::string type;
        int n = 0;
        if (!(std::cin >> type >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("n 必须在 1 到 1000 之间");
        }
        /* BEGIN 2 */
        // 按 type 读入 int 或 string 的 n 个值，排序后空格分隔输出。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
