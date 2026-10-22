/* 第28天 文件操作与文字显示：文件系统读 + 控制台输出 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* 模拟: 文件内容存在内存里，读出后逐字节送显存 */
static const char file_content[] = "Hello, OS!\nSecond line\n";

int main(void) {
    const char *path = "eisbook.txt";
    printf("打开文件: %s\n", path);

    /* 模拟 FAT: 目录项 -> 首簇 -> 簇链 -> 数据 */
    uint16_t cluster = 9;
    printf("  目录项首簇 = %u\n", cluster);
    printf("  簇大小 = 512 字节，文件跨 %zu 簇\n", (strlen(file_content) + 511) / 512);

    printf("\n读出内容并逐字节显示:\n  ");
    for (const char *p = file_content; *p; ++p) {
        putchar(*p);
        if (*p == '\n') printf("  ");
    }
    printf("\n共 %zu 字节\n", strlen(file_content));

    printf("\n文件读 = 目录项 -> 簇链 -> 拼出连续字节流；\n");
    printf("文字显示 = 查字模 -> 写 VRAM。两者独立，可任意组合。\n");
    return 0;
}
