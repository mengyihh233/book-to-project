/* 操作系统和应用的关系：系统调用是唯一的桥 */
#include <stdio.h>
#include <stdint.h>

/* 模拟: 用户态无法直接访问硬件，必须通过系统调用陷入内核 */
typedef enum { USER, KERNEL } Mode;

static Mode mode = USER;

static long syscall(int num, long arg) {
    printf("  int 0x80 -> 陷入内核（模式 USER -> KERNEL）\n");
    mode = KERNEL;
    long r = (num == 1) ? (long)putchar((int)arg) : (num == 4) ? 0 : -1;
    printf("  syscall %d 返回 %ld，iret 回到用户态（KERNEL -> USER）\n", num, r);
    mode = USER;
    return r;
}

int main(void) {
    printf("当前模式: %s\n\n", mode == USER ? "USER（用户态）" : "KERNEL（内核态）");

    printf("应用想写一个字符 'A':\n");
    syscall(4, 'A');
    putchar('\n');

    printf("\n为什么需要这层桥:\n");
    printf("  - 用户态代码访问硬件会触发异常，保护系统稳定\n");
    printf("  - 内核统一管理文件/进程/内存，避免应用互相破坏\n");
    printf("  - 系统调用是应用请求内核服务的唯一入口\n\n");
    printf("性能代价: 每次调用都有模式切换开销，所以频繁小系统调用是性能杀手。\n");
    return 0;
}
