// 【本题说明开始】
// 第13章 · 习题4：编辑器缓冲区
//
// 题目：实现一个带光标的文本缓冲区：插入、前后移动、删除、按位置打印。
// 实现什么：EditorBuffer 的插入/移动/删除/取长度 + main 的命令分派。
// 写在哪里：只补下方 BEGIN 1（EditorBuffer 的成员函数）与 BEGIN 2（命令循环与输出）之间的代码。
// 文本格式：print 输出带 `|` 的文本，length 输出字符数；非法命令返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>
#include <string>

class EditorBuffer {
public:
    void insert(char ch);
    void forward();
    void backward();
    void deleteCharacter();
    int length() const { return static_cast<int>(text_.size()); }
    std::string text() const { return text_; }
    int cursor() const { return cursor_; }

private:
    std::string text_;
    int cursor_ = 0;
};

/* BEGIN 1 */
// @@1@@
/* END 1 */

int main() {
    try {
        int n = 0;
        if (!(std::cin >> n) || n < 0 || n > 200) {
            throw std::invalid_argument("命令条数必须在 0 到 200 之间");
        }
        EditorBuffer buffer;

        /* BEGIN 2 */
        // @@2@@
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
