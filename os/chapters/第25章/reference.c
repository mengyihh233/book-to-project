/* 第25天 增加命令行窗口：多窗口与焦点切换 */
#include <stdio.h>
#include <string.h>

#define MAXW 8

typedef struct { int used; char title[16]; int z; int focused; } Win;

int main(void) {
    Win wins[MAXW] = {0};
    const char *names[] = {"console", "editor", "image"};
    int nn = 3;

    for (int i = 0; i < nn; ++i) {
        wins[i].used = 1;
        strcpy(wins[i].title, names[i]);
        wins[i].z = i;                 /* 后开的盖在前面 */
        wins[i].focused = (i == nn - 1);
    }

    printf("初始状态:\n");
    for (int i = 0; i < nn; ++i)
        printf("  z=%d %-8s %s\n", wins[i].z, wins[i].title, wins[i].focused ? "<- 焦点" : "");

    /* 点击 console 提到最前 */
    int top = 0;
    for (int i = 0; i < nn; ++i) if (wins[i].z > wins[top].z) top = i;
    for (int i = 0; i < nn; ++i) wins[i].focused = (i == top);
    ++wins[top].z;
    for (int i = 0; i < nn; ++i) if (i != top && wins[i].z > 0) --wins[i].z;

    printf("\n点击 console 后:\n");
    for (int i = 0; i < nn; ++i)
        printf("  z=%d %-8s %s\n", wins[i].z, wins[i].title, wins[i].focused ? "<- 焦点" : "");

    printf("\n置顶 = 把自己的 z 设为最大，其余全部 -1；焦点窗口接收键盘。\n");
    return 0;
}
