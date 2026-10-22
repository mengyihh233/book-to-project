// 用字符长度与类型大小建立最基础的“计算机观”
#include <stdio.h>

int main(void) {
    printf("sizeof(int)    = %zu 字节\n", sizeof(int));
    printf("sizeof(double) = %zu 字节\n", sizeof(double));
    printf("int 最多表示 %d\n", 2147483647);
    printf("double 能表示约 %.1e\n", 1e308);
    return 0;
}
