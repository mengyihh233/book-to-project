// 【本题说明开始】
// 第12章 · 习题4：动态数组 IntArray
//
// 题目：实现一个自己管内存的 IntArray：越界要抛异常、扩容要保留旧值、拷贝必须是深拷贝。
// 实现什么：IntArray 的构造、析构、拷贝、get/set/resize/sum + main 命令循环。
// 写在哪里：只补下方 BEGIN 1（IntArray 的成员函数）与 BEGIN 2（命令循环与输出）之间的代码。
// 文本格式：按命令输出整数；越界或非法长度返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

class IntArray {
public:
    explicit IntArray(int size);
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);
    ~IntArray();

    int size() const { return size_; }
    int get(int index) const;
    void set(int index, int value);
    void resize(int newSize);
    long long sum() const;

private:
    int* data_;
    int size_;
};

/* BEGIN 1 */
// 这里放上面 7 个成员函数的实现（构造、拷贝构造、拷贝赋值、析构、get、set、resize、sum）。
// @@1@@
/* END 1 */

int main() {
    try {
        int commands = 0;
        if (!(std::cin >> commands) || commands < 0 || commands > 100) {
            throw std::invalid_argument("命令条数必须在 0 到 100 之间");
        }
        int size = 0;
        if (!(std::cin >> size) || size < 1 || size > 1000) {
            throw std::invalid_argument("数组长度必须在 1 到 1000 之间");
        }
        IntArray array(size);

        /* BEGIN 2 */
        // 读 commands 条命令并执行：
        // set i v / get i / size / sum / resize k / deepcopy
        // get、size、sum、deepcopy 要输出；未知命令抛 invalid_argument。
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
