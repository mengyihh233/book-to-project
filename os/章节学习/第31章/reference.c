/* 第31天 写在开发完成之后：回顾 OS 各模块与调用关系 */
#include <stdio.h>

typedef struct { const char *module; const char *job; const char *talks_to; } Mod;

int main(void) {
    Mod mods[] = {
        {"启动区 IPL",    "把内核从磁盘读进内存并跳转",        "BIOS -> 内核"},
        {"GDT/IDT",       "段与中断的描述符表",              "CPU 硬件"},
        {"中断处理",      "响应时钟/键盘/鼠标",              "PIT, 键盘控制器"},
        {"FIFO",          "中断与主循环之间的缓冲",          "中断 -> 任务"},
        {"内存管理",      "分配/释放 4KB 页",                "malloc 调用方"},
        {"图层 sheet",    "窗口叠加与刷新",                  "窗口 -> VRAM"},
        {"多任务",        "上下文切换与调度",                "定时器中断"},
        {"命令行窗口",    "按键 -> 命令解析 -> 执行",        "键盘 -> API"},
        {"文件系统",      "目录项/簇链 -> 字节流",           "磁盘 -> 应用"},
        {"API",           "应用请求系统服务的唯一入口",      "应用 -> 内核"},
    };
    int n = sizeof(mods) / sizeof(mods[0]);

    printf("你写成的这个 OS 的模块清单:\n\n");
    printf("  %-14s %-26s %s\n", "模块", "职责", "与谁对话");
    printf("  %-14s %-26s %s\n", "----", "----", "--------");
    for (int i = 0; i < n; ++i)
        printf("  %-14s %-26s %s\n", mods[i].module, mods[i].job, mods[i].talks_to);

    printf("\n数据流一句话: 磁盘 ->(IPL)-> 内存 ->(GDT/中断)-> CPU ->(图层)-> 屏幕\n");
    printf("           键盘 ->(FIFO)-> 任务 ->(API)-> 应用 ->(文件系统)-> 磁盘\n");
    printf("\n到这里你已经摸过一个真实 OS 的每一层；再读 Linux 源码会清楚得多。\n");
    return 0;
}
