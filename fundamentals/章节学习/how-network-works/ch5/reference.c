/* 服务器端的局域网中有什么玄机：防火墙与负载均衡 */
#include <stdio.h>
#include <stdint.h>

/* 模拟: 请求经过防火墙 -> 负载均衡 -> Web 服务器 */
typedef struct { uint32_t src, dst; uint16_t dport; int allowed; } Packet;

static int firewall(const Packet *p) {
    /* 规则: 只放行 80/443，拒绝其余入站 */
    if (p->dport == 80 || p->dport == 443) return 1;
    return 0;
}

int main(void) {
    Packet in[] = {
        {0x0A000001, 0x0A0000FF, 80,  0},
        {0x0A000002, 0x0A0000FF, 443, 0},
        {0x0A000003, 0x0A0000FF, 22,  0},
        {0x0A000004, 0x0A0000FF, 3389, 0},
    };
    int n = sizeof(in) / sizeof(in[0]);

    printf("防火墙规则: 仅放行 80/443 端口\n\n");
    printf("  源地址        目标端口  结果\n");
    for (int i = 0; i < n; ++i) {
        in[i].allowed = firewall(&in[i]);
        printf("  10.0.0.%d      %-6u    %s\n", i + 1, in[i].dport,
               in[i].allowed ? "放行" : "拒绝");
    }

    printf("\n放行的流量再进负载均衡:\n");
    printf("  轮询: 请求1 -> Web1, 请求2 -> Web2, 请求3 -> Web1 ...\n");
    printf("  后端多台 Web 服务器对外表现为一个 IP，扩容对用户透明。\n");
    return 0;
}
