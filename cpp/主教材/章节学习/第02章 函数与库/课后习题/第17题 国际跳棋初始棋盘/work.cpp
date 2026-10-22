// 【本题说明开始】
// 第2章习题17：国际跳棋初始棋盘
//
// 题目与要求：
// 画居中的8×8棋盘及初始棋子，不实现走棋。棋盘边长S=0.85×min(W,H)，格长=S/8；左上格浅色#fff3e0，
// 深格#6d4c41。上三行的深格放红子#c0392b，下三行深格放黑子#30343b，各12枚；中间两行无子。棋子
// 在格中心，半径为格长的0.36，背景白色。尺寸配色是本区教学约定。
//
// 写在哪里：只编辑本文件中的自己的实现；不要复制参考答案覆盖。
// 怎么做：先手算样例，再写实现，最后检查正常、边界和错误情况。
// 怎么检查：任务“本题：检查作答”，使用图形专项检查器。
//
// 写在哪里：本文件的draw(Canvas& canvas)函数体；保留main和canvas.h。
// 输入：width height，均为200..1600；空输入默认640×400。
// 输出：SVG文本；普通运行不会自动弹出图形窗口。
// 完整题目与文本格式：README.md。
// 【本题说明结束】
//
#include "canvas.h"
#include <algorithm>
// 只复用绘图工具，题目图形在这里独立实现。
void draw(Canvas& canvas) {
    (void)canvas; // TODO: 完成题目图形
}
int main() {
    try { int width,height; dimensions(width,height); Canvas canvas(width,height); draw(canvas); canvas.write(); }
    catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; }
}
