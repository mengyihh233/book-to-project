/* 用电信号传输 TCP/IP 数据：协议栈逐层封装 */
#include <stdio.h>
#include <string.h>

typedef struct { const char *layer; const char *unit; int header; } Layer;

int main(void) {
    Layer stack[] = {
        {"应用层", "HTTP 消息",   0},
        {"传输层", "TCP 段",     20},
        {"网络层", "IP 数据报",  20},
        {"链路层", "以太网帧",   14},
    };
    int n = sizeof(stack) / sizeof(stack[0]);

    const char *payload = "GET / HTTP/1.1";
    size_t app_len = strlen(payload);
    size_t total = app_len;

    printf("应用数据: \"%s\" (%zu 字节)\n\n向下逐层封装:\n", payload, app_len);
    for (int i = n - 1; i >= 0; --i) {
        total += stack[i].header;
        printf("  %s 加 %2d 字节首部 -> %s，累计 %zu 字节\n",
               stack[i].layer, stack[i].header, stack[i].unit, total);
    }

    printf("\n对端收到后反向拆解，每层剥掉自己那个首部。\n");
    printf("首部里放着给对端同层看的信息: TCP 端口、IP 地址、MAC 地址。\n");
    printf("这就是“分层”的意义: 每层只关心自己的首部，不用管上层内容。\n");
    return 0;
}
