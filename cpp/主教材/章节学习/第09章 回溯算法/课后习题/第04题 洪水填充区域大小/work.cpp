// 【本题说明开始】
// 第9章 · 习题4：洪水填充区域大小
//
// 题目：读入一张黑白像素图，求从某个白点出发能连成一片的白色像素个数。
// 实现什么：`flood` 的四方向递归求和 + `main` 的读图与输出。
// 写在哪里：只补下方 BEGIN 1（递归搜索函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行区域大小；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int flood(const std::vector<std::string>& grid, std::vector<std::vector<bool>>& seen,
          int rows, int cols, int x, int y) {
    /* BEGIN 1 */
    throw std::logic_error("补全区尚未完成");
    /* END 1 */
}

int main() {
    try {
        int rows = 0, cols = 0;
        if (!(std::cin >> rows >> cols) || rows < 1 || rows > 20 || cols < 1 || cols > 20) {
            throw std::invalid_argument("行列必须在 1 到 20 之间");
        }
        std::vector<std::string> grid(rows);
        for (int i = 0; i < rows; ++i) {
            if (!(std::cin >> grid[i]) || static_cast<int>(grid[i].size()) != cols) {
                throw std::invalid_argument("第 " + std::to_string(i + 1) + " 行长度不对");
            }
        }
        int sr = 0, sc = 0;
        if (!(std::cin >> sr >> sc)) throw std::invalid_argument("缺少起点");
        if (sr < 0 || sr >= rows || sc < 0 || sc >= cols) throw std::invalid_argument("起点越界");
        /* BEGIN 2 */
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
