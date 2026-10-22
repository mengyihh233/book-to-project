/* 第20天 API：系统调用分发表 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef int (*Syscall)(int, int);

static int sys_getkey(int a, int b) { (void)a; (void)b; return 0x1E; }   /* 'a' */
static int sys_putchar(int ch, int b) { (void)b; putchar(ch); return 1; }
static int sys_malloc(int size, int b) { (void)b; return 0x00300000 + size; }
static int sys_exit(int code, int b) { (void)b; printf("[进程退出 %d]\n", code); return code; }

int main(void) {
    Syscall table[16] = {0};
    table[1] = sys_getkey;
    table[2] = sys_putchar;
    table[3] = sys_malloc;
    table[9] = sys_exit;

    printf("系统调用表（edx=功能号, eax/ebx=参数, 返回值在 eax）\n\n");
    printf("  api 1 (getkey)  -> 返回 %d\n", table[1](0, 0));
    printf("  api 2 (putchar) -> ");
    table[2]('H', 0); table[2]('i', 0); putchar('\n');
    printf("  api 3 (malloc)  -> 返回 %#x\n", table[3](4096, 0));
    printf("  api 9 (exit)    -> ");
    table[9](0, 0);

    printf("\n应用程序通过 int 0x40 触发，OS 按功能号查表分发 —— 这就是 API 的本质。\n");
    printf("原书的 _asm_api 用 EDX 传功能号，正是这张表的约定。\n");
    return 0;
}
