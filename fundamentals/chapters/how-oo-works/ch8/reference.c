/* UML：查看无形软件的工具 —— 用文本画出类图 */
#include <stdio.h>

int main(void) {
    printf("一个订单系统的 UML 类图（文本版）:\n\n");
    printf("  +------------------+        +------------------+\n");
    printf("  |     Customer     |        |      Order       |\n");
    printf("  +------------------+        +------------------+\n");
    printf("  | - name: string   | 1    * | - id: int        |\n");
    printf("  | - email: string  |------->| - total: float   |\n");
    printf("  +------------------+ 下单   +------------------+\n");
    printf("  | + place(): void  |        | + pay(): bool    |\n");
    printf("  +------------------+        +------------------+\n");
    printf("                                     ^\n");
    printf("                                     | 继承\n");
    printf("                            +------------------+\n");
    printf("                            |   OnlineOrder    |\n");
    printf("                            +------------------+\n");
    printf("                            | - url: string    |\n");
    printf("                            +------------------+\n\n");
    printf("UML 三要素: 类名 / 属性与方法 / 关系（关联、继承、依赖）。\n");
    printf("画图的目的不是交差，是把设计里的含糊处逼出来。\n");
    return 0;
}
