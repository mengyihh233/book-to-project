/* 第30天 高级的应用程序：文本编辑器内核（间隙缓冲） */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CAP 256

/* Gap buffer: 光标前是一段，光标后是一段，中间是空隙 */
typedef struct {
    char buf[CAP];
    int gap_start, gap_end;   /* [gap_start, gap_end) 是空隙 */
    int cursor;
} Gap;

static void gb_init(Gap *g) { g->gap_start = g->cursor = 0; g->gap_end = CAP; }
static void gb_left(Gap *g) {
    if (g->gap_start == 0) return;
    g->buf[--g->gap_end] = g->buf[--g->gap_start];
    --g->cursor;
}
static void gb_right(Gap *g) {
    if (g->gap_end == CAP) return;
    g->buf[g->gap_start++] = g->buf[g->gap_end++];
    ++g->cursor;
}
static void gb_insert(Gap *g, char c) {
    if (g->gap_start >= g->gap_end) return;
    g->buf[g->gap_start++] = c;
    ++g->cursor;
}
static void gb_text(const Gap *g, char *out) {
    memcpy(out, g->buf, g->gap_start);
    memcpy(out + g->gap_start, g->buf + g->gap_end, CAP - g->gap_end);
    out[CAP - (g->gap_end - g->gap_start)] = 0;
}

int main(void) {
    Gap g;
    gb_init(&g);
    const char *s = "hello world";
    for (const char *p = s; *p; ++p) gb_insert(&g, *p);

    /* 光标移到 'o' 与 ' ' 之间（即 hello| world），插入 '!' */
    for (int i = 0; i < 5; ++i) gb_left(&g);
    gb_insert(&g, '!');
    for (int i = 0; i < 5; ++i) gb_right(&g);

    char out[CAP];
    gb_text(&g, out);
    printf("输入:   \"%s\"\n", s);
    printf("光标移到第 5 字符后插入 '!': \"%s\"\n", out);
    printf("\n间隙缓冲让插入/删除都是 O(1)（改边界），代价是移动光标要搬数据。\n");
    printf("真实编辑器（Emacs 等）正是这么做的。\n");
    return 0;
}
