/* 函数式语言是怎样工作的：不可变数据与高阶函数 */
#include <stdio.h>
#include <stdlib.h>

/* map: 对每个元素应用函数，返回新数组（不改原数组） */
static int *map(const int *src, int n, int (*f)(int)) {
    int *out = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) out[i] = f(src[i]);
    return out;
}
static int *filter(const int *src, int n, int (*pred)(int), int *outn) {
    int *out = malloc(sizeof(int) * n);
    int k = 0;
    for (int i = 0; i < n; ++i) if (pred(src[i])) out[k++] = src[i];
    *outn = k;
    return out;
}

static int square(int x) { return x * x; }
static int is_even(int x) { return x % 2 == 0; }

int main(void) {
    int src[6] = {1, 2, 3, 4, 5, 6};
    printf("原数组（不可变）: ");
    for (int i = 0; i < 6; ++i) printf("%d ", src[i]);

    int *sq = map(src, 6, square);
    printf("\nmap(square):    ");
    for (int i = 0; i < 6; ++i) printf("%d ", sq[i]);

    int m;
    int *ev = filter(src, 6, is_even, &m);
    printf("\nfilter(is_even): ");
    for (int i = 0; i < m; ++i) printf("%d ", ev[i]);

    printf("\n\n函数式三要素在这段代码里都有: 函数当参数、不改原数据、返回新集合。\n");
    printf("不可变让并发与调试都简单得多 —— 这是它回流的根本原因。\n");
    free(sq); free(ev);
    return 0;
}
