/* 第26天 为窗口移动提速：差分刷新（只更新变化像素） */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define W 40
#define H 10

static uint8_t prev[H][W], cur[H][W];

static int diff_and_draw(void) {
    int changed = 0;
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            if (cur[y][x] != prev[y][x]) {
                ++changed;
                prev[y][x] = cur[y][x];
            }
    return changed;
}

int main(void) {
    memset(prev, '.', sizeof(prev));
    memcpy(cur, prev, sizeof(cur));

    /* 移动一个 5x3 的小方块 */
    for (int y = 2; y < 5; ++y) for (int x = 5; x < 10; ++x) cur[y][x] = '#';
    int c1 = diff_and_draw();
    printf("第一次出现方块: 更新 %d 像素\n", c1);

    for (int y = 2; y < 5; ++y) for (int x = 5; x < 10; ++x) cur[y][x] = '.';
    for (int y = 2; y < 5; ++y) for (int x = 8; x < 13; ++x) cur[y][x] = '#';
    int c2 = diff_and_draw();
    printf("右移 3 格:     更新 %d 像素（整屏重绘要 %d）\n", c2, W * H);

    printf("\n差分刷新只写变化像素: 本次省 %.0f%% 显存写入。\n", 100.0 * (1 - (double)c2 / (W * H)));
    printf("代价是内存里要存一份上一帧 —— 典型的空间换时间。\n");
    return 0;
}
