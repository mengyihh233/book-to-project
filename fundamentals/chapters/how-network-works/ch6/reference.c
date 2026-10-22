/* 请求到达 Web 服务器，响应返回浏览器：一次完整往返 */
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void) {
    printf("一次 Web 请求的完整时间线（浏览器视角）:\n\n");
    struct { double t; const char *what; } steps[] = {
        {0.0,  "用户在地址栏输入网址并回车"},
        {0.5,  "DNS 查询: 域名 -> IP（可能命中缓存，也可能递归查询）"},
        {1.0,  "TCP 三次握手: SYN -> SYN/ACK -> ACK"},
        {2.0,  "TLS 握手（HTTPS）: 交换证书与密钥"},
        {4.0,  "发送 HTTP 请求"},
        {20.0, "服务器处理，返回 HTTP 响应"},
        {21.0, "浏览器解析 HTML，发现 CSS/JS/图片后并行发起额外请求"},
        {80.0, "页面渲染完成"},
    };
    int n = sizeof(steps) / sizeof(steps[0]);

    for (int i = 0; i < n; ++i)
        printf("  %5.0f ms  %s\n", steps[i].t, steps[i].what);

    printf("\nDNS + 握手占了前 4ms 却决定“感觉快不快”；\n");
    printf("首字节时间(TTFB) 20ms 里，网络往返可能只占几毫秒，其余是服务器计算。\n");
    printf("优化优先级: 减少请求数 > 用 CDN/缓存缩短距离 > 压缩体积。\n");
    return 0;
}
