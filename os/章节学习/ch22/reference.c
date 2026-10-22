/* 第22天 用 C 语言编写应用程序：可重定位的独立程序结构 */
#include <stdio.h>
#include <stdint.h>

/* 一个极简的“可加载模块”格式: 头 + 代码 + 重定位表 */
typedef struct {
    char magic[4];       /* "APP1" */
    uint32_t entry;      /* 入口偏移 */
    uint32_t code_size;
    uint32_t reloc_count;
} AppHeader;

int main(void) {
    AppHeader app = {"APP1", 0x10, 64, 3};
    printf("应用文件头:\n");
    printf("  魔数     : %.4s\n", app.magic);
    printf("  入口偏移 : %#x\n", app.entry);
    printf("  代码大小 : %u 字节\n", app.code_size);
    printf("  重定位项 : %u 个\n\n", app.reloc_count);

    printf("加载步骤:\n");
    printf("  1. 读出文件头，校验魔数\n");
    printf("  2. 按 code_size 分配内存，把代码搬进去\n");
    printf("  3. 逐项处理重定位: 把代码里的绝对地址加上实际装载基址\n");
    printf("  4. 跳到 entry 开始执行\n\n");

    uint32_t base = 0x00310000;
    printf("装载基址 %#x，入口实际地址 = %#x\n", base, base + app.entry);
    printf("\n重定位让同一份代码可以加载到任意地址，这是可重定位目标文件的核心。\n");
    return 0;
}
