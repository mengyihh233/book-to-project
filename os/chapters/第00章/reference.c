/* 第0天 着手开发之前：确认工具链与开发环境 */
#include <stdio.h>

int main(void) {
    printf("=== 开发前检查清单 ===\n\n");
    printf("[1] 编译器   : %s\n", __VERSION__);
    printf("[2] 标准     : C%ld\n", __STDC_VERSION__ / 100L);
    printf("[3] 指针大小 : %zu 字节（裸机 32 位下应为 4）\n", sizeof(void *));
    printf("[4] int 大小 : %zu 字节\n", sizeof(int));
    printf("[5] long 大小: %zu 字节\n", sizeof(long));
    printf("\n原书工具链: nasm（汇编）+ gcc/ld（C 与链接）+ make + qemu（模拟器）\n");
    printf("本书代码在 32 位保护模式下运行，指针 4 字节；这里显示的是宿主环境。\n");
    return 0;
}
