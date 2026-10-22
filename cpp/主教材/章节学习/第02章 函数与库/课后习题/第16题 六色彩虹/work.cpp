// 【本题说明开始】
// 第2章习题16：六色彩虹
//
// 题目与要求：
// 在天蓝背景上画红、橙、黄、绿、蓝、紫六条彩虹拱带，内部仍为天空色。为配合本区采样，所有椭圆中
// 心为(0.5W,1.35H)；从外到内编号b=0..6，半轴分别是W×(0.9−0.035b)、H×(1.2−0.055b)。颜色依次为#
// e53935、#fb8c00、#fdd835、#43a047、#1e88e5、#8e24aa、#87ceeb；最后一个为天空内部。尺寸和配色
// 是本区教学约定。
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
