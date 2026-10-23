// 【本题说明开始】
// 第9章 · 习题1：迷宫是否可达
//
// 题目：读入一张迷宫，判断从起点能否走到终点（只能上下左右走，不能穿墙）。
// 实现什么：`canReach` 的四方向递归 + `main` 的读图与判定。
// 写在哪里：只补下方 BEGIN 1（递归搜索函数）与 BEGIN 2（读入与输出）之间的代码。
// 文本格式：一行 `能到达`/`不能到达`；非法输入返回 2 且 stdout 为空。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int erGlobal = 0, ecGlobal = 0;   // 终点坐标，由 main 填好

bool canReach(const std::vector<std::string>& grid, int rows, int cols,
              int x, int y, std::vector<std::vector<bool>>& seen) {
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
        int sr = 0, sc = 0, er = 0, ec = 0;
        if (!(std::cin >> sr >> sc >> er >> ec)) throw std::invalid_argument("缺少起终点");
        erGlobal = er;
        ecGlobal = ec;
        if (sr < 0 || sr >= rows || sc < 0 || sc >= cols || er < 0 || er >= rows || ec < 0 || ec >= cols)
            throw std::invalid_argument("起终点越界");
        if (grid[sr][sc] != '.' || grid[er][ec] != '.') throw std::invalid_argument("起终点不能是墙");
        /* BEGIN 2 */
        throw std::logic_error("补全区尚未完成");
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
