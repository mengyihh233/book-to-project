/* 衍生：敏捷开发和 TDD —— 先写测试再写实现 */
#include <stdio.h>

/* TDD: 先写测试（会失败），再写实现让测试通过 */
static int add(int a, int b) { return a + b; }        /* 后写的实现 */
static int divide(int a, int b) { return b ? a / b : 0; }

static int tests_run = 0, tests_failed = 0;

static void check(const char *name, int got, int want) {
    ++tests_run;
    if (got == want) printf("  PASS %s\n", name);
    else { ++tests_failed; printf("  FAIL %s: 期望 %d 实际 %d\n", name, want, got); }
}

int main(void) {
    printf("红 -> 绿 -> 重构 一轮:\n\n");
    printf("[红] 先写测试（此时还没有实现，全部失败）\n");
    check("add(2,3)==5", 0, 5);          /* 故意用 0 演示失败 */

    printf("\n[绿] 写最简单实现让测试通过\n");
    check("add(2,3)==5", add(2, 3), 5);
    check("add(-1,1)==0", add(-1, 1), 0);
    check("divide(10,2)==5", divide(10, 2), 5);

    printf("\n结果: %d 个测试，%d 个失败\n", tests_run, tests_failed);
    printf("\nTDD 的价值不在测试本身，而在“每次只前进一步”的节奏。\n");
    return 0;
}
