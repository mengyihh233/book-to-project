/* 第15天 多任务（1）: 任务上下文的结构（寄存器集合） */
#include <stdio.h>
#include <stdint.h>

/* x86 任务切换要保存的寄存器（原书的 TSS32 / 手动切换） */
typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi;
    uint32_t ebp, esp, eip;
    uint16_t cs, ds, es, fs, gs, ss;
    uint32_t eflags;
} Context;

static void show(const char *tag, const Context *c) {
    printf("  %-10s eax=%08x ebx=%08x eip=%08x esp=%08x\n",
           tag, c->eax, c->ebx, c->eip, c->esp);
}

int main(void) {
    Context taskA = {.eax = 1, .ebx = 10, .eip = 0x1000, .esp = 0x8000, .eflags = 0x202};
    Context taskB = {.eax = 2, .ebx = 20, .eip = 0x2000, .esp = 0x9000, .eflags = 0x202};

    printf("两个任务的上下文:\n");
    show("任务A", &taskA);
    show("任务B", &taskB);

    printf("\n切换 A -> B:\n");
    Context saved = taskA;              /* 保存 A 的全部寄存器 */
    printf("  1. 保存 A 的现场（%zu 字节）\n", sizeof(Context));
    printf("  2. 恢复 B 的现场\n");
    printf("  3. 跳转到 B 的 eip=%#x\n", taskB.eip);

    printf("\n再切回 A -> B:\n");
    printf("  从 saved 恢复: eax=%08x eip=%#x（A 停在哪就回到哪）\n", saved.eax, saved.eip);
    printf("\n抢占式多任务的关键: 定时器中断里做这件事，任务本身无感知。\n");
    return 0;
}
