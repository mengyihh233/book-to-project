/* 对程序员来说 CPU 是什么：寄存器与运算的最小模型 */
#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("=== x86 程序员可见的寄存器（32 位） ===\n\n");
    printf("  通用: EAX(累加) EBX(基址) ECX(计数) EDX(数据)\n");
    printf("        ESI(源索引) EDI(目标索引) EBP(帧指针) ESP(栈指针)\n");
    printf("  段:   CS DS ES FS SS\n");
    printf("  标志: EFLAGS(ZF 零 SF 负 OF 溢出 CF 进位)\n\n");

    printf("演示标志位如何产生:\n");
    uint32_t a = 0xFFFFFFFF, b = 2;
    uint32_t r = a + b;
    printf("  %u + %u = %u\n", a, b, r);
    printf("  ZF=%d (结果为零?) SF=%d (最高位为1?) CF=%d (无符号进位?)\n",
           r == 0, (int)(r >> 31), r < a);

    printf("\nCPU 对程序员的意义: 所有高级语言最终都落在这些寄存器和标志上。\n");
    return 0;
}
