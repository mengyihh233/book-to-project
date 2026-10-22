/* 第6天 分割编译与中断处理：模拟中断向量表与中断分发 */
#include <stdio.h>
#include <stdint.h>

#define IDT_SIZE 256

typedef struct { uint16_t offset_low, sel; uint8_t zero, attr; uint16_t offset_high; } Gate;

static Gate idt[IDT_SIZE];
static const char *names[] = {"除零", "调试", "NMI", "断点", "溢出"};

static void set_gate(int vec, void *handler, uint16_t sel) {
    uint32_t addr = (uint32_t)(uintptr_t)handler;
    idt[vec].offset_low = addr & 0xFFFF;
    idt[vec].offset_high = addr >> 16;
    idt[vec].sel = sel;
    idt[vec].attr = 0x8E;      /* 存在, 32 位中断门, DPL=0 */
    idt[vec].zero = 0;
}

static void int_handler(int vec) __attribute__((noinline));
static void int_handler(int vec) {
    printf("  进入中断 %d", vec);
    if (vec < 5) printf(" (%s)", names[vec]);
    printf("，发送 EOI 后返回\n");
}

int main(void) {
    set_gate(0, (void *)int_handler, 0x08);
    set_gate(3, (void *)int_handler, 0x08);
    printf("IDT 已初始化 2 项（其余 254 项指向哑中断）\n\n");
    printf("CPU 收到中断向量号后:\n");
    printf("  1. 压栈 EFLAGS, CS, EIP\n");
    printf("  2. 从 IDT[vec] 取出处理程序地址与选择子\n");
    printf("  3. 跳转执行\n\n触发:\n");
    int_handler(0);
    int_handler(3);
    printf("\n分割编译: 每个中断处理单独一个 .nas/.c，链接时由段属性合并。\n");
    return 0;
}
