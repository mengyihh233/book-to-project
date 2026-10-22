/* 第4天 C 语言与画面显示：模拟 VGA 显存与像素写入 */
#include <stdio.h>
#include <stdint.h>

#define W 320
#define H 200

static uint8_t vram[W * H];   /* 模式 0x13: 320x200x8bit 调色板 */

static void put(int x, int y, uint8_t c) {
    if (x >= 0 && x < W && y >= 0 && y < H) vram[y * W + x] = c;
}

int main(void) {
    /* 画一条 Bresenham 直线 (10,10) -> (100,60) */
    int x0 = 10, y0 = 10, x1 = 100, y1 = 60;
    int dx = x1 - x0, dy = y1 - y0;
    int sx = dx > 0 ? 1 : -1, sy = dy > 0 ? 1 : -1;
    dx = dx < 0 ? -dx : dx; dy = dy < 0 ? -dy : dy;
    int err = dx - dy, plotted = 0;
    for (;;) {
        put(x0, y0, 15);
        ++plotted;
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
    printf("Bresenham 画线 (10,10)->(100,60): 绘制 %d 个像素\n", plotted);

    /* 填充矩形 */
    int filled = 0;
    for (int y = 150; y < 180; ++y)
        for (int x = 200; x < 260; ++x) { put(x, y, 4); ++filled; }
    printf("填充矩形 60x30: %d 个像素\n", filled);

    printf("VRAM 地址 0xa0000，每字节一像素，值是调色板索引而非 RGB。\n");
    printf("原书用汇编写 init_palette + 逐像素赋值，本质就是这个二维数组。\n");
    return 0;
}
