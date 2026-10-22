/* 第13天 定时器（2）: 多定时器超时管理 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NTIMER 16

typedef struct { int used; uint32_t timeout; void (*cb)(void); } Timer;

static Timer timers[NTIMER];
static uint32_t now;

static int timer_alloc(void) {
    for (int i = 0; i < NTIMER; ++i)
        if (!timers[i].used) { timers[i].used = 1; return i; }
    return -1;
}

static void cb_a(void) { printf("    [t=%u] 定时器 A 触发\n", now); }
static void cb_b(void) { printf("    [t=%u] 定时器 B 触发\n", now); }

int main(void) {
    int a = timer_alloc(); timers[a].timeout = 50; timers[a].cb = cb_a;
    int b = timer_alloc(); timers[b].timeout = 120; timers[b].cb = cb_b;

    printf("注册: A 50ms 后触发, B 120ms 后触发\n\n推进时钟:\n");
    for (now = 1; now <= 150; ++now) {
        for (int i = 0; i < NTIMER; ++i)
            if (timers[i].used && now >= timers[i].timeout) {
                timers[i].cb();
                timers[i].used = 0;
            }
    }
    printf("\n每个定时器一个超时时刻，时钟推进时逐项比对，到点就回调并注销。\n");
    return 0;
}
