/* 第16天 多任务（2）: 轮转调度 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NTASK 4

typedef struct {
    int id;
    uint32_t esp, eip;
    int state;          /* 0 就绪 1 运行 2 睡眠 */
    int sleep_until;
} Task;

static Task tasks[NTASK];
static int current = -1;
static uint32_t clocktick;

static int next_ready(void) {
    for (int k = 1; k <= NTASK; ++k) {
        int i = (current + k) % NTASK;
        if (tasks[i].state == 0) return i;
    }
    return current;
}

int main(void) {
    for (int i = 0; i < NTASK; ++i) {
        tasks[i].id = i;
        tasks[i].eip = 0x1000 + i * 0x100;
        tasks[i].state = 0;
    }
    printf("4 个任务轮转调度，每 tick 切换一次:\n\n");
    for (clocktick = 1; clocktick <= 10; ++clocktick) {
        int prev = current;
        current = next_ready();
        printf("  tick %2u: 运行任务 %d (eip=%#x)\n", clocktick, tasks[current].id, tasks[current].eip);
        if (clocktick == 4) { tasks[2].state = 2; printf("           -> 任务 2 进入睡眠\n"); }
        if (clocktick == 8) { tasks[2].state = 0; printf("           -> 任务 2 被唤醒\n"); }
        (void)prev;
    }
    printf("\n轮转 = 就绪队列里转一圈，每人一个时间片；睡眠的任务被跳过。\n");
    return 0;
}
