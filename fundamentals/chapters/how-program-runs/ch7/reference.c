/* 程序是在何种环境中运行的：从源码到运行的全链路 */
#include <stdio.h>

int main(void) {
    printf("hello.c 到运行，中间发生的事:\n\n");
    printf("  [1] 预处理  gcc -E    展开 #include / #define -> hello.i\n");
    printf("  [2] 编译    gcc -S    生成汇编              -> hello.s\n");
    printf("  [3] 汇编    gcc -c    汇编 -> 机器码目标文件  -> hello.o\n");
    printf("  [4] 链接    gcc       合并 .o 与库，解析符号 -> hello.exe\n");
    printf("  [5] 装载    操作系统  读文件、建进程、映射段、跳入口\n");
    printf("  [6] 运行    CPU       取指执行，动态库按需加载\n\n");

    printf("关键事实:\n");
    printf("  - .o 里地址很多还是 0 或相对值，链接时才确定\n");
    printf("  - 可执行文件分 .text .data .bss，装载时分别映射\n");
    printf("  - 动态链接把库函数留到运行时解析，省内存但启动稍慢\n\n");
    printf("掌握这条链，遇到“undefined reference”才知道去查第 4 步。\n");
    return 0;
}
