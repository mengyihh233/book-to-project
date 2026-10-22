/* 第1天 从计算机结构到汇编程序入门：模拟 CPU 取指执行与寄存器 */
#include <stdio.h>
#include <string.h>

/* 一个只有 4 个寄存器的迷你 CPU，跑三条指令 */
typedef enum { MOV, ADD, HLT } Op;

typedef struct { Op op; int dst, src; long imm; } Insn;

int main(void) {
    long reg[4] = {0};
    /* 程序: MOV r0, 10 ; ADD r0, 32 ; MOV r1, r0 ; HLT */
    Insn prog[] = {
        {MOV, 0, -1, 10},
        {ADD, 0, -1, 32},
        {MOV, 1, 0, 0},
        {HLT, -1, -1, 0},
    };
    int n = sizeof(prog) / sizeof(prog[0]);

    printf("取指 -> 译码 -> 执行 -> 写回，PC 每次 +1\n\n");
    for (int pc = 0; pc < n; ++pc) {
        Insn in = prog[pc];
        printf("PC=%d  ", pc);
        switch (in.op) {
            case MOV: if (in.src >= 0) reg[in.dst] = reg[in.src]; else reg[in.dst] = in.imm;
                      printf("MOV r%d, %s%d\n", in.dst, in.src >= 0 ? "r" : "#", in.src >= 0 ? in.src : (int)in.imm); break;
            case ADD: reg[in.dst] += in.imm; printf("ADD r%d, #%ld\n", in.dst, in.imm); break;
            case HLT: printf("HLT（停机）\n"); goto done;
        }
        printf("       寄存器: r0=%ld r1=%ld r2=%ld r3=%ld\n", reg[0], reg[1], reg[2], reg[3]);
    }
done:
    printf("\n最终 r0=%ld, r1=%ld —— 验证: 10+32=42, r1 复制了 r0\n", reg[0], reg[1]);
    return 0;
}
