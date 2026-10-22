/* 第23天 图形处理：线段裁剪（Cohen-Sutherland） */
#include <stdio.h>
#include <stdint.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

#define XMIN 0
#define YMIN 0
#define XMAX 100
#define YMAX 60

static int compute_code(double x, double y) {
    int c = INSIDE;
    if (x < XMIN) c |= LEFT; else if (x > XMAX) c |= RIGHT;
    if (y < YMIN) c |= BOTTOM; else if (y > YMAX) c |= TOP;
    return c;
}

int main(void) {
    double x0 = -20, y0 = -10, x1 = 120, y1 = 80;
    printf("裁剪前线段: (%.0f,%.0f) -> (%.0f,%.0f)\n", x0, y0, x1, y1);

    int c0 = compute_code(x0, y0), c1 = compute_code(x1, y1);
    int accept = 0, steps = 0;

    for (;;) {
        if ((c0 | c1) == 0) { accept = 1; break; }
        if ((c0 & c1) != 0) break;
        int cout = c0 ? c0 : c1;
        double x, y;
        if (cout & TOP) { x = x0 + (x1 - x0) * (YMAX - y0) / (y1 - y0); y = YMAX; }
        else if (cout & BOTTOM) { x = x0 + (x1 - x0) * (YMIN - y0) / (y1 - y0); y = YMIN; }
        else if (cout & RIGHT) { y = y0 + (y1 - y0) * (XMAX - x0) / (x1 - x0); x = XMAX; }
        else { y = y0 + (y1 - y0) * (XMIN - x0) / (x1 - x0); x = XMIN; }

        if (cout == c0) { x0 = x; y0 = y; c0 = compute_code(x0, y0); }
        else { x1 = x; y1 = y; c1 = compute_code(x1, y1); }
        ++steps;
        if (steps > 10) break;
    }

    if (accept) printf("裁剪后线段: (%.1f,%.1f) -> (%.1f,%.1f)  (%d 步)\n", x0, y0, x1, y1, steps);
    else printf("线段完全在窗口外，丢弃\n");
    printf("\nCohen-Sutherland 用端点编码快速判断“全内/全外/要求交”。\n");
    return 0;
}
