// 观察变量在内存中的地址与布局
#include <stdio.h>

int main(void) {
    int a = 42;
    double b = 3.1415926;
    char c = 'A';
    printf("&a=%p size=%zu\n", (void *)&a, sizeof a);
    printf("&b=%p size=%zu\n", (void *)&b, sizeof b);
    printf("&c=%p size=%zu\n", (void *)&c, sizeof c);
    printf("相邻整数差 = %zu 字节\n", (size_t)((char *)(&b) - (char *)(&a)));
    return 0;
}
