/* 第8天 鼠标控制与 32 位模式切换：模拟鼠标数据包解码 */
#include <stdio.h>
#include <stdint.h>

int main(void) {
    /* PS/2 鼠标 3 字节协议 */
    uint8_t pkt[3] = {0x09, 0xFD, 0x03};

    int always_one = (pkt[0] >> 3) & 1;
    int left   = pkt[0] & 1;
    int right  = (pkt[0] >> 1) & 1;
    int middle = (pkt[0] >> 2) & 1;
    int xsign = pkt[0] & 0x10;
    int ysign = pkt[0] & 0x20;

    int dx = pkt[1] - (xsign ? 256 : 0);
    int dy = pkt[2] - (ysign ? 256 : 0);

    printf("原始包: %02X %02X %02X\n", pkt[0], pkt[1], pkt[2]);
    printf("bit3 恒为 1: %d （用于同步，不是 1 就丢弃这个包）\n", always_one);
    printf("按键: 左=%d 右=%d 中=%d\n", left, right, middle);
    printf("X 符号位=%d Y 符号位=%d\n", xsign ? 1 : 0, ysign ? 1 : 0);
    printf("位移: dx=%+d dy=%+d\n", dx, dy);
    printf("\n溢出标志在 bit6/bit7；dx/dy 是 9 位补码，第 9 位存在 byte0 的 bit4/bit5。\n");
    return 0;
}
