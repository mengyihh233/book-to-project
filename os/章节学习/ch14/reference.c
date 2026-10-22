/* 第14天 高分辨率及键盘输入：键盘扫描码 -> ASCII */
#include <stdio.h>
#include <stdint.h>

/* 简化: US 布局主区扫描码 -> ASCII（仅可打印键） */
static const char map[128] = {
    ['A']='a', ['B']='b', ['C']='c', ['D']='d', ['E']='e', ['F']='f', ['G']='g',
    ['H']='h', ['I']='i', ['J']='j', ['K']='k', ['L']='l', ['M']='m', ['N']='n',
    ['O']='o', ['P']='p', ['Q']='q', ['R']='r', ['S']='s', ['T']='t',
    ['U']='u', ['V']='v', ['W']='w', ['X']='x', ['Y']='y', ['Z']='z',
    [' ']=' ', ['\r']='\n'
};

int main(void) {
    /* 一串扫描码（含 shift 与释放码） */
    uint8_t codes[] = {0x1E, 0x9E, 0x2A, 0x1E, 0x9E, 0xAA, 0x39, 0xB9};
    int n = sizeof(codes) / sizeof(codes[0]);
    int shift = 0;

    printf("扫描码流（0x80 位表示释放，0x2A/0xAA 是左右 shift）:\n  ");
    for (int i = 0; i < n; ++i) printf("%02X ", codes[i]);
    printf("\n\n解码:\n");

    for (int i = 0; i < n; ++i) {
        uint8_t c = codes[i];
        if (c == 0x2A || c == 0x36) { shift = 1; printf("  shift 按下\n"); continue; }
        if (c == 0xAA || c == 0xB6) { shift = 0; printf("  shift 释放\n"); continue; }
        if (c & 0x80) { printf("  %02X 释放，忽略\n", c); continue; }

        char ch = map[c];
        if (shift && ch >= 'a' && ch <= 'z') ch -= 32;
        printf("  %02X 按下 -> '%c'\n", c, ch ? ch : '?');
    }
    printf("\n键盘控制器只给 make/break code，字符映射由 OS 维护的表格决定。\n");
    return 0;
}
