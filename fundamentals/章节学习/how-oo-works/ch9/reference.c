/* 建模：填补现实世界和软件之间的沟壑 */
#include <stdio.h>
#include <string.h>

/* 把“现实中的借书”建模成程序里的对象交互 */
typedef struct { const char *title; int available; } Book;
typedef struct { const char *name; int borrowed; } Member;

int main(void) {
    Book book = {"C程序设计语言", 1};
    Member member = {"小明", 0};

    printf("现实世界: 小明去图书馆借《%s》\n\n", book.title);
    printf("建模成对象交互:\n");
    printf("  1. Member.borrow(Book) 被调用\n");
    printf("  2. 检查 Book.available -> %s\n", book.available ? "可借" : "已借出");
    if (book.available && !member.borrowed) {
        book.available = 0;
        member.borrowed = 1;
        printf("  3. 修改状态: Book.available=0, Member.borrowed=1\n");
        printf("  4. 返回成功\n");
    }
    printf("\n建模的关键: 找出名词（对象）与动词（行为），\n");
    printf("再决定哪个动词挂在哪个名词上 —— 职责分配。\n");
    return 0;
}
