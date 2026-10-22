/* 硬件控制方法：端口 I/O 与 MMIO 的区别 */
#include <stdio.h>
#include <stdint.h>

/* x86 用 in/out 指令访问端口；现代设备多用 MMIO 映射到内存地址 */
static uint8_t ports[65536];
static uint8_t mmio[4096];

static void outb(uint16_t port, uint8_t val) { ports[port] = val; printf("  out %#04x, %#04x\n", port, val); }
static uint8_t inb(uint16_t port) { printf("  in  %#04x -> %#04x\n", port, ports[port]); return ports[port]; }

int main(void) {
    printf("=== 两种硬件访问方式 ===\n\n");
    printf("[端口 I/O] 独立地址空间，用 in/out 指令\n");
    outb(0x43, 0x34);          /* PIT 控制字 */
    outb(0x40, 0x9C);          /* 低字节 */
    outb(0x40, 0x00);          /* 高字节 */
    inb(0x61);                 /* 读键盘状态 */

    printf("\n[MMIO] 设备寄存器映射到物理地址，用普通访存指令\n");
    *(volatile uint32_t *)&mmio[0x100] = 0x1234;
    uint32_t v = *(volatile uint32_t *)&mmio[0x100];
    printf("  写 0x%#x -> 0x100，读回 0x%#x\n", 0x1234u, v);

    printf("\n端口 I/O 需要专门指令，地址空间小；\n");
    printf("MMIO 用普通 load/store，可被缓存与预取，现代设备主流。\n");
    return 0;
}
