/* 程序像河水一样流动着：顺序/分支/循环三种控制流 */
#include <stdio.h>

int main(void) {
    printf("=== 三种基本控制流 ===\n\n");

    /* 顺序流 */
    printf("[顺序流] 一条条往下执行\n");
    int a = 1, b = 2;
    printf("  a=%d b=%d -> a+b=%d\n\n", a, b, a + b);

    /* 分支流 */
    printf("[分支流] 依条件走不同路径\n");
    int score = 75;
    const char *grade = score >= 90 ? "A" : score >= 60 ? "B" : "C";
    printf("  score=%d -> grade=%s\n\n", score, grade);

    /* 循环流 */
    printf("[循环流] 重复执行直到条件不成立\n");
    int sum = 0;
    for (int i = 1; i <= 10; ++i) sum += i;
    printf("  1+2+...+10 = %d\n", sum);

    printf("\nCPU 的 PC（程序计数器）每周期取下一条指令地址；\n");
    printf("跳转指令改写 PC 就形成分支，比较+跳转组合成循环。\n");
    return 0;
}
