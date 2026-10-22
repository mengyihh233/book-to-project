/* 第9天 内存管理：空闲块链表分配器（首次适应） */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NBLK 32

typedef struct { uint32_t addr, size; int free; } Block;

int main(void) {
    Block mem[NBLK];
    int n = 0;
    mem[n++] = (Block){0x00100000, 0x00010000, 1};   /* 128KB 空闲 */

    int request[] = {0x8000, 0x4000, 0x10000, 0x4000, 0x8000};
    int nr = sizeof(request) / sizeof(request[0]);

    printf("初始: 一块 64KB 空闲\n\n");
    for (int i = 0; i < nr; ++i) {
        /* 首次适应: 找第一个足够大的空闲块 */
        int found = -1;
        for (int b = 0; b < n; ++b)
            if (mem[b].free && mem[b].size >= (uint32_t)request[i]) { found = b; break; }
        if (found < 0) { printf("请求 %5d 字节 -> 失败（无足够空闲块）\n", request[i]); continue; }

        Block *blk = &mem[found];
        printf("请求 %5d 字节 -> 从 %#010x 处切分\n", request[i], blk->addr);
        blk->addr += request[i];
        blk->size -= request[i];
        if (blk->size == 0) blk->free = 0;
        /* 记录已分配（简化: 直接打印，不维护完整表） */
    }

    printf("\n剩余空闲:\n");
    for (int b = 0; b < n; ++b)
        if (mem[b].free && mem[b].size) printf("  %#010x  大小 %#x\n", mem[b].addr, mem[b].size);
    printf("\n首次适应简单但易留下小碎片；原书用 0x1000 为单位的管理表。\n");
    return 0;
}
