/* 第18天 dir 命令：解析 FAT 目录项 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* FAT 目录项 32 字节 */
typedef struct {
    char name[8];       /* 8.3 文件名 */
    char ext[3];
    uint8_t attr;
    uint8_t reserved[10];
    uint16_t time, date;
    uint16_t cluster;
    uint32_t size;
} __attribute__((packed)) DirEntry;

static void print_entry(const DirEntry *e) {
    if (e->name[0] == 0x00) { printf("  (后续无条目)\n"); return; }
    if ((uint8_t)e->name[0] == 0xE5) { printf("  (已删除条目)\n"); return; }

    char nm[13] = {0};
    memcpy(nm, e->name, 8);
    int p = 7; while (p > 0 && nm[p] == ' ') nm[p--] = 0;
    if (e->ext[0] != ' ') {
        strcat(nm, ".");
        strncat(nm, e->ext, 3);
    }
    int q = (int)strlen(nm) - 1;
    while (q > 0 && nm[q] == ' ') nm[q--] = 0;

    printf("  %-14s 属性=%02X 首簇=%5u 大小=%6u 字节", nm, e->attr, e->cluster, e->size);
    printf("  [%s%s%s%s]\n",
           (e->attr & 0x01) ? "只读 " : "",
           (e->attr & 0x02) ? "隐藏 " : "",
           (e->attr & 0x10) ? "目录 " : "",
           (e->attr & 0x20) ? "归档" : "");
}

int main(void) {
    DirEntry dir[5] = {0};
    memcpy(dir[0].name, "KERNEL  SYS", 11); dir[0].attr = 0x20; dir[0].cluster = 2; dir[0].size = 72000;
    memcpy(dir[1].name, "HARIBOTE ", 8); memcpy(dir[1].ext, "OS ", 3); dir[1].attr = 0x20; dir[1].cluster = 5; dir[1].size = 1024;
    dir[1].name[0] = (char)0xE5;   /* 已删除 */
    memcpy(dir[2].name, "EISBOOK  ", 8); memcpy(dir[2].ext, "TXT", 3); dir[2].attr = 0x20; dir[2].cluster = 9; dir[2].size = 356;
    memcpy(dir[3].name, "MYDIR    ", 8); memcpy(dir[3].ext, "   ", 3); dir[3].attr = 0x10; dir[3].cluster = 12; dir[3].size = 0;
    dir[4].name[0] = 0x00;

    printf("FAT 根目录前 5 个 32 字节条目:\n");
    for (int i = 0; i < 5; ++i) print_entry(&dir[i]);
    printf("\ndir 命令就是遍历目录区，跳过 0xE5 与 0x00，按 8.3 格式拼出文件名。\n");
    return 0;
}
