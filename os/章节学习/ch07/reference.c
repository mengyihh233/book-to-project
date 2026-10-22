/* 第7天 FIFO 与鼠标控制：环形缓冲队列（中断与主循环间的桥梁） */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CAP 32

typedef struct {
    uint8_t buf[CAP];
    int head, tail, count;
} FIFO;

static void fifo_init(FIFO *f) { memset(f, 0, sizeof(*f)); }
static int fifo_put(FIFO *f, uint8_t v) {
    if (f->count >= CAP) return 0;
    f->buf[f->tail] = v;
    f->tail = (f->tail + 1) % CAP;
    ++f->count;
    return 1;
}
static int fifo_get(FIFO *f, uint8_t *v) {
    if (f->count == 0) return 0;
    *v = f->buf[f->head];
    f->head = (f->head + 1) % CAP;
    --f->count;
    return 1;
}

int main(void) {
    FIFO f;
    fifo_init(&f);

    printf("模拟鼠标中断: 每 3 字节一个数据包\n");
    uint8_t packets[3][3] = {{0x08, 0x02, 0x00}, {0x08, 0xFE, 0xFF}, {0x09, 0x01, 0x00}};
    for (int i = 0; i < 3; ++i)
        for (int k = 0; k < 3; ++k) {
            if (!fifo_put(&f, packets[i][k])) printf("  队列满，丢弃!\n");
        }
    printf("入队后队列长度: %d\n\n", f.count);

    printf("主循环按 3 字节一组解码:\n");
    uint8_t v;
    while (f.count >= 3) {
        fifo_get(&f, &v); int state = v;
        fifo_get(&f, &v); int dx = (int8_t)v;
        fifo_get(&f, &v); int dy = (int8_t)v;
        printf("  state=%#04x dx=%+d dy=%+d  左键=%d\n",
               state, dx, dy, state & 1);
    }
    printf("\n环形缓冲让中断处理只管入队，解码放在主循环，两者不互相阻塞。\n");
    return 0;
}
