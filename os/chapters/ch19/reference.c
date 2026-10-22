/* 第19天 应用程序：一个极简字节码虚拟机（模拟加载执行 app） */
#include <stdio.h>
#include <stdint.h>

typedef enum { PUSH, ADD, MUL, PRINT, HALT } Op;

int main(void) {
    /* 程序: push 6 ; push 7 ; add ; push 6 ; mul ; print ; halt  => (6+7)*6 */
    uint8_t code[] = {PUSH, 6, PUSH, 7, ADD, PUSH, 6, MUL, PRINT, HALT};
    int stack[64], sp = 0;
    int pc = 0, guard = 0;

    printf("字节码程序（计算 (6+7)*6）:\n  ");
    for (unsigned i = 0; i < sizeof(code); ++i) printf("%02X ", code[i]);
    printf("\n\n执行:\n");

    while (pc < (int)sizeof(code) && guard++ < 100) {
        Op op = code[pc++];
        switch (op) {
            case PUSH: printf("  PUSH %d\n", code[pc]); stack[sp++] = code[pc++]; break;
            case ADD: { int b = stack[--sp], a = stack[--sp]; stack[sp++] = a + b;
                        printf("  ADD  -> %d\n", stack[sp-1]); break; }
            case MUL: { int b = stack[--sp], a = stack[--sp]; stack[sp++] = a * b;
                        printf("  MUL  -> %d\n", stack[sp-1]); break; }
            case PRINT: printf("  PRINT -> 栈顶 = %d\n", stack[sp-1]); break;
            case HALT: printf("  HALT\n"); goto done;
        }
    }
done:
    printf("\n结果: %d   （验证: (6+7)*6 = %d）\n", stack[sp-1], (6 + 7) * 6);
    printf("\nOS 加载应用程序的本质: 把字节码/机器码读进内存，交给一个执行循环。\n");
    return 0;
}
