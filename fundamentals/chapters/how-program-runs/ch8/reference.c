/* 从源文件到可执行文件：目标文件的三段与符号 */
#include <stdio.h>
#include <stdint.h>

/* 模拟目标文件的段布局与符号表 */
typedef struct { const char *name; uint32_t addr; int is_def; } Sym;

int main(void) {
    printf("hello.o 的段（简化）:\n\n");
    printf("  .text  代码段   0x0000  已初始化的数据与指令\n");
    printf("  .data  数据段   0x1000  已初始化的全局/静态变量\n");
    printf("  .bss   BSS 段   0x2000  未初始化，装载时清零，不占文件空间\n\n");

    printf("符号表:\n");
    Sym syms[] = {
        {"main",      0x0000, 1},
        {"printf",    0x0000, 0},   /* 未定义，等待链接 */
        {"greeting",  0x1000, 1},
        {"counter",   0x2000, 1},
    };
    for (unsigned i = 0; i < sizeof(syms) / sizeof(syms[0]); ++i)
        printf("  %-10s 地址 %#06x %s\n", syms[i].name, syms[i].addr,
               syms[i].is_def ? "已定义" : "未定义（外部）");

    printf("\n链接器做两件事:\n");
    printf("  1. 合并多个 .o 的同名段，重新分配地址\n");
    printf("  2. 把未定义符号（如 printf）在库里找到并填地址\n\n");
    printf(".bss 不占文件体积，所以大的未初始化数组几乎不增加可执行文件大小。\n");
    return 0;
}
