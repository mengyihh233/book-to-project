/* 第10天 叠加处理：图层（sheet）管理与刷新 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_SHEET 16
#define W 80
#define H 24

typedef struct {
    int used, x, y, w, h, z, transparent_color;
    uint8_t buf[W * H];
} Sheet;

static Sheet sheets[MAX_SHEET];
static uint8_t vram[H][W];

static void sheet_refresh(int z) {
    memset(vram, ' ', sizeof(vram));
    for (int zz = 0; zz <= z; ++zz)
        for (int s = 0; s < MAX_SHEET; ++s) {
            Sheet *sh = &sheets[s];
            if (!sh->used || sh->z != zz) continue;
            for (int y = 0; y < sh->h; ++y)
                for (int x = 0; x < sh->w; ++x) {
                    uint8_t c = sh->buf[y * sh->w + x];
                    if (c == sh->transparent_color) continue;
                    int vy = sh->y + y, vx = sh->x + x;
                    if (vy >= 0 && vy < H && vx >= 0 && vx < W) vram[vy][vx] = c;
                }
        }
}

int main(void) {
    /* 两个图层: 背景( z=0 ) 与窗口( z=1 ) */
    Sheet *bg = &sheets[0];
    bg->used = 1; bg->x = 0; bg->y = 0; bg->w = W; bg->h = H; bg->z = 0;
    bg->transparent_color = 0xFF;
    memset(bg->buf, '.', sizeof(bg->buf));

    Sheet *win = &sheets[1];
    win->used = 1; win->x = 10; win->y = 5; win->w = 30; win->h = 6; win->z = 1;
    win->transparent_color = 0xFF;
    memset(win->buf, 0xFF, sizeof(win->buf));
    memcpy(win->buf, "  [ 窗口 z=1 ]", 16);

    sheet_refresh(1);
    printf("叠加结果（背景 '.' 上盖一个窗口）:\n");
    for (int y = 0; y < 12; ++y) {
        for (int x = 0; x < 50; ++x) putchar(vram[y][x]);
        putchar('\n');
    }
    printf("\n图层按 z 从小到大绘制，后画的覆盖先画的；透明色跳过。\n");
    return 0;
}
