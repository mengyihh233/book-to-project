# 在 Ubuntu 桌面里使用学习工作台

2026-10-21 已修正。KDE 桌面和应用菜单现在都有 **学习工作台（Ubuntu浏览器）**。点这个入口会使用 Ubuntu 内的 Google Chrome，留在 Ubuntu 图形会话里，不再调用 Windows 浏览器。

## 之前为什么会跳到 Windows

原桌面快捷方式明确写了 `/mnt/c/Windows/explorer.exe http://127.0.0.1:18765`。`explorer.exe` 是 Windows 程序，因此网址由 Windows 默认浏览器打开。那是之前配置的入口行为，这次已替换。

另外，迁移来的网页默认关联还是 Firefox，但 Ubuntu22.04 并未安装 Firefox。本轮已将 **Ubuntu 的 HTTP/HTTPS 默认浏览器**改为现有 Google Chrome；Windows 浏览器与默认设置保持原样。

## 现在每天怎么打开

1. Windows 桌面打开 **Ubuntu 22.04 桌面**，进入 KDE。
2. 双击 KDE 桌面的 **学习工作台（Ubuntu浏览器）**，或者在应用菜单搜索同名入口。
3. 工作台选当前教材与章节；需要写 Linux C++，打开 KDE 的 **VS Code Linux 学习工作区**，保存并运行当前作答。

也可在 Ubuntu 的 Konsole 输入：

```bash
learning-workbench
```

只想检查入口，不打开窗口：

```bash
learning-workbench --check
```

如果桌面仍显示旧名称，刷新桌面或从应用菜单搜索新入口。不需要重新安装 Ubuntu、桌面或浏览器。

## 页面在 Ubuntu，资料仍是一份

| 部分 | 现在在哪里 |
|---|---|
| 浏览器窗口 | Ubuntu 的 Chrome |
| 工作台服务 | Windows 上原有服务，继续使用 |
| Ubuntu 访问地址 | [已有 Tailscale 工作台入口](https://lsy.tailaa8c77.ts.net:8443) |
| 教材、代码和进度 | 同一份 仓库根目录，Ubuntu 对应 仓库根目录 |
| Linux 编译与调试 | Ubuntu 原生 VS Code + GCC/GDB |

没有在 Ubuntu 另外启动一套后台或另建一份进度。Windows、平板和 Ubuntu 读的是同一份学习数据；同时编辑同一文件或复盘时仍要避免覆盖，页面报告冲突时先保留自己的文字再刷新。

当前采用 NAT：Ubuntu 的 `127.0.0.1` 指向 Ubuntu 自己，Windows 的同一地址指向 Windows。Windows 服务只监听自己的回环地址，因此不能只把旧快捷方式里的程序名换成 Chrome，还需要使用已接通的 Tailscale HTTPS 入口。本轮从 Ubuntu 直连该入口的健康检查返回200，并由 Linux Chrome 实际渲染出三门重点课程与159项重点任务；总目录仍为10主线、388项。

访问这个私人入口不需要开启 Clash、TUN、LAN共享或公开18765端口。Windows 的 Tailscale 与原工作台需要运行。启动器会先做健康检查，失败时给出说明，不会悄悄切回 Windows 浏览器。

## 哪些按钮会操作哪一边

浏览器放在哪里，与后台运行在哪里，是两件事。现有工作台的电脑窗口操作由 Windows 服务执行；私人 HTTPS 页面还会限制这类操作。**想在 Ubuntu 内写代码，请用 KDE 的 VS Code Linux 学习工作区**，不依赖工作台替你打开原生窗口。网页 VS Code 则是另一种浏览器编辑入口。

[Ubuntu 原生 VS Code 使用](Ubuntu内VSCode使用.md) · [桌面、文件互通与 GitHub](Ubuntu22桌面与迁移教程.md) · [网页版 VS Code](VSCode网页版使用手册.md)

## 打不开时按顺序检查

- 先在 Windows 双击桌面 **学习工作台**，确认原服务能正常打开。
- 确认 Windows 的 Tailscale 已连接，再在 Ubuntu 运行 `learning-workbench --check`。
- 提示网络失败时，先查这两个服务；不要关闭防火墙、重新安装系统或把端口改成公网监听。
- 开了终端代理后出现异常，可在原终端 `proxy-off` 后重试。工作台启动器的健康检查直接连接已有私人入口。

Linux 启动器位于 `~/.local/bin/learning-workbench`；桌面入口为 `~/Desktop/learning-workbench.desktop`。修改前的原文件保存在 `~/.local/state/book-learning/backups/native-workbench-*`。本轮使用临时 Chrome 配置验收，没有替你操作实际 RDP 桌面点击或登录浏览器个人账户。[验收记录](Ubuntu浏览器入口验收.json)
