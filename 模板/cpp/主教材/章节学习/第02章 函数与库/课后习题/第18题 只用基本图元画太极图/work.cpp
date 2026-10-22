// 【本题说明开始】
// 第2章习题18：只用基本图元画太极图
//
// 题目与要求：
// 画居中的太极图，不实现动画。圆心(W/2,H/2)，大圆半径R=0.38×min(W,H)，背景白；上方圆心y=cy−R/2、
// 下方y=cy+R/2，S形区域按本区上白下黑朝向；两处反色圆点半径R/8。使用canvas.h的矩形/椭圆和外轮
// 廓工具，不能只输出一个文字名称代替图形。朝向尺寸是本区教学约定。
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
