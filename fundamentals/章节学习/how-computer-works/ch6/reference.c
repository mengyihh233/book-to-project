// 顺序栈实现，理解“栈”只是数组加一个指针
#include <stdio.h>

#define N 16
static int data[N];
static int top = -1;

static void push(int v) { if (top < N - 1) data[++top] = v; }
static int pop(void) { return top >= 0 ? data[top--] : -1; }

int main(void) {
    for (int i = 1; i <= 5; ++i) push(i * i);
    while (top >= 0) printf("%d ", pop());
    printf("\n");
    return 0;
}
