/* XML 究竟是什么：按开闭标签逐层解析出一棵树 */
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *xml = "<book><title>C语言入门</title><year>1972</year></book>";
    const char *p = xml;
    int depth = 0;

    printf("文档: %s\n\n解析过程:\n", xml);
    while ((p = strchr(p, '<')) != NULL) {
        int closing = (p[1] == '/');
        char name[32];
        int i = 0;
        p += closing ? 2 : 1;
        while (*p && *p != '>' && i < 31) name[i++] = *p++;
        name[i] = '\0';
        if (*p == '>') ++p;

        if (closing) --depth;
        printf("  %*s<%s> %s\n", depth * 4, "", name, closing ? "结束" : "开始");
        if (!closing) ++depth;
    }
    printf("\nXML 的标签嵌套本质是树；解析就是按开闭标签维护深度。\n");
    return 0;
}
