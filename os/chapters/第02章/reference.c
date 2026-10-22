/* 第2天 汇编语言与 Makefile 入门：模拟 make 的依赖解析 */
#include <stdio.h>
#include <string.h>

typedef struct { const char *target; const char *dep; const char *cmd; } Rule;

int main(void) {
    /* 对应原书的 Makefile 依赖关系 */
    Rule rules[] = {
        {"hello.sys", "asmhead.bin bootpack.hrb", "copy /b asmhead.bin+bootpack.hrb hello.sys"},
        {"bootpack.hrb", "bootpack.bim", "bim2hrb bootpack.bim bootpack.hrb 0"},
        {"bootpack.bim", "bootpack.obj naskfunc.obj", "obj2bim bootpack.obj naskfunc.obj"},
        {"bootpack.obj", "bootpack.c", "gcc -c bootpack.c"},
        {"naskfunc.obj", "naskfunc.nas", "nasm naskfunc.nas"},
        {"asmhead.bin", "asmhead.nas", "nasm asmhead.nas"},
    };
    int n = sizeof(rules) / sizeof(rules[0]);

    const char *goal = "hello.sys";
    printf("目标: %s\n\n递归展开依赖（后序执行命令）:\n", goal);
    /* 简单后序: 从最终目标反向找链 */
    int done[8] = {0};
    for (int round = 0; round < n; ++round)
        for (int i = 0; i < n; ++i) {
            if (done[i]) continue;
            if (strstr(rules[i].target, goal) || strstr(rules[i].dep, goal)) {
                printf("  [%d] %s <- %s\n      $ %s\n", i, rules[i].target, rules[i].dep, rules[i].cmd);
                done[i] = 1;
                goal = rules[i].target;
            }
        }
    printf("\nmake 的核心: 按依赖图后序执行，只重建比目标旧的文件。\n");
    return 0;
}
