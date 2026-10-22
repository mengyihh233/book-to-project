/* 浏览器生成消息：一次 HTTP 请求的构成 */
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *req =
        "GET /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "User-Agent: MyBrowser/1.0\r\n"
        "Accept: text/html\r\n"
        "\r\n";

    printf("浏览器生成的 HTTP 请求消息:\n\n%s\n", req);
    printf("消息结构:\n");
    printf("  [请求行]  方法 路径 协议版本\n");
    printf("  [首部]    每行 字段名: 值，以 CRLF 结尾\n");
    printf("  [空行]    首部与主体的分界\n");
    printf("  [主体]    GET 通常为空，POST 才有数据\n\n");

    size_t len = strlen(req);
    printf("消息总长 %zu 字节；它将被交给协议栈，逐步封装成:\n", len);
    printf("  TCP 段 -> IP 包 -> 以太网帧 -> 电信号\n");
    return 0;
}
