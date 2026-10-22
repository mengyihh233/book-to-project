/* 第3天 进入 32 位模式：GDT 段描述符的位域打包 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* 段描述符 8 字节布局（段上限 20 位 + 基址 32 位 + 属性 12 位） */
typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  limit_high_and_flags;
    uint8_t  base_high;
} __attribute__((packed)) SegDesc;

int main(void) {
    /* 代码段: 基址 0, 上限 4GB, 可执行可读 */
    SegDesc code = {
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_mid = 0,
        .access = 0x9A,          /* P=1 DPL=0 S=1 Type=1010(代码,可读) */
        .limit_high_and_flags = 0xCF,  /* G=1 D/B=1 上限高4位=0xF */
        .base_high = 0
    };
    /* 数据段: 基址 0, 上限 4GB, 可写 */
    SegDesc data = {
        .limit_low = 0xFFFF, .base_low = 0, .base_mid = 0,
        .access = 0x92,          /* Type=0010(数据,可写) */
        .limit_high_and_flags = 0xCF, .base_high = 0
    };

    uint64_t cw, dw;
    memcpy(&cw, &code, 8);
    memcpy(&dw, &data, 8);

    printf("代码段描述符: %016llx\n", (unsigned long long)cw);
    printf("数据段描述符: %016llx\n", (unsigned long long)dw);

    /* 解回来验证 */
    uint32_t base = (uint32_t)code.base_low | ((uint32_t)code.base_mid << 16) | ((uint32_t)code.base_high << 24);
    uint32_t limit = (uint32_t)code.limit_low | ((uint32_t)(code.limit_high_and_flags & 0x0F) << 16);
    limit = (limit << 12) | 0xFFF;   /* G=1 时上限按 4KB 粒度 */
    printf("\n解码验证: 基址=%#x 上限=%#x (%u GB)\n", base, limit, limit / 1024 / 1024 / 1024 + 1);
    printf("\naccess 0x9A = 1001 1010: P=1 DPL=0 S=1 Type=代码可读\n");
    printf("G=1 让 20 位上限按 4KB 粒度算，4GB 内存一段全覆盖。\n");
    return 0;
}
