# Ubuntu 22.04 + KDE：启动、学习与设置

更新：2026-10-22。Ubuntu 22.04.5、KDE Plasma 5.24、NAT 和迁移已经完成。现在从下面的日常入口使用即可。

[Ubuntu 内 VS Code 使用](Ubuntu内VSCode使用.md) · [本轮验收记录](Ubuntu22迁移验收.json) · [桌面实测截图](../workbench/verification/ubuntu22/plasma.png)

## 每天只需这几步

1. 在 Windows 桌面双击 **Ubuntu 22.04 桌面**，连接本机 `127.0.0.1:3390`。xrdp 选择 **Xorg**，用户名 **mengyi**，输入原来的 **Linux 密码**。
2. 进入 KDE 后，在菜单搜索 **VS Code Linux 学习工作区**。这是 Ubuntu 内已安装的 VS Code，打开现有 Linux 学习工作区，直接使用 Linux 编译器。
3. 要用 Windows 的编辑器界面，则双击 Windows 桌面 **Ubuntu 22.04 学习 VS Code**，确认左下角 `WSL: Ubuntu-22.04`。两种入口选一种编辑当前文件即可。
4. 需要终端代理时，先在 KDE 打开 **Clash Verge**，再在 Konsole 输入 `proxy-on`。用完输入 `proxy-off`；没有网络需求时不必启动代理。
5. 结束时先保存文件。在 KDE 中“注销”结束图形会话；单纯关闭远程桌面窗口通常只是断开连接。

**登录与显示验收：** 用户已于2026-10-21实际登录并确认画面铺满，服务端也核实过2560×1600；不再需要重复“首次登录”验收。拖动窗口与滚动卡顿仍未解决，详见下方记录。Docker属于选用项，使用前仍需核对Windows Docker Desktop的新发行版集成。

### 工作台也可以留在 Ubuntu 里

KDE 桌面点 **学习工作台（Ubuntu浏览器）**，或在 Konsole 输入 `learning-workbench`。入口已改用 Ubuntu Chrome 和已有 Tailscale HTTPS 工作台，不再调用 Windows explorer.exe。页面仍共用原 D 盘教材与进度。[原因、操作和排障](Ubuntu工作台与浏览器说明.md)

### 全屏、黑边与流畅度

桌面主入口使用实际主屏像素尺寸，命令行显式传入全屏、宽和高。当前主屏2560×1600；已由用户确认画面铺满，并由Ubuntu的 `xrandr --current` 核实会话实际2560×1600。

- 窗口没有铺满时，可用 Ctrl+Alt+Break 切换；从桌面“Ubuntu 22.04 桌面”重连会自动读取主屏尺寸。
- 黑边与绘制流畅度是两个检查项。经典mstsc直接进入全屏会按显示器尺寸连接；本轮实测即使命令写1920×1200，服务端仍收到2560×1600。因此主入口恢复真实原生全屏，不再称它为已生效的低分辨率流畅模式。
- `D:/WSL/Ubuntu-22.04/launchers/Ubuntu-流畅窗口.rdp` 是诊断用固定1600×1000窗口配置，用户登录后已由服务端确认生效；用户仍反馈拖动、滚动明显卡顿。它尚未解决卡顿，不替代日常主入口。
- KDE合成已核实关闭，动画时长设为0；内存检查时约3.2GiB/15GiB、未用交换。现有证据不能把拖动卡顿直接归因于内存不足或所有虚拟机必然缓慢。
- 全屏已解决，xrdp/KDE拖动与滚动卡顿仍未解决。继续排查应测量绘制/编码与客户端刷新，避免反复让用户改分辨率、登录或随机升级软件。

日常写C++可使用Windows侧VS Code连接Ubuntu，编译、终端和调试仍在Linux，编辑界面避开整套桌面远程传图。Linux图形应用可按需要通过WSLg独立打开；WSLg不等于完整KDE桌面，官方说明见 [Microsoft WSL GUI文档](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps)。这不要求删除KDE或迁移现有学习文件。

## 1. 当前环境在哪里

| 部分 | 当前状态与位置 |
|---|---|
| 默认 WSL 发行版 | `Ubuntu-22.04`，Ubuntu 22.04.5，WSL 2，systemd |
| 新系统磁盘 | `D:\WSL\Ubuntu-22.04\ext4.vhdx` |
| 旧环境 | 原 `Ubuntu` 26.04 保留，位于 `D:\WSL\ubuntu`，未删除 |
| Linux 用户 | `mengyi`，UID 1000，沿用原 Linux 登录口令 |
| 桌面 | KDE Plasma 5.24 / X11，Breeze 浅色、中文字体 |
| 桌面连接 | xrdp 仅监听 `127.0.0.1:3390` |
| 共享学习区 | Windows 的 `D:\Book-Learning` = Ubuntu 的 `仓库根目录` |
| 网络 | NAT，localhost 转发和 DNS 隧道开启，Windows 代理自动导入关闭 |

home 中的原文件和个人设置已迁入；可重建缓存未复制。迁移核对 5511 个原文件，5510 个相同，1 个 `.bashrc` 因加入代理开关有意修改，未发现意外缺失或改动。教材、自己的作答与进度继续使用原 D 盘同一份文件。

Linux 软件按 Ubuntu 22.04 兼容版本重新安装，不是把旧系统 `/usr` 整体覆盖过来。主要 Linux 数据在 D 盘；Windows 的 WSL 组件及少量缓存仍可能占用 C 盘。

## 2. 打开、断开、注销与停止

日常优先使用已建立的桌面入口。需要手动进入时，在 **Windows PowerShell** 运行：

```powershell
wsl -d Ubuntu-22.04
```

再在 Windows 按 `Win + R`，输入：

```text
mstsc /v:127.0.0.1:3390
```

首次证书提示对应本机自签名 xrdp 服务，先核对目标地址确为 `127.0.0.1:3390`。登录界面选 Xorg，不选 Wayland。

| 操作 | 结果 |
|---|---|
| 关闭远程桌面窗口 | 通常仅断开，桌面程序可能继续运行 |
| KDE 菜单中注销 | 结束该次图形会话 |
| `wsl --terminate Ubuntu-22.04` | 停止新发行版；先保存所有 Ubuntu 文件 |
| `wsl --shutdown` | 停止全部 WSL 及其虚拟机，也会影响 Docker；日常不需要 |

电脑重启后重新点启动入口，不用再装系统、创建账号或重新迁移。系统停止后，Linux 程序和终端也需要重新打开。

## 3. 账号与密码

xrdp 使用 **Linux 用户名 mengyi + 原 Linux 密码**，不是 Windows PIN。密码不需要发到聊天里。忘记时，在本机 PowerShell 交互重设：

```powershell
wsl -d Ubuntu-22.04 -u root -- passwd mengyi
```

按提示输入两遍新密码，通常没有星号回显。此命令只改变新 22.04 环境的密码，不会自动改变旧 `Ubuntu` 的密码。正常使用桌面时用普通用户，需要管理权限时在终端输入 `sudo`。

## 4. Windows 和 Ubuntu 之间传文件

| 你在做什么 | 位置或操作 |
|---|---|
| Ubuntu 打开 D 盘学习区 | `仓库根目录` |
| Ubuntu 打开 Windows 下载目录 | `/mnt/c/Users/lsy08/Downloads` |
| Windows 打开 Linux 主目录 | 资源管理器地址栏输入 `\\wsl.localhost\Ubuntu-22.04\home\mengyi` |
| 在 Ubuntu 当前目录打开 Windows 资源管理器 | `explorer.exe .`，保留最后的点 |
| 从 Windows 快速进 Linux 文件 | 桌面 **Ubuntu 22.04 Linux 文件** |

`仓库根目录` 就是 D 盘原目录，保存后双方看到同一份文件。复制到 `/home/mengyi` 后才会变成两份独立内容，后续不会自动同步。日常用一个编辑窗口修改当前文件，避免两边同时保存。

本轮已实际完成 Windows 写、Ubuntu 读，以及 Ubuntu 写、Windows 读，双方 SHA256 核对通过。两个小样例保留在：

```text
D:\WSL\Exchange\20261021-0318-runtime-e87e8d0b
/mnt/d/WSL/Exchange/20261021-0318-runtime-e87e8d0b
```

在 Ubuntu Konsole 可试：

```bash
cd /mnt/d/WSL/Exchange/20261021-0318-runtime-e87e8d0b
cat from-windows.txt
cat from-ubuntu.txt
explorer.exe .
```

现有教材源码继续留 D 盘。以后以 Linux 为主、依赖和小文件很多的新项目可放 `~/projects`，Windows 仍通过 WSL 共享路径访问。源码保持一份，Windows 与 Linux 的构建产物分目录；Shell 文件用 LF 换行，跨系统项目避免仅大小写不同的重名文件。不要手工修改正在使用的 `ext4.vhdx`。[微软文件互通说明](https://learn.microsoft.com/en-us/windows/wsl/filesystems)

RDP 剪贴板已开启，可复制文字；大文件用文件夹互通更直观。中文字体已安装，能显示汉字与 Linux 输入法是两件事；需要连续输入时再单独配置并验证输入法。

## 5. KDE 外观与常用位置

当前使用内置 Breeze 浅色、Noto 中文字体，远程会话关闭合成以降低绘制负担。可在系统设置搜索关键词调整：

| 想调整 | KDE 中的入口 |
|---|---|
| 浅色主题、颜色 | 系统设置 → 外观 → 全局主题 / 颜色 |
| 字体与字号 | 系统设置 → 外观 → 字体；Konsole 字号可独立调 |
| 动画 | 系统设置搜索“动画”或“常规行为” |
| 文件位置 | Dolphin 中固定学习区和 Linux 家目录 |

先调整到清楚、舒适，再添加少量喜欢的外观。更换主题时留意是否同时重置桌面布局。[KDE 外观说明](https://userbase.kde.org/System_Settings/Appearance)

## 6. Clash：已复用 Windows 的配置与选择

Ubuntu 内已安装 **Clash Verge Rev 2.5.8**，已有 profiles 和选择状态已在本机迁入。当前沿用 Windows 保存的 **GLOBAL / 全局模式选择**，持久化后的冷启动核对中，选中路径访问 GitHub 返回 200、Google 连通检测返回 204。**这验证选中的路径，不代表全部节点可用。**

当前设置：混合端口 **127.0.0.1:7897**；系统代理、TUN、LAN 共享和自动启动均关闭。Linux 与 Windows 各自维护一份配置，之后改节点或订阅不会自动同步另一边。

需要终端联网时：

1. 在 KDE 菜单搜索 **Clash Verge** 并打开，确认内核已启动。
2. 在正在使用的 Konsole 输入 `proxy-on`，再运行 Git、curl 等需要代理的命令。
3. 不再需要或准备关闭 Clash 时，在该终端输入 `proxy-off`。

```bash
proxy-on
curl -sS -o /dev/null -w '%{http_code}\n' --max-time 20 https://github.com
proxy-off
```

代理变量只影响当前终端及其子进程，不会保证所有已经打开的图形程序或提权命令都跟随。Clash 没启动时别开终端代理；关闭客户端后，旧终端的变量也不会自动消失。

订阅元数据中的有效时间已过，但原配置当前选中节点本轮仍可用。以后访问失败时，先在本机客户端检查内核、节点和订阅状态，再按需更新。当前不改回未经验证的规则模式，也不需要为此开启 LAN 或 TUN。

配置保存在 Linux 用户私有目录，不放入学习区仓库；订阅链接、节点凭据及整份私有日志不写入教程或聊天。[Clash Verge Rev 使用说明](https://www.clashverge.dev/guide/quickstart.html)

## 7. GitHub：已接通 Windows 登录

Ubuntu 内继续用 Linux Git；访问 `https://github.com` 时，通过凭据助手调用 Windows 已登录的 GitHub CLI。令牌保留在 Windows 凭据存储，不另建 Linux token 文件。本轮已实际通过 GitHub `/user` 认证请求，返回 **200**。

Git 提交署名沿用现有设置。可在 Ubuntu 安全查看：

```bash
git config --get user.name
git config --get user.email
```

提交署名、网络可达和仓库权限是不同的检查。当前桥接用于 HTTPS 地址；SSH 仓库使用另一套密钥配置。某个私有仓库是否允许访问，仍取决于你的账号权限。

Windows 登录过期时，在 **Windows PowerShell** 运行 `gh auth login`，通过本机浏览器重新授权；Linux Git 继续使用已有助手。不要重复清空全局 credential helper，也不用把 token 复制进 Ubuntu。查看状态用 `gh auth status`，不要使用打印 token 的参数或命令。[GitHub CLI 凭据助手](https://cli.github.com/manual/gh_auth_setup-git)

Linux Git 使用 Ubuntu 网络；Windows gh、GCM 和浏览器仍是 Windows 进程，网络和代理取决于 Windows 设置。NAT 下同样的 `127.0.0.1` 字面地址在两侧含义不同。其他 HTTPS 网站按需使用 Windows GCM，不影响当前 GitHub 专用助手。

## 8. NAT 网络：已经配置，不必每天重设

网络模式已实测为 **nat**。Windows 用户目录 `.wslconfig` 的实际关键设置为：

```ini
[wsl2]
networkingMode=nat
localhostForwarding=true
dnsTunneling=true
autoProxy=false
```

这些是全部 WSL 2 发行版共享的配置。原文件已备份，内存、CPU 等其他设置保留；迁移时已整体重启让 NAT 生效。日常不用再修改或 `wsl --shutdown`。`autoProxy=false` 避免把 Windows 回环代理误当 Ubuntu 本机代理。[微软 WSL 网络](https://learn.microsoft.com/en-us/windows/wsl/networking)

| 访问方向 | 当前用法 |
|---|---|
| Windows → Ubuntu 桌面 | `127.0.0.1:3390`，经 localhost 转发 |
| Ubuntu → Ubuntu 内 Clash | `127.0.0.1:7897` |
| Ubuntu → Windows 上的其他服务 | 使用当前 NAT 网关地址，还要确认 Windows 服务允许该来源 |

需要确定 Windows 主机的当前 NAT 地址，在 Ubuntu 运行：

```bash
ip route show default
```

查看 `via` 后面的地址，不照抄固定的 172.x 地址。WSL 自己的 `127.0.0.1` 无法直接代表只监听 Windows 回环的程序；服务绑定和防火墙范围也要匹配。

NAT 与图形显示不是同一件事。WSLg 负责单个图形应用，xrdp 负责独立桌面会话；保留各自的 DISPLAY，不把网关写进全局 DISPLAY。平板上的 `127.0.0.1` 指平板自己；平板学习继续用已有 Tailscale 工作台和浏览器 VS Code，当前 3390 不对外开放。

## 9. C++ 与两种 VS Code 入口

Ubuntu 内已安装 **VS Code 1.142**、简体中文语言包和 C/C++ 扩展，采用浅色主题；已实际绘制窗口验收。详细按钮与任务用法见 [Ubuntu 内 VS Code 使用](Ubuntu内VSCode使用.md)。

| 入口 | 编辑器运行在哪 | 如何确认 |
|---|---|---|
| KDE 菜单 **VS Code Linux 学习工作区** | Ubuntu 内原生 VS Code | 终端直接使用 `/usr/bin/g++`，通常不显示 Remote WSL 标记 |
| Windows 桌面 **Ubuntu 22.04 学习 VS Code** | Windows 界面 + Ubuntu 远程开发服务 | 左下角应显示 `WSL: Ubuntu-22.04` |

两种方式都应打开这份 **Linux 工作区**：

```text
仓库根目录/workspaces/focus-wsl.code-workspace
```

在 KDE Konsole 可运行：

```bash
/home/mengyi/.local/bin/code-linux 仓库根目录/workspaces/focus-wsl.code-workspace
```

从 Windows PowerShell 使用 Remote WSL 入口：

```powershell
code --remote wsl+Ubuntu-22.04 仓库根目录/workspaces/focus-wsl.code-workspace
```

**不要在 Ubuntu 内直接打开普通 cpp 根目录后照用其 Windows 任务。** 那里的任务含 Windows 路径；focus-wsl 工作区已经指定 Linux 编译器、脚本、当前文件任务与 GDB。日常选中自己的源码，从“终端 → 运行任务”选 **本题：运行作答**；需要输入文件时选对应 `input.txt` 任务。参考运行不等于自己的作答已完成。

确认终端环境可输入：

```bash
cat /etc/os-release
which g++
g++ --version
pwd
```

应是 22.04、Linux 编译器和 `/mnt/d/...` 或 Linux 家目录。Windows Remote WSL 首次连接会按需建立服务端及扩展；这与已安装的 Ubuntu 原生 VS Code 是两套入口，不要混淆两边的扩展安装位置。[VS Code 官方 WSL 开发说明](https://code.visualstudio.com/docs/remote/wsl)

C++、CMake、GDB 与 OpenCV 开发链已经重装；本轮 C++ 参考和 OpenCV 图像文件示例已实际运行。图形显示可用 WSLg 或 KDE；Windows 摄像头不会因为打开桌面就自动成为 Linux `/dev/video0`，当前先用学习区图像文件。

## 10. Node、Python、Chrome 与 Docker

| 软件 | 本轮核查结果 | 平时使用 |
|---|---|---|
| Node / npm | 迁来的 Node 24.18.0、npm 11.16.0 可运行，普通交互终端识别正常 | `node --version`、`npm --version` |
| Python | 3.10.12，可新建并运行独立虚拟环境 | 需要 Python 的项目再建环境 |
| .NET | 旧、新系统均只有 corefx 缓存，无可执行 SDK | 当前学习无需补装；以后相关项目按需安装 |
| Chrome | 官方 deb 安装 155.0.8059.84，独立临时配置、保留沙箱的渲染通过 | KDE 搜索 Google Chrome，或输入 `google-chrome` |
| Docker | 当前尚未启用 Ubuntu-22.04 集成，命令明确返回相应提示 | 按下方步骤在 Windows Docker Desktop 勾选 |

本轮未在旧、新 home、常见 pipx/venv 位置及现有学习项目中发现待迁移的 `pyvenv.cfg`，没有批量重建或安装依赖。未扫描整机所有项目；以后打开其他 Python 项目时再确认兼容性。

新 Python 项目在自己的项目目录内执行：

```bash
python3 -m venv .venv
source .venv/bin/activate
python --version
python -m pip --version
# 用完退出环境：
deactivate
```

已有 `.venv` 时先核对解释器，不直接覆盖。不同 Python 版本的二进制依赖需根据该项目依赖清单安装。

Chrome 本轮未额外导入浏览器登录信息，也未修改 Windows Chrome；个人账号状态和真实桌面浏览尚未代替你登录验收。[Google 官方安装说明](https://support.google.com/chrome/answer/95346?hl=zh-Hans)

需要 Docker 时，在 Windows 打开 **Docker Desktop**，进入 **Settings → Resources → WSL Integration**，开启 **Ubuntu-22.04** 后点击 **Apply**。若没有该页面，确认是 Linux containers；General 中可见时启用 **Use WSL 2 based engine**。回 Ubuntu 执行 `docker version`，同时出现 Client 与 Server 才算接通。不要在 Ubuntu 再装另一套 Docker Engine。[Docker 官方 WSL 设置](https://docs.docker.com/desktop/features/wsl/)

## 11. 维护时核对的配置

以下只供排障查阅，日常无需重装或重写文件。

**systemd 与版本：**

```bash
ps -p 1 -o comm=
cat /etc/os-release
systemctl is-active xrdp xrdp-sesman
ss -lnt | grep ':3390'
```

PID 1 应是 systemd；桌面启动后两个服务应 active，端口只应显示 `127.0.0.1:3390`。systemd 随发行版启动，不表示 Windows 开机后发行版已经在运行。

**xrdp：** `/etc/xrdp/xrdp.ini` 的 `[Globals]` 当前为 `port=tcp://127.0.0.1:3390`，`sesman.ini` 禁止 root 桌面登录。不要全文件替换所有 `port=`，Xorg 节中的 `port=-1` 含义不同。[Ubuntu xrdp 配置手册](https://manpages.ubuntu.com/manpages/jammy/man5/xrdp.ini.5.html)

**用户会话：** `/home/mengyi/.xsession` 当前实际内容如下，保留 xrdp 分配的 DISPLAY：

```sh
#!/bin/sh
unset DBUS_SESSION_BUS_ADDRESS SESSION_MANAGER WAYLAND_DISPLAY
export XDG_CURRENT_DESKTOP=KDE
export XDG_SESSION_DESKTOP=KDE
export XDG_SESSION_TYPE=x11
export XDG_RUNTIME_DIR=/run/user/$(id -u)
export QT_QUICK_BACKEND=software
exec dbus-run-session -- startplasma-x11
```

运行时目录对当前用户为 `/run/user/1000`，Qt Quick 使用软件绘制。不要在 `.bashrc` 全局强制 `DISPLAY=:0`。`.xsession` 归 mengyi、权限700；修改前先备份，避免两个桌面启动命令同时执行。

**软件维护：** 桌面与开发依赖已安装，不用重跑旧安装清单。按需更新 22.04 的软件包；保持 jammy 软件源，不执行发行版升级或直接换到其他版本。原始部署脚本和安装日志保留在工作区 `learning-update/wsl22-desktop`，是维护记录，不是每日操作入口。

## 12. 遇到问题按这个顺序检查

| 现象 | 先做什么 |
|---|---|
| RDP 连接超时 | 重新打开桌面入口，核对新发行版与 xrdp 状态、3390监听 |
| 账号或密码错误 | 用 mengyi 与 Linux 密码；确实忘记时在本机交互重设 |
| 选 Xorg 后马上退出或黑屏 | 检查 `.xsession` 归属与上面的运行时设置，确认没有写死 DISPLAY |
| VS Code 任务找 Windows 路径 | 打开 focus-wsl.code-workspace，使用带 WSL 标签的任务 |
| Windows VS Code 进入旧 Ubuntu | 左下角核对 Ubuntu-22.04，重新使用指定发行版入口 |
| 中文能显示但不能输入 | 字体不是输入法；先用剪贴板，再单独验证输入法 |
| 代理开了仍不通 | 先确认 Clash 已启动，再核对当前终端 proxy-on、节点和订阅状态 |
| 关 Clash 后终端断网 | 在原终端执行 proxy-off，再重试 |
| GitHub 网络正常但私有库失败 | 核对 Windows 登录及该账号仓库权限，不改 SSL 校验 |
| docker 提示未集成 | 启动 Windows Docker Desktop，勾 Ubuntu-22.04 并 Apply |

Ubuntu 的桌面服务日志可以在本机查看：

```bash
journalctl -u xrdp -u xrdp-sesman --no-pager -n 80
tail -n 80 ~/.xsession-errors
```

Windows 检查连接：

```powershell
wsl --list --verbose
Test-NetConnection 127.0.0.1 -Port 3390
```

检查结果不清楚时先看日志与当前环境，不反复重装。Clash 私有日志可能含订阅信息，不整份发布。

## 13. 备份与本轮验收范围

旧 `Ubuntu` 26.04 保留，当前不会自动注销或删除。新环境大规模修改前，先保存文件并注销桌面，可在 PowerShell 用 `wsl --export Ubuntu-22.04 新的备份文件路径.tar` 导出；备份目录先建立，使用新文件名并确认空间足够。恢复时用独立的新发行版名字，避免覆盖现在的学习环境。

本轮已有证据：22.04/WSL2/systemd、NAT、回环 xrdp、home 文件核对、KDE 与原生 VS Code 绘制、C++/OpenCV 运行、Node/npm、Python 临时环境、Chrome 渲染、双向文件读写、Clash 当前选择路径联网，以及 GitHub 身份认证。

仍需区分：你的真实 RDP 首次口令登录、所有手动交互、浏览器个人登录、Docker Desktop 新集成和所有代理节点并未全部代替你验收。参考或环境测试通过也不会自动标记个人习题完成。详细证据见[迁移验收记录](Ubuntu22迁移验收.json)。
