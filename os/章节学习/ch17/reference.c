/* 第17天 命令行窗口：行缓冲与命令行解析 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX 128

int main(void) {
    char line[LINE_MAX] = "mem 32 dir  type  file.txt";
    printf("输入行: [%s]\n\n", line);

    printf("按空白切分（多个连续空白算一个）:\n");
    char *save;
    int argc = 0;
    for (char *tok = strtok_r(line, " \t", &save); tok; tok = strtok_r(NULL, " \t", &save)) {
        printf("  argv[%d] = \"%s\"\n", argc++, tok);
    }
    printf("\nargc = %d\n", argc);

    printf("\n命令行窗口 = 一个特殊图层 + 行缓冲 + 按键回显 + 回车分发。\n");
    printf("原书的 console_task 用 FIFO 收按键，遇到 '\\n' 就把整行交给命令解析。\n");
    return 0;
}
