/* 类库、框架、组件、设计模式：用“策略模式”隔离变化 */
#include <stdio.h>

typedef struct { int (*compare)(int, int); } Sorter;

static int asc(int a, int b) { return a - b; }
static int desc(int a, int b) { return b - a; }

static void sort(int *arr, int n, Sorter s) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (s.compare(arr[j], arr[j + 1]) > 0) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
}

int main(void) {
    int arr[5] = {5, 2, 8, 1, 9};
    printf("原数组: ");
    for (int i = 0; i < 5; ++i) printf("%d ", arr[i]);

    sort(arr, 5, (Sorter){asc});
    printf("\n升序:   ");
    for (int i = 0; i < 5; ++i) printf("%d ", arr[i]);

    sort(arr, 5, (Sorter){desc});
    printf("\n降序:   ");
    for (int i = 0; i < 5; ++i) printf("%d ", arr[i]);

    printf("\n\n排序算法不变，比较规则可插拔 —— 这就是策略模式:\n");
    printf("把“会变的部分”抽成接口，主体逻辑就能复用。\n");
    return 0;
}
