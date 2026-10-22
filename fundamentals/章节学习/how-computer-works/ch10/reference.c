// 异或“加密”：对称、同一把钥匙两用
#include <stdio.h>

int main(void) {
    const char plain[] = "HELLO";
    const unsigned char key = 0x5A;
    char cipher[16];
    for (int i = 0; plain[i]; ++i) cipher[i] = plain[i] ^ key;
    cipher[5] = '\0';
    printf("密文十六进制:");
    for (int i = 0; i < 5; ++i) printf(" %02X", (unsigned char)cipher[i]);
    printf("\n再用同一把钥匙解密:");
    for (int i = 0; i < 5; ++i) printf("%c", cipher[i] ^ key);
    printf("\n");
    return 0;
}
