/* 第11天 制作窗口：窗口数据结构与标题栏绘制 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int x, y, w, h;
    char title[32];
    int active;          /* 是否激活（标题栏颜色不同） */
} Window;

static void draw_titlebar(const Window *win) {
    char c = win->active ? '*' : '-';
    printf("  %c", c);
    for (int i = 0; i < win->w - 2; ++i) putchar(c);
    printf("%c\n", c);
    /* 标题居中 */
    int tlen = (int)strlen(win->title);
    int pad = (win->w - 2 - tlen) / 2;
    if (pad < 0) pad = 0;
    printf("  |");
    for (int i = 0; i < pad; ++i) putchar(' ');
    printf("%s", win->title);
    for (int i = pad + tlen; i < win->w - 2; ++i) putchar(' ');
    printf("|\n");
    for (int i = 0; i < win->w - 2; ++i) printf("--");
    printf("\n");
}

int main(void) {
    Window a = {5, 3, 28, 10, "term", 1};
    Window b = {12, 8, 28, 10, "editor", 0};

    printf("窗口 A（激活）:\n"); draw_titlebar(&a);
    printf("\n窗口 B（非激活）:\n"); draw_titlebar(&b);
    printf("\n激活窗口标题栏用亮色，非激活用暗色 —— 用户据此判断焦点。\n");
    printf("窗口 = 一个图层 + x/y/w/h + 标题；移动窗口只是改图层的 x/y 再重绘。\n");
    return 0;
}
