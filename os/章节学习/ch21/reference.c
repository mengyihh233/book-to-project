/* 第21天 保护操作系统：段级权限与 RPL 检查 */
#include <stdio.h>
#include <stdint.h>

/* 选择子: bit0-1=RPL, bit2=TI(0=GDT 1=LDT), bit3-15=索引 */
static uint16_t make_selector(int index, int ti, int rpl) {
    return (uint16_t)((index << 3) | (ti << 2) | rpl);
}
static void decode(uint16_t sel) {
    printf("  选择子 %#06x -> 索引 %d, %s, RPL=%d\n", sel, sel >> 3,
           (sel >> 2) & 1 ? "LDT" : "GDT", sel & 3);
}

int main(void) {
    printf("GDT 布局: 0=空 1=代码段(内核) 2=数据段(内核) 3=代码段(应用) 4=数据段(应用)\n\n");

    uint16_t kernel_cs = make_selector(1, 0, 0);
    uint16_t app_cs    = make_selector(3, 0, 3);

    printf("内核代码段选择子: %#06x\n", kernel_cs); decode(kernel_cs);
    printf("应用代码段选择子: %#06x\n", app_cs);    decode(app_cs);

    printf("\n权限检查（CPL <= DPL 且 RPL <= DPL 才允许访问）:\n");
    int cpl = 3;   /* 应用层 CPL=3 */
    int dpl_kernel = 0, dpl_app = 3;
    printf("  应用(CPL=%d) 访问内核段(DPL=%d): %s\n", cpl, dpl_kernel,
           cpl <= dpl_kernel ? "允许" : "拒绝");
    printf("  应用(CPL=%d) 访问应用段(DPL=%d): %s\n", cpl, dpl_app,
           cpl <= dpl_app ? "允许" : "拒绝");

    printf("\n结论: 用户程序碰不到内核段，越界访问触发 #GP 中断 —— 这就是“保护”。\n");
    return 0;
}
