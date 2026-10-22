/* 第24天 窗口操作：拖动窗口与脏矩形重绘 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define W 60
#define H 15

typedef struct { int x, y, w, h; int dragging; } Win;

static uint8_t vram[H][W];
static int dirty[H][W];

static void draw(const Win *win) {
    memset(vram, ' ', sizeof(vram));
    memset(dirty, 0, sizeof(dirty));
    for (int y = 0; y < win->h; ++y)
        for (int x = 0; x < win->w; ++x) {
            int vy = win->y + y, vx = win->x + x;
            if (vy >= 0 && vy < H && vx >= 0 && vx < W) {
                vram[vy][vx] = (y == 0 || x == 0) ? '+' : ' ';
                dirty[vy][vx] = 1;
            }
        }
}

int main(void) {
    Win win = {5, 3, 20, 6, 0};
    draw(&win);
    int first = 0;
    for (int y = 0; y < H; ++y) for (int x = 0; x < W; ++x) first += dirty[y][x];
    printf("初始绘制: %d 个像素被写\n", first);

    /* 拖动到新位置 */
    win.x += 10; win.y += 2;
    draw(&win);
    int second = 0;
    for (int y = 0; y < H; ++y) for (int x = 0; x < W; ++x) second += dirty[y][x];
    printf("移动后重绘: %d 个像素被写\n", second);
    printf("\n若不优化: 每次刷新整屏 %d 像素；只重绘脏矩形省 %.0f%%\n",
           W * H, 100.0 * (1 - (double)second / (W * H)));
    printf("\n窗口移动 = 改 x/y + 只重绘受影响区域；原书用 sheet 的 bx/by/bw/bh 记录。\n");
    return 0;
}
