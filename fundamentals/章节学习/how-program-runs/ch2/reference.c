/* 数据是用二进制数表示的：整数/浮点的位级表示 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static void print_bits(const void *v, size_t n) {
    const uint8_t *b = v;
    for (size_t i = n; i-- > 0;)
        for (int k = 7; k >= 0; --k) putchar((b[i] >> k) & 1 ? '1' : '0');
}

int main(void) {
    int32_t i = -6;
    uint32_t u = 6;
    float f = 6.5f;

    printf("int32 -6  : "); print_bits(&i, 4);
    printf("   （补码: 取反加一）\n");
    printf("uint32 6   : "); print_bits(&u, 4);
    printf("   （原码即补码）\n");
    printf("float 6.5  : "); print_bits(&f, 4);
    printf("   （IEEE754）\n\n");

    printf("拆解 float 6.5:\n");
    printf("  符号位 %d，指数 %d，尾数 %.6f\n",
           (*(uint32_t *)&f) >> 31,
           (int)(((*(uint32_t *)&f) >> 23) & 0xFF) - 127,
           1.0f + (float)((*(uint32_t *)&f) & 0x7FFFFF) / (1 << 23));
    printf("  6.5 = 110.1b = 1.101 x 2^2，指数存 2+127=129\n");
    printf("\n同一个比特序列，按不同类型解释就是不同数值 —— 类型决定含义。\n");
    return 0;
}
