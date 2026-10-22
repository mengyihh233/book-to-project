// 用文件模拟一次“表 + 记录”的存取
#include <stdio.h>

int main(void) {
    FILE *f = fopen("build/fundamentals-record.txt", "w");
    if (!f) { puts("写入失败"); return 1; }
    fprintf(f, "1,张三,92\n2,李四,85\n3,王五,78\n");
    fclose(f);

    int id, score; char name[32];
    f = fopen("build/fundamentals-record.txt", "r");
    if (!f) { puts("读取失败"); return 1; }
    while (fscanf(f, "%d,%31[^,],%d", &id, name, &score) == 3)
        printf("id=%d %s 分数=%d %s\n", id, name, score, score >= 90 ? "优秀" : "");
    fclose(f);
    return 0;
}
