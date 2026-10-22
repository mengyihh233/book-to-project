// 手动累加 1 到 10，理解“程序只是一串指令”
#include <stdio.h>

int main(void) {
    int sum = 0;
    for (int i = 1; i <= 10; ++i) sum += i;
    printf("1+2+...+10 = %d\n", sum);
    return 0;
}
