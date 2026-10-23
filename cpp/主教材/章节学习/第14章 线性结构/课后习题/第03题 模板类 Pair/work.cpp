// 【本题说明开始】
// 第14章 · 习题3：模板类 Pair
//
// 题目：实现一个模板类 Pair，存一对同类型的值，按第一项排序输出。
// 实现什么：`Pair<T>` 模板类 + `main` 的类型判断与排序。
// 写在哪里：只补下方 BEGIN 1（模板实现）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：每行 `(a, b)`；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
class Pair {
public:
    Pair(T first, T second) : first_(first), second_(second) {}
    T first() const { return first_; }
    T second() const { return second_; }
    std::string toString() const {
        std::ostringstream out;
        out << '(' << first_ << ", " << second_ << ')';
        return out.str();
    }

private:
    T first_;
    T second_;
};

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 1 || n > 1000) {
            throw std::invalid_argument("n 必须在 1 到 1000 之间");
        }
        /* BEGIN 1 */
        // @@1@@
        /* END 1 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
