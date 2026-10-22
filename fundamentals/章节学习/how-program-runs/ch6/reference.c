/* 亲自尝试压缩数据：RLE 与霍夫曼思想对比 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/* RLE: 适合大量重复；霍夫曼: 适合频率不均 */
static size_t rle(const uint8_t *in, size_t n, uint8_t *out) {
    size_t o = 0;
    for (size_t i = 0; i < n; ) {
        uint8_t c = in[i];
        size_t run = 1;
        while (i + run < n && in[i + run] == c && run < 255) ++run;
        out[o++] = (uint8_t)run; out[o++] = c;
        i += run;
    }
    return o;
}

/* 统计字符频率，估算霍夫曼的理论收益 */
static void huffman_gain(const char *s) {
    int freq[256] = {0};
    size_t n = strlen(s);
    for (size_t i = 0; i < n; ++i) freq[(uint8_t)s[i]]++;
    double fixed = n * 8.0, huff = 0.0;
    for (int c = 0; c < 256; ++c)
        if (freq[c]) huff += freq[c] * (double)(-log((double)freq[c] / n) / log(2.0));
    printf("定长编码: %.0f 位\n霍夫曼理论: %.0f 位 (压缩到 %.0f%%)\n",
           fixed, huff, 100.0 * huff / fixed);
}

int main(void) {
    uint8_t data[64];
    for (int i = 0; i < 32; ++i) data[i] = 0x41;
    for (int i = 32; i < 48; ++i) data[i] = 0x42;
    for (int i = 48; i < 64; ++i) data[i] = 0x43;

    uint8_t comp[256];
    size_t cn = rle(data, 64, comp);
    printf("RLE: 64 字节 -> %zu 字节 (%.0f%%)\n\n", cn, 100.0 * cn / 64);

    const char *text = "aaabbbcccccddddd";
    printf("文本 \"%s\":\n", text);
    huffman_gain(text);

    printf("\nRLE 抓“连续重复”，霍夫曼抓“频率不均”，两者可组合使用。\n");
    return 0;
}
