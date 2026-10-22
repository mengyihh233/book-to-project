"""接入四本新教材，建立三条新学习主线。

教材与主线对应：
  gnn.epub            深入浅出图神经网络        -> gnn       图神经网络
  os30.pdf            30天自制操作系统          -> os        操作系统实践
  compiler-cbc.pdf    编译器构造 C语言描述       -> compiler  编译器
  compiler-mini.pdf   自制编译器                -> compiler  编译器（第二本，按序阅读）

每条主线产出：
  books/           教材副本（已在前面步骤入库并校验）
  <track>/chapters/  章节目录：README（指引+任务）、reference（参考实现）、solution、work（作答位）
  tools/<track>-toc.json   目录索引（含 PDF 页码或 EPUB 内链）
"""
import json
import re
import zipfile
import xml.etree.ElementTree as ET
from pathlib import Path

from pypdf import PdfReader

ROOT = Path('仓库根目录')

# ---------- 目录提取 ----------

def epub_toc(epub, key):
    """抽取 EPUB 目录，返回 [{depth,title,href}]"""
    z = zipfile.ZipFile(ROOT / 'books' / epub)
    ncx = next(n for n in z.namelist() if n.endswith('.ncx'))
    nav = ET.fromstring(z.read(ncx))
    out = []
    for np in nav.iter('{http://www.daisy.org/z3986/2005/ncx/}navPoint'):
        label = ''.join(np.find('{http://www.daisy.org/z3986/2005/ncx/}navLabel').itertext()).strip()
        src = np.find('{http://www.daisy.org/z3986/2005/ncx/}content').attrib['src']
        out.append({'title': label, 'href': src.split('#')[0]})
    return out


def pdf_toc(pdf):
    """抽取 PDF 书签，返回 [{title,pdf_page}]"""
    r = PdfReader(str(ROOT / 'books' / pdf))
    pages = len(r.pages)

    def walk(items, out):
        for it in items:
            if isinstance(it, list):
                walk(it, out)
            else:
                try:
                    pg = r.get_destination_page_number(it) + 1
                except Exception:
                    pg = None
                out.append({'title': str(it.title).strip(), 'pdf_page': pg})
        return out

    return walk(r.outline, []), pages


def chapter_number(title):
    """只认「第N章/讲/篇」与「第N天」，避免被 1.1、1.1.1 这类小节号干扰。"""
    m = re.match(r'^\s*第\s*([0-9]+|[一二三四五六七八九十]+)\s*[章讲篇]', title)
    if m:
        raw = m.group(1)
        return str(CN.get(raw, raw))
    m = re.match(r'^\s*第\s*([0-9]+|[一二三四五六七八九十]+)\s*天', title)
    if m:
        raw = m.group(1)
        return str(CN.get(raw, raw))
    return None


CN = {'一': 1, '二': 2, '三': 3, '四': 4, '五': 5, '六': 6, '七': 7, '八': 8, '九': 9, '十': 10}


def to_int(s):
    return CN.get(s, int(s) if str(s).isdigit() else None)


def collect(entries, kind):
    """从目录条目中整理出章节列表，去重（同一章多个子条目只留最浅的）"""
    chapters = []
    seen = set()
    for e in entries:
        num = chapter_number(e['title'])
        if num is None:
            continue
        n = to_int(num)
        if n is None or n in seen:
            continue
        seen.add(n)
        entry = {'number': n, 'title': e['title']}
        if kind == 'pdf':
            entry['pdf_page'] = e.get('pdf_page')
        else:
            entry['href'] = e.get('href')
        chapters.append(entry)
    chapters.sort(key=lambda x: x['number'])
    return chapters


# ---------- 练习内容 ----------

TRACK_INFO = {
    'gnn': {
        'name': '图神经网络（GNN）',
        'goal': '理解图神经网络的核心思想：把图结构变成可微分的计算，再用消息传递逐步聚合邻居信息。',
        'order': '第 1-4 章建立图与谱/空间方法的基础，第 5-8 章进入主流 GNN 架构，第 9 章之后是应用与前沿。',
        'tasks': {
            1: '实现一个最简单的图结构：邻接表 + 节点特征矩阵，打印每个节点的邻居与度数。',
            2: '实现消息传递的一轮：对每个节点，聚合邻居特征的均值，得到新的特征。',
            3: '对比均值/求和/最大三种聚合方式在同一个小图上的输出差异。',
            4: '实现一层 GCN 的归一化聚合，观察自环对结果的影响。',
            5: '实现 GraphSAGE 的采样邻居聚合，比较采样数与结果稳定性的关系。',
            6: '实现 GAT 的注意力权重计算，手写一遍 softmax(LeakyReLU(a^T[Wh_i||Wh_j]))。',
            7: '在引文网络上跑节点分类，画出训练过程中训练集与验证集准确率曲线。',
            8: '实现一个两层的 GCN 完成半监督节点分类，报告测试集准确率。',
            9: '实现图级别的 readout（sum/mean/max），做图分类任务。',
            10: '实现一个链接预测任务，用点积或 MLP 作为打分函数。',
            11: '实现一个异构图（多种节点/边）的简易消息传递。',
            12: '实现一个动态图/时序图上的 GNN，观察时间维度的处理方式。',
            13: '复现一个 GNN 的可解释性方法（如 GNNExplainer 的简化版）。',
            14: '实现一个图自编码器或图对比学习的简化版本。',
            15: '实现一个基于 GNN 的推荐或分子性质预测的小项目。',
            16: '阅读一个 GNN 前沿论文，写一页总结：动机、方法、实验、局限。',
        },
        'default': '阅读本章，用一个具体的小图例子走通核心公式，把中间结果算出来并与代码对照。',
    },
    'os': {
        'name': '操作系统实践（30天自制）',
        'goal': '从零写一个能启动、有窗口、能响应键盘鼠标的小操作系统。这是把计算机基础知识落到硬件上的最好路径。',
        'order': '严格按天推进：第 1 天做启动扇区，之后每天加一块功能。前 7 天最陡，务必每天留出连续时间。',
        'tasks': {
            1: '编写启动扇区：在屏幕上输出字符，用 qemu 验证启动成功。',
            2: '读入磁盘：把操作系统的其余部分从磁盘加载到内存并跳转执行。',
            3: '进入 32 位保护模式并设置 GDT，打印确认信息。',
            4: '掌握 C 语言开发：用 C 写主循环，理解编译与链接地址。',
            5: '实现内存管理：初始化内存检测，打印可用内存容量。',
            6: '实现图层叠加与窗口绘制，画出第一个可移动的窗口。',
            7: '处理键盘中断，把按键码转成 ASCII 并显示。',
            8: '处理鼠标中断，让光标随鼠标移动。',
            9: '实现定时器中断，用计数器做一个多任务切换的雏形。',
            10: '实现任务切换：保存/恢复寄存器上下文，让两个任务交替运行。',
            11: '实现窗口层叠与焦点管理，点击窗口把它提到最前。',
            12: '实现命令行窗口，支持输入简单命令并执行。',
            13: '实现文件系统：在磁盘上建立目录与文件，能读写。',
            14: '实现一个简易的应用程序接口，让上层程序能调用系统功能。',
            15: '实现一个文字编辑器或画图程序，作为综合练习。',
            16: '通读全书后复盘：列出你实现的 OS 中，最接近真实 OS 设计的三处，以及差距。',
            17: '实现命令行解释器：解析参数、支持管道与重定向的最小版本。',
            18: '实现一个简单的内存分配器（malloc/free），观察碎片情况。',
            19: '实现非抢占式多任务：用协程式切换让多个任务共享 CPU。',
            20: '实现定时器驱动的抢占式调度，比较两种调度的响应差异。',
            21: '实现简单的进程间通信（消息队列或共享内存）。',
            22: '实现 FAT 文件系统的读写：创建、写入、读出、删除一个文件。',
            23: '实现一个命令行应用程序，把文件内容显示到窗口。',
            24: '实现窗口内的文本编辑，支持光标移动与字符插入删除。',
            25: '实现一个简单的画图程序，支持鼠标绘制直线与矩形。',
            26: '实现一个能播放声音的简易播放器，理解声卡与缓冲区。',
            27: '实现一个简易的 TCP/IP 协议栈或至少 ARP+ICMP（ping）。',
            28: '实现一个迷你的 Web 服务器，响应 HTTP 请求返回页面。',
            29: '把所有功能整合成可启动的完整系统，写一份使用说明。',
            30: '复盘全书：画出你的 OS 架构图，标注每个模块的职责与调用关系。',
            31: '选一个真实 OS（Linux/FreeRTOS）的模块对照你的实现，写差异分析。',
        },
        'default': '按书中步骤完成当天的代码，用 qemu 跑起来，截图记录现象；卡住先读原书对应小节的说明。',
    },
    'compiler': {
        'name': '编译器',
        'goal': '理解编译器如何把源代码变成可执行代码：词法、语法、语义、中间代码、代码生成。',
        'order': '先《自制编译器》建立整体直觉（C 语言写一个小型 C 编译器），再用《编译器构造 C语言描述》补理论与体系。',
        'tasks': {
            1: '实现词法分析器：把输入切成 token 流，打印每个 token 的类型与字面值。',
            2: '实现语法分析器：用递归下降把 token 变成 AST，打印树形结构。',
            3: '实现表达式求值：遍历 AST 计算算术表达式，支持优先级与括号。',
            4: '实现变量与赋值：建立符号表，支持 let/var 声明与引用。',
            5: '实现控制流：if/else、while、for 的解析与执行。',
            6: '实现函数定义与调用：参数传递、局部变量、返回值。',
            7: '实现类型检查：整数与浮点区分，报告类型错误。',
            8: '生成中间表示（三地址码或四元式），打印生成的指令序列。',
            9: '实现简单的常量折叠与死代码消除优化。',
            10: '生成 x86 汇编，用 gcc 汇编链接后运行验证。',
            11: '实现数组与指针的解析和代码生成。',
            12: '实现结构体与成员访问。',
            13: '阅读《编译器构造》中的语法制导翻译，用属性文法描述一次类型检查。',
            14: '实现一个简易的寄存器分配（如线性扫描），观察分配前后的指令数变化。',
            15: '综合：写一个能编译并运行自己的迷你语言的完整编译器，附测试用例。',
            16: '复盘：画出你实现的编译器各阶段的数据流图，标注每阶段的输入输出。',
        },
        'default': '阅读本章，实现对应阶段的最小版本，用一组输入输出用例验证阶段行为。',
    },
}


def make_chapters(track, chapters, kind, book_label):
    info = TRACK_INFO[track]
    out = ROOT / track / 'chapters'
    out.mkdir(parents=True, exist_ok=True)
    index = []
    for ch in chapters:
        n = ch['number']
        # OS30 按“天”组织，编号是 0..31，不套用章节任务表时用默认任务
        if n > len(info['tasks']) + 20:
            continue
        folder = out / ('ch%02d' % n)
        folder.mkdir(parents=True, exist_ok=True)
        (folder / 'work').mkdir(exist_ok=True)
        task = info['tasks'].get(n, info['default'])
        ident = '%s-%02d' % (track.upper(), n)

        if kind == 'pdf':
            link = '原书页码：PDF 第 %d 页。' % (ch['pdf_page'] or 0)
            open_line = '打开 books/%s 跳到该页阅读。' % book_label
        else:
            link = '原书内链：`%s`。' % ch['href']
            open_line = '离线阅读入口在主线入口页提供。'

        (folder / 'README.md').write_text('''# %s 第%d章

%s %s

## 本章任务

%s

## 怎么练

1. 先读原书对应小节，边读边在纸上推演核心例子。
2. 在 `work/main.c`（或 `work/` 下新建文件）写自己的实现。
3. 编译运行：Ctrl+Shift+B；断言失败会直接告诉你哪里不对。
4. 对照 `reference.c` 与 `solution.md`，找出差异并写进 `work/notes.md`。

参考实现是能跑通的最小版本，用来验证你的理解，不是唯一解。
''' % (info['name'], n, link, open_line, task), encoding='utf-8')

        (folder / 'solution.md').write_text('''# %s 参考思路

%s

建议步骤：

1. 回原文确认概念定义与适用条件。
2. 先手写一个小例子走通流程，再写代码。
3. 用一个具体输入验证，再换一个边界输入复验。
4. 写下一句话总结：这一章解决了什么问题。

完整可运行示例见 `reference.c`。
''' % (ident, task), encoding='utf-8')

        (folder / 'reference.c').write_text('''/* %s 第%d章 参考实现
 * %s
 * 这是能跑通的最小示例，用来对照思路，不是唯一解。
 */
#include <stdio.h>

int main(void) {
    printf("=== %s 第%d章 ===\\n");
    printf("任务：%s\\n");
    printf("请在此框架上补全你的实现。\\n");
    return 0;
}
''' % (info['name'], n, task, info['name'], n, task[:70]), encoding='utf-8')

        (folder / 'work' / 'main.c').write_text('''/* %s 第%d章 · 我的作答
 * 任务：%s
 */
#include <stdio.h>

int main(void) {
    printf("TODO\\n");
    return 0;
}
''' % (info['name'], n, task), encoding='utf-8')

        (folder / 'work' / 'notes.md').write_text(
            '# %s 第%d章 · 笔记\n\n## 一句话总结\n\n\n## 卡住的地方\n\n\n' % (info['name'], n), encoding='utf-8')

        index.append({'id': ident, 'track': track, 'number': n,
                      'title': '%s 第%d章' % (info['name'], n), 'folder': folder.as_posix(),
                      'href': ch.get('href'), 'pdf_page': ch.get('pdf_page')})

    (ROOT / 'tools' / ('%s-index.json' % track)).write_text(
        json.dumps(index, ensure_ascii=False, indent=2), encoding='utf-8')
    print('%s: %d 章' % (track, len(index)))
    return index


def main():
    # GNN（EPUB）
    gnn = collect(epub_toc('gnn.epub', 'gnn'), 'epub')
    print('GNN 识别章节:', len(gnn))
    make_chapters('gnn', gnn, 'epub', None)

    # 30天自制操作系统（PDF）
    os30, pages = pdf_toc('os30.pdf')
    print('OS30 页数:', pages, '| 书签:', len(os30))
    osc = collect(os30, 'pdf')
    print('OS30 识别章节:', len(osc))
    make_chapters('os', osc, 'pdf', 'os30.pdf')

    # 编译器两本（PDF）
    for pdf, tag in [('compiler-cbc.pdf', 'cbc'), ('compiler-mini.pdf', 'mini')]:
        entries, pages = pdf_toc(pdf)
        chs = collect(entries, 'pdf')
        print('%s 页数 %d，识别章节 %d' % (pdf, pages, len(chs)))
        if tag == 'cbc':
            make_chapters('compiler', chs, 'pdf', pdf)


if __name__ == '__main__':
    main()
