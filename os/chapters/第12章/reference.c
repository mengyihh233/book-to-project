/* 第12天 定时器（1）: PIT 通道编程与计数器 */
#include <stdio.h>
#include <stdint.h>

/* PIT (8254) 控制字: 通道0, 先低后高, 模式2(比率发生器), 二进制 */
#define PIT_CTRL 0x43
#define PIT_CH0  0x40
#define PIT_FREQ 1193182

static uint32_t pit_reload;
static uint64_t ticks;

static void pit_init(uint32_t hz) {
    uint32_t div = PIT_FREQ / hz;
    if (div > 65535) div = 65535;
    pit_reload = div;
    printf("PIT 输入时钟 %d Hz，目标 %u Hz\n", PIT_FREQ, hz);
    printf("  控制字: 0x34 (通道0, 16位, 模式2)\n");
    printf("  重装值: %u (0x%04X) -> 实际 %.2f Hz\n", div, div, (double)PIT_FREQ / div);
    ticks = 0;
}

static void tick(void) {
    ++ticks;
    if (ticks % (uint64_t)(PIT_FREQ / pit_reload) == 0) {
        /* 每秒一次 */
    }
}

int main(void) {
    pit_init(100);      /* 100 Hz，与常见 OS 时钟频率一致 */
    printf("\n模拟 3 秒:\n");
    for (int i = 0; i < 3 * 100; ++i) tick();
    printf("  3 秒共 %llu 次中断\n", (unsigned long long)ticks);
    printf("\n定时器是分时调度的心跳: 每次中断决定是否切换任务。\n");
    return 0;
}
