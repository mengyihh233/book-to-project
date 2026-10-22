/* 第5天 结构体、文字显示与 GDT/IDT 初始化：模拟 8x16 点阵字体 */
#include <stdio.h>
#include <stdint.h>

/* 用 5x7 点阵拼 "Hi" */
static const uint8_t font_H[7] = {0x7F,0x08,0x08,0x08,0x08,0x08,0x7F};
static const uint8_t font_i[7] = {0x00,0x08,0x08,0x08,0x08,0x08,0x08};

int main(void) {
    const char *msg = "Hi";
    printf("文字显示 = 每个字符一张位图，逐行扫到显存\n\n");
    for (int row = 0; row < 7; ++row) {
        printf("  ");
        for (const char *p = msg; *p; ++p) {
            uint8_t bits = (*p == 'H') ? font_H[row] : font_i[row];
            for (int b = 4; b >= 0; --b) putchar((bits >> b) & 1 ? '#' : '.');
            putchar(' ');
        }
        putchar('\n');
    }
    printf("\n原书把 256 个 ASCII 的字模存成 hankaku 数组，取模后写入 VRAM。\n");
    printf("IDT 有 256 项，每项 8 字节；未使用的中断指向一个“假中断”处理。\n");
    return 0;
}
