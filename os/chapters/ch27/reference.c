/* 第27天 LDT 与库：局部描述符表与动态链接模拟 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* 简化 ELF: 符号表 + 重定位，实现“运行时解析外部符号” */
typedef struct { const char *name; uint32_t addr; } Sym;

static uint32_t base = 0x00400000;
static uint32_t next_addr(void) { return base += 0x100; }

static Sym libsyms[4] = {
    {"printf", 0x00101000},
    {"malloc", 0x00102000},
    {"api_putchar", 0x00103000},
    {NULL, 0}
};

static uint32_t resolve(const char *name) {
    for (int i = 0; libsyms[i].name; ++i)
        if (strcmp(libsyms[i].name, name) == 0) return libsyms[i].addr;
    printf("  [错误] 未解析符号: %s\n", name);
    return 0;
}

int main(void) {
    /* 应用里引用了两个外部符号 */
    const char *undef[] = {"api_putchar", "printf", "malloc"};
    printf("应用的未定义符号与解析结果:\n");
    for (unsigned i = 0; i < sizeof(undef) / sizeof(undef[0]); ++i)
        printf("  %-14s -> %#x\n", undef[i], resolve(undef[i]));

    printf("\n应用入口地址: %#x\n", next_addr());
    printf("\nLDT 让每个任务有自己的段（局部内存）；\n");
    printf("动态链接把“外部符号”留到运行时按名字查找 —— 库才能被共享。\n");
    return 0;
}
