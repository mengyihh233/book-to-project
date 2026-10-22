// TCP/IP 分层理解：把一次请求拆成封装与拆解
#include <stdio.h>

int main(void) {
    const char *msg = "GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";
    printf("应用层数据长度 = %zu 字节\n", sizeof("GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n") - 1);
    printf("向下每加一层就加一个首部：TCP → IP → 以太网帧\n");
    printf("对端收到后逐层拆解，把负载交回应用层\n");
    for (int layer = 4; layer >= 1; --layer)
        printf("第 %d 层%s\n", layer, (layer == 4 ? " 应用" : layer == 3 ? " 传输" : layer == 2 ? " 网络" : " 链路"));
    (void)msg;
    return 0;
}
