/* 第29天 压缩与简单的应用程序：RLE 行程编码 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/* RLE: (count, byte) 对，count 用 1 字节，最多 255 */
static size_t rle_compress(const uint8_t *in, size_t n, uint8_t *out) {
    size_t o = 0;
    for (size_t i = 0; i < n; ) {
        uint8_t c = in[i];
        size_t run = 1;
        while (i + run < n && in[i + run] == c && run < 255) ++run;
        out[o++] = (uint8_t)run;
        out[o++] = c;
        i += run;
    }
    return o;
}

static size_t rle_decompress(const uint8_t *in, size_t n, uint8_t *out) {
    size_t o = 0;
    for (size_t i = 0; i + 1 < n; i += 2) {
        uint8_t run = in[i], c = in[i + 1];
        for (int k = 0; k < run; ++k) out[o++] = c;
    }
    return o;
}

int main(void) {
    /* 高度可压缩的数据: 大块同色 */
    uint8_t data[512];
    for (int i = 0; i < 256; ++i) data[i] = 0x0C;
    for (int i = 256; i < 400; ++i) data[i] = 0x02;
    for (int i = 400; i < 512; ++i) data[i] = 0x0F;
    size_t n = sizeof(data);

    uint8_t comp[2048], back[2048];
    size_t cn = rle_compress(data, n, comp);
    size_t bn = rle_decompress(comp, cn, back);

    printf("原始: %zu 字节\n压缩: %zu 字节 (%.1f%%)\n解压: %zu 字节\n",
           n, cn, 100.0 * cn / n, bn);
    printf("往返一致: %s\n", (bn == n && memcmp(data, back, n) == 0) ? "是" : "否");

    printf("\n压缩比取决于重复度；对随机数据 RLE 反而会变大（每字节配一个计数）。\n");
    printf("原书用 RLE 把启动画面和字体数据压小，换启动时的解压时间。\n");
    return 0;
}
