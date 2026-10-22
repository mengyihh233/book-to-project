/* 理解 OOP：编程语言的历史 —— 用 C 模拟“类”的雏形 */
#include <stdio.h>
#include <string.h>

/* 没有 class 的语言里，用“结构体 + 函数指针”模拟对象 */
typedef struct Animal {
    char name[16];
    void (*speak)(struct Animal *);
} Animal;

static void dog_speak(Animal *a) { printf("  %s: 汪汪\n", a->name); }
static void cat_speak(Animal *a) { printf("  %s: 喵喵\n", a->name); }

int main(void) {
    Animal dog, cat;
    strcpy(dog.name, "旺财"); dog.speak = dog_speak;
    strcpy(cat.name, "咪咪"); cat.speak = cat_speak;

    printf("同一个接口 speak，不同实现:\n");
    dog.speak(&dog);
    cat.speak(&cat);

    printf("\n这就是多态的雏形: 调用方只认“有个 speak 方法”，\n");
    printf("具体调哪个由对象里存的函数指针决定 —— 面向对象不是新发明，\n");
    printf("而是把这种手法变成了语言内置能力。\n");
    return 0;
}
