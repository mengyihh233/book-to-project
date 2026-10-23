# 第9章 · 习题4：洪水填充区域大小 · 解析

> **先自己写完再看。** 先想清楚自己卡在哪一步，再读代码；整段抄过去这题就白做了。

## 思路

- 递归返回值是「这一片有多少个」，所以是 `1 + 四个方向` 的和。
- 黑点返回 0，不要抛异常——它只是不能填。
- 访问标记防止重复计数，也不用撤销（这里只数一次）。

## 容易错的边界

- 起点是黑点时答案是 0，不是返回 2（越界才是 2）。
- 别把对角线算进连通——四连通只算上下左右。
- 20×20 全白时答案是 400，用 int 足够，但别再往下加。

## 参考实现

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int flood(const std::vector<std::string>& grid, std::vector<std::vector<bool>>& seen,
          int rows, int cols, int x, int y) {
    /* BEGIN 1 */
        if (x < 0 || x >= rows || y < 0 || y >= cols) return 0;
    if (grid[x][y] != '.') return 0;
    if (seen[x][y]) return 0;
    seen[x][y] = true;
    return 1 + flood(grid, seen, rows, cols, x + 1, y) + flood(grid, seen, rows, cols, x - 1, y) +
           flood(grid, seen, rows, cols, x, y + 1) + flood(grid, seen, rows, cols, x, y - 1);
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
                std::vector<std::vector<bool>> seen(rows, std::vector<bool>(cols, false));
        std::cout << flood(grid, seen, rows, cols, sr, sc) << '\n';
        /* END 2 */
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 2;
    }
}
```
