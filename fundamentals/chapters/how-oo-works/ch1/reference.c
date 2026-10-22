// 对象、成员变量与成员函数：先建立 OOP 的运行期直觉
#include <stdio.h>

struct Counter {
    int value;                  // 成员变量
    void (*add)(struct Counter *, int);  // 成员函数指针
};

static void counter_add(struct Counter *c, int n) { c->value += n; }

int main(void) {
    struct Counter c = {0, counter_add};
    c.add(&c, 5);
    c.add(&c, 37);
    printf("value = %d\n", c.value);
    return 0;
}
