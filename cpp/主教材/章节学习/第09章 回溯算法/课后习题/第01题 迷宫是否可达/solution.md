# 第9章 · 习题1：迷宫是否可达 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 三个「不能再走」的条件缺一不可：越界、撞墙、已经走过。
- **先判终点再判墙**还是反过来？起点等于终点时也应当能到达，所以先判坐标合法再判终点。
- 访问标记要回溯吗？求「是否可达」不需要撤销，走过就是走过，这和求所有路径不同。

## 容易错的边界

- 不标记访问会在两个格子之间来回递归，栈直接爆。
- 只走上下左右，不含斜角。
- 终点是墙时按非法输入处理，别返回「不能到达」。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int erGlobal = 0, ecGlobal = 0;   // 终点坐标，由 main 填好

bool canReach(const std::vector<std::string>& grid, int rows, int cols,
              int x, int y, std::vector<std::vector<bool>>& seen) {
    /* BEGIN 1 */
        if (x < 0 || x >= rows || y < 0 || y >= cols) return false;
    if (grid[x][y] != '.') return false;
    if (seen[x][y]) return false;
    if (x == erGlobal && y == ecGlobal) return true;
    seen[x][y] = true;
    return canReach(grid, rows, cols, x + 1, y, seen) || canReach(grid, rows, cols, x - 1, y, seen) ||
           canReach(grid, rows, cols, x, y + 1, seen) || canReach(grid, rows, cols, x, y - 1, seen);
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
                std::vector<std::vector<bool>> seen(rows, std::vector<bool>(cols, false));
        std::cout << (canReach(grid, rows, cols, sr, sc, seen) ? "能到达" : "不能到达") << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
