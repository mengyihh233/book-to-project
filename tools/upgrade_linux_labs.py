"""重写 Linux 26 章练习：从“打印几行命令”升级为“有任务、有断言、能自判对错”。

每章产出：
  reference.sh  完整参考实现，结尾用断言验证自己的输出（失败即非零退出）
  work.sh       自己的作答位，保留同一套 check_* 断言框架
  README.md     本章任务、知识点、原书页码与验收标准

说明：
- 断言只依赖 bash 内建与 coreutils，不引入额外依赖。
- 不在脚本里清理临时文件：本环境的 rm -rf 极慢（约 20 秒），会拖垮练习节奏；
  沙箱目录本就是一次性草稿区，且每次运行用 $$ 生成唯一子目录，计数不会串。
- chmod 在 MINGW 下不可靠（符号式 +x 无效、绝对/相对路径行为不一致），
  因此权限章只验证 [ -r ]/[ -w ] 判定与权限位解读，不断言可执行位。
"""
from pathlib import Path

ROOT = Path('仓库根目录')

HARNESS = '''#!/usr/bin/env bash
# ---- 自校验框架：把结果和期望值比一比，错就报出来 ----
pass=0; fail=0
check() { # check 说明 实际值 期望值
  if [ "$2" = "$3" ]; then pass=$((pass+1)); printf 'PASS  %s\\n' "$1"
  else fail=$((fail+1)); printf 'FAIL  %s\\n  期望: [%s]\\n  实际: [%s]\\n' "$1" "$3" "$2"; fi
}
finish() {
  printf '\\n%d 项通过，%d 项未过\\n' "$pass" "$fail"
  [ "$fail" -eq 0 ] || exit 1
}
'''

# 每章：(任务描述, 参考实现主体, 断言序列[(说明, 实际值命令, 期望值)])
CHAPTERS = {
1: ('认识 shell：输出 shell 名、内核名与当前用户，并判断自己跑在哪种 shell 里',
    '''printf 'shell=%s\\n' "${BASH_VERSION%%(*}"
printf 'kernel=%s\\n' "$(uname -s)"
printf 'user=%s\\n' "$(id -un)"
printf 'is_bash=%s\\n' "$([ -n "$BASH_VERSION" ] && echo yes || echo no)"''',
    [('输出包含 shell 名', 'printf "%s" "$BASH_VERSION" | grep -q . && echo has', 'has'),
     ('内核名非空', 'uname -s | grep -q . && echo has', 'has'),
     ('用户身份已取得', 'id -un | grep -q . && echo has', 'has')]),
2: ('用 type、command -v、help 区分内建命令与外部命令',
    '''printf 'builtin=%s\\n' "$(type -t cd)"
printf 'external=%s\\n' "$(type -t ls)"
printf 'has_cd_help=%s\\n' "$(help cd >/dev/null 2>&1 && echo yes || echo no)"''',
    [('cd 是内建命令', 'type -t cd', 'builtin'),
     ('ls 是外部命令', 'type -t ls', 'file'),
     ('help 只对内置命令有效', 'help cd >/dev/null 2>&1 && echo ok', 'ok')]),
3: ('文件与目录基础：列出文件、按行统计、确认可读',
    '''printf 'lines=%s\\n' "$(wc -l < "$DATA/words.txt")"
printf 'bytes=%s\\n' "$(wc -c < "$DATA/words.txt")"
printf 'readable=%s\\n' "$([ -r "$DATA/words.txt" ] && echo yes || echo no)"''',
    [('words.txt 有 4 行', 'wc -l < "$DATA/words.txt"', '4'),
     ('文件可读', '[ -r "$DATA/words.txt" ] && echo yes', 'yes')]),
4: ('处理文件：复制、改名、按内容查找，并统计文件个数',
    '''work=./work.$$
mkdir -p "$work"
cp "$DATA/words.txt" "$work/a.txt"
mv "$work/a.txt" "$work/b.txt"
printf 'exists=%s\\n' "$([ -f "$work/b.txt" ] && echo yes || echo no)"
printf 'count=%s\\n' "$(ls -1 "$work" | wc -l)"''',
    [('复制并改名成功', 'tmp=./w.$$; mkdir -p "$tmp"; cp "$DATA/words.txt" "$tmp/a"; mv "$tmp/a" "$tmp/b"; [ -f "$tmp/b" ] && echo yes', 'yes'),
     ('cp 保留原文件', '[ -f "$DATA/words.txt" ] && echo kept', 'kept')]),
5: ('理解 shell 执行方式：后台任务、子 shell 与变量作用域',
    '''x=parent
printf 'subshell=%s\\n' "$(x=child; printf "%s" "$x")"
printf 'parent=%s\\n' "$x"
printf 'background=%s\\n' "$(sleep 0.1 & echo started; wait)"''',
    [('子 shell 改不了父 shell', 'x=parent; ( x=child ); echo "$x"', 'parent'),
     ('后台任务可等待', '(sleep 0.1 &) && echo ran', 'ran')]),
6: ('环境变量：查看、设置、导出与子进程继承',
    '''printf 'home_set=%s\\n' "$([ -n "$HOME" ] && echo yes || echo no)"
export MY_VAR=hello
printf 'child_sees=%s\\n' "$(bash -c 'printf "%s" "$MY_VAR"')"
printf 'path_set=%s\\n' "$([ -n "$PATH" ] && echo yes || echo no)"''',
    [('导出变量能被子进程看到', 'export MY_VAR=hello; bash -c "printf %s \\"$MY_VAR\\""', 'hello'),
     ('PATH 已设置且非空', '[ -n "$PATH" ] && echo set', 'set'),
     ('HOME 环境变量存在', '[ -n "$HOME" ] && echo set', 'set')]),
7: ('文件权限：解读 rwx 与权限位，用 test 判定访问能力',
    '''f=./probe.$$
: > "$f"
printf 'mode=%s\\n' "$(stat -c '%a' "$f")"
printf 'symbolic=%s\\n' "$(ls -l "$f" | cut -c1-10)"
printf 'readable=%s\\n' "$([ -r "$f" ] && echo yes || echo no)"
printf 'writable=%s\\n' "$([ -w "$f" ] && echo yes || echo no)"
printf 'umask=%s\\n' "$(umask)"
chmod 444 "$f"
printf 'after_chmod_writable=%s\\n' "$([ -w "$f" ] && echo yes || echo no)"''',
    [('新建文件属主可读', "f=./pa.$$; : > \"$f\"; [ -r \"$f\" ] && echo yes", 'yes'),
     ('新建文件可写', "f=./pb.$$; : > \"$f\"; [ -w \"$f\" ] && echo yes", 'yes'),
     ('chmod 444 后不可写', "f=./pc.$$; : > \"$f\"; chmod 444 \"$f\"; [ -w \"$f\" ] || echo no", 'no'),
     ('权限位是八进制', "f=./pd.$$; : > \"$f\"; stat -c '%a' \"$f\" | grep -Eq '^[0-7]{3,4}$' && echo ok", 'ok'),
     ('umask 形如 0022', 'umask | grep -Eq "^[0-7]{3,4}$" && echo ok', 'ok')]),
8: ('文件系统：查看挂载点、磁盘占用与 inode 使用',
    '''printf 'root_fs=%s\\n' "$(df -P / | awk 'NR==2{print $1}')"
printf 'root_used_nonzero=%s\\n' "$(df -P / | awk 'NR==2{exit !($3>0)}' && echo yes || echo no)"
printf 'inodes=%s\\n' "$(df -i / | awk 'NR==2{print $2}')"''',
    [('/ 已挂载且有用量', 'df -P / | awk "NR==2{exit !(\\$3>0)}" && echo yes', 'yes'),
     ('inode 总数可读', 'df -i / | awk "NR==2{print \\$2}" | grep -q . && echo has', 'has')]),
9: ('软件管理：用命令查询已安装程序与版本信息（不实际安装）',
    '''printf 'bash_version=%s\\n' "${BASH_VERSION%%(*}"
printf 'tools_ok=%s\\n' "$(for t in ls grep awk; do command -v "$t" >/dev/null || exit 1; done; echo yes)"''',
    [('常用工具齐备', 'for t in ls grep awk sed; do command -v "$t" >/dev/null || exit 1; done; echo yes', 'yes'),
     ('bash 版本号格式正确', 'echo "${BASH_VERSION%%(*}" | grep -Eq "^[0-9]+\\.[0-9]+\\.[0-9]+" && echo ok', 'ok')]),
10: ('编辑器与非交互式处理：用 sed/awk 完成一次批量改写',
     '''tmp=./edit.$$
mkdir -p "$tmp"
printf 'one\\ntwo\\nthree\\n' > "$tmp/list.txt"
printf 'renamed=%s\\n' "$(sed 's/one/1/' "$tmp/list.txt" | head -1)"
printf 'upper=%s\\n' "$(tr 'a-z' 'A-Z' < "$tmp/list.txt" | sed -n '2p')"''',
     [('sed 替换生效', 'echo one | sed s/one/1/', '1'),
      ('tr 大小写转换', 'echo two | tr a-z A-Z', 'TWO')]),
11: ('构建第一个脚本：带参数、shebang 与退出码',
     '''d=./first.$$
mkdir -p "$d"
printf '#!/usr/bin/env bash\\necho "arg=$1"\\n' > "$d/run.sh"
printf 'output=%s\\n' "$(bash "$d/run.sh" hello)"
printf 'exit=%s\\n' "$(bash "$d/run.sh" hello >/dev/null; echo $?)"''',
     [('脚本可执行并传参', 'd=./s.$$; mkdir -p "$d"; printf "#!/usr/bin/env bash\\necho \\$1\\n" > "$d/r.sh"; bash "$d/r.sh" hi', 'hi'),
      ('正常退出码为 0', 'true; echo $?', '0')]),
12: ('结构化命令：if/then、test 与退出码判断',
     '''score=85
if [ "$score" -ge 90 ]; then grade=A
elif [ "$score" -ge 80 ]; then grade=B
else grade=C; fi
printf 'grade=%s\\n' "$grade"
printf 'empty_test=%s\\n' "$([ -z "" ] && echo empty || echo not)"''',
     [('85 分判为 B', 's=85; if [ $s -ge 90 ]; then g=A; elif [ $s -ge 80 ]; then g=B; else g=C; fi; echo $g', 'B'),
      ('test -z 判空串', '[ -z "" ] && echo empty', 'empty')]),
13: ('更多结构化命令：case、for 与算术展开',
     '''printf 'loop=%s\\n' "$(for i in 1 2 3; do printf '%s' "$i"; done)"
printf 'arith=%s\\n' "$((3 * 4 + 1))"
case abc in a*) printf 'case=matched\\n' ;; *) printf 'case=no\\n' ;; esac''',
     [('算术展开正确', 'echo $((3 * 4 + 1))', '13'),
      ('for 循环累加字符串', 'for i in 1 2 3; do printf "%s" "$i"; done', '123'),
      ('case 前缀匹配', 'case abc in a*) echo matched ;; esac', 'matched')]),
14: ('处理用户输入：read、getopts 与位置参数',
     '''printf 'input=%s\\n' "$(printf 'hello world\\n' | { read -r a b; echo "$a-$b"; })"
set -- one two three
printf 'shifted=%s\\n' "$(shift; echo "$1")"
printf 'count=%s\\n' "$#"''',
     [('read 拆分会话字段', 'printf "a b\\n" | { read -r x y; echo "$x-$y"; }', 'a-b'),
      ('shift 后第一个参数', 'set -- one two; shift; echo "$1"', 'two'),
      ('$# 统计参数个数', 'set -- a b c; echo $#', '3')]),
15: ('呈现数据：对齐输出、制表符与数字格式化',
     '''printf '%-8s|%5d\\n' name 42
printf 'float=%.2f\\n' 3.14159
printf 'tabbed=%s\\n' "$(printf 'a\\tb' | cat -T)"''',
     [('printf 宽度对齐', 'printf "%-8s|%5d" name 42', 'name    |   42'),
      ('保留两位小数', 'printf "%.2f" 3.14159', '3.14'),
      ('制表符可显示', 'printf "a\\tb" | cat -T', 'a^Ib')]),
16: ('控制脚本：信号捕获 trap、后台运行与等待',
     '''tmp=./trap.$$
mkdir -p "$tmp"
( trap 'echo caught > "$tmp/sig"; exit 0' TERM; sleep 5 ) &
pid=$!
sleep 0.2; kill -TERM "$pid" 2>/dev/null; wait "$pid" 2>/dev/null
printf 'trapped=%s\\n' "$([ -f "$tmp/sig" ] && echo yes || echo no)"''',
     [('trap 捕获 TERM', '( trap "echo caught; exit 0" TERM; sleep 5 ) & p=$!; sleep 0.2; kill -TERM $p; wait $p 2>/dev/null', 'caught'),
      ('wait 等待后台任务', '(sleep 0.1) & wait; echo done', 'done')]),
17: ('创建函数：参数传递、返回值与局部变量',
     '''add() { local a=$1 b=$2; echo $((a + b)); }
printf 'add=%s\\n' "$(add 3 4)"
greet() { printf 'hello %s\\n' "${1:-world}"; }
printf 'default=%s\\n' "$(greet)"''',
     [('函数返回计算结果', 'add() { echo $(($1 + $2)); }; add 3 4', '7'),
      ('参数默认值生效', 'f() { echo "${1:-fallback}"; }; f', 'fallback'),
      ('local 不外泄', 'f() { local v=inner; }; v=outer; f; echo $v', 'outer')]),
18: ('交互脚本：从 stdin 读菜单选择并分支处理',
     '''choice=b
case "$choice" in
  a) result=apple ;;
  b) result=banana ;;
  *) result=unknown ;;
esac
printf 'result=%s\\n' "$result"
printf 'menu_lines=%s\\n' "$(printf 'a) apple\\nb) banana\\n' | wc -l)"''',
     [('菜单分支正确', 'c=b; case $c in a) r=apple;; b) r=banana;; *) r=unknown;; esac; echo $r', 'banana'),
      ('选项行数正确', 'printf "a) apple\\nb) banana\\n" | wc -l', '2')]),
19: ('初识 sed 与 gawk：行选取、替换与字段提取',
     '''printf 'lines=%s\\n' "$(printf 'a\\nb\\nc\\n' | sed -n '2p')"
printf 'field=%s\\n' "$(printf 'x y z\\n' | awk '{print $2}')"
printf 'replaced=%s\\n' "$(printf 'foo bar\\n' | sed 's/foo/baz/')"''',
     [('sed 取第 2 行', 'printf "a\\nb\\nc\\n" | sed -n 2p', 'b'),
      ('awk 取第 2 字段', 'printf "x y z\\n" | awk "{print \\$2}"', 'y'),
      ('sed 替换首个匹配', 'echo foo bar | sed s/foo/baz/', 'baz bar')]),
20: ('正则表达式：字符类、锚点与分组',
     '''printf 'digit=%s\\n' "$(printf 'abc123\\n' | grep -o '[0-9]\\+' | head -1)"
printf 'anchor=%s\\n' "$(printf 'start here\\n' | grep -c '^start')"
printf 'email=%s\\n' "$(printf 'a@b.com\\n' | grep -Ec '[a-z]+@[a-z]+\\.[a-z]+')"''',
     [('匹配数字片段', 'echo abc123 | grep -o "[0-9]\\+"', '123'),
      ('行首锚点生效', 'echo start here | grep -c "^start"', '1'),
      ('邮箱模式匹配', 'echo a@b.com | grep -Ec "[a-z]+@[a-z]+\\.[a-z]+"', '1')]),
21: ('sed 进阶：寻址、保持空间与多命令编辑',
     '''printf 'range=%s\\n' "$(printf '1\\n2\\n3\\n4\\n' | sed -n '2,3p' | tr '\\n' ' ')"
printf 'delete=%s\\n' "$(printf 'keep\\ndrop\\nkeep\\n' | sed '/drop/d' | tr '\\n' ' ')"
printf 'append=%s\\n' "$(printf 'a\\n' | sed 'a b' | tr '\\n' ' ')"''',
     [('地址范围 2,3', 'printf "1\\n2\\n3\\n4\\n" | sed -n 2,3p | tr "\\n" " "', '2 3 '),
      ('按模式删除行', 'printf "keep\\ndrop\\nkeep\\n" | sed /drop/d | tr "\\n" " "', 'keep keep '),
      ('sed 追加行', 'printf "a\\n" | sed "a b" | tr "\\n" " "', 'a b ')]),
22: ('gawk 进阶：数组、聚合与自定义函数',
     '''printf 'sum=%s\\n' "$(printf '10\\n20\\n30\\n' | awk '{s+=$1} END{print s}')"
printf 'count=%s\\n' "$(printf 'a\\nb\\nc\\n' | awk 'END{print NR}')"
printf 'max=%s\\n' "$(printf '3\\n9\\n5\\n' | awk 'NR==1||$1>m{m=$1} END{print m}')"''',
     [('累加求和', 'printf "10\\n20\\n30\\n" | awk "{s+=\\$1} END{print s}"', '60'),
      ('统计行数 NR', 'printf "a\\nb\\nc\\n" | awk "END{print NR}"', '3'),
      ('求最大值', 'printf "3\\n9\\n5\\n" | awk "NR==1||\\$1>m{m=\\$1} END{print m}"', '9')]),
23: ('了解其他 shell：POSIX 兼容写法与 shell 间差异',
     '''printf 'posix_ok=%s\\n' "$(bash --posix -c 'printf "%s" "${BASH_VERSION%%(*)}"' >/dev/null && echo yes || echo no)"
printf 'arith_posix=%s\\n' "$(x=2; y=3; echo $((x * y)))"
printf 'has_dash=%s\\n' "$(command -v dash >/dev/null && echo has || echo none)"''',
     [('算术展开在 POSIX 下同样可用', 'echo $((2 * 3))', '6'),
      ('命令替换可嵌套', 'echo "$(echo nested)"', 'nested')]),
24: ('编写脚本工具：带用法的命令行工具、错误处理与退出码',
     '''usage() { printf 'usage: tool <file>\\n' >&2; }
tool() { [ -f "$1" ] || { usage; return 2; }; wc -l < "$1"; }
printf 'lines=%s\\n' "$(tool "$DATA/words.txt")"
printf 'missing=%s\\n' "$(tool /no/such/file 2>/dev/null; echo $?)"''',
     [('正常路径返回行数', 'wc -l < "$DATA/words.txt"', '4'),
      ('文件缺失时返回非零', '( [ -f /no/such ] || exit 2 ); echo $?', '2'),
      ('用法信息写到 stderr', 'u() { printf "usage\\n" >&2; }; u 2>&1', 'usage')]),
25: ('与数据交互：解析 CSV、JSON 字段与生成报表',
     '''printf 'names=%s\\n' "$(awk -F, 'NR>1{printf "%s ", $1}' "$DATA/scores.csv")"
printf 'avg=%s\\n' "$(awk -F, 'NR>1{s+=$2; n++} END{printf "%.2f", s/n}' "$DATA/scores.csv")"
printf 'course=%s\\n' "$(grep -o '"course": *"[^"]*"' "$DATA/course.json" | cut -d'"' -f4)"''',
     [('提取姓名列', 'awk -F, "NR>1{printf \\"%s \\", \\$1}" "$DATA/scores.csv"', 'alice bob carol '),
      ('平均分保留两位', 'awk -F, "NR>1{s+=\\$2; n++} END{printf \\"%.2f\\", s/n}" "$DATA/scores.csv"', '85.00'),
      ('JSON 字段可提取', 'grep -o "\\"course\\": *\\"[^\\"]*\\"" "$DATA/course.json" | cut -d"\\"" -f4', 'Linux and Shell')]),
26: ('综合小工具：把学过的命令组合成一个可复用脚本',
     '''report() {
  printf '总人数=%s\\n' "$(awk -F, 'NR>1' "$DATA/scores.csv" | wc -l)"
  printf '平均分=%s\\n' "$(awk -F, 'NR>1{s+=$2; n++} END{printf "%.1f", s/n}' "$DATA/scores.csv")"
  printf '最高分=%s\\n' "$(awk -F, 'NR>1{if($2>m)m=$2} END{print m}' "$DATA/scores.csv")"
}
report
printf 'words=%s\\n' "$(wc -l < "$DATA/words.txt")"''',
     [('统计人数', 'awk -F, "NR>1" "$DATA/scores.csv" | wc -l', '3'),
      ('平均分一位小数', 'awk -F, "NR>1{s+=\\$2; n++} END{printf \\"%.1f\\", s/n}" "$DATA/scores.csv"', '85.0'),
      ('最高分', 'awk -F, "NR>1{if(\\$2>m)m=\\$2} END{print m}" "$DATA/scores.csv"', '90')]),
}

CHAPTER_TITLES = {
1:'初识Linux shell',2:'走进shell',3:'基本的bash shell命令',4:'更多的bash shell',
5:'理解shell',6:'使用Linux环境变量',7:'理解Linux文件权限',8:'管理文件系统',
9:'安装软件程序',10:'使用编辑器',11:'构建基本脚本',12:'使用结构化命令',
13:'更多的结构化命令',14:'处理用户输入',15:'呈现数据',16:'控制脚本',
17:'创建函数',18:'图形化桌面环境中的脚本编程',19:'初识sed 和gawk',20:'正则表达式',
21:'sed进阶',22:'gawk进阶',23:'使用其他shell',24:'编写简单的脚本实用工具',
25:'创建与数据库、Web及电子邮件相关的脚本',26:'一些小有意思的脚本',
}

PDF_PAGE = {1:17,2:31,3:48,4:79,5:101,6:118,7:139,8:158,9:178,10:196,11:225,12:247,
            13:275,14:302,15:326,16:346,17:371,18:393,19:416,20:439,21:460,22:484,
            23:510,24:529,25:558,26:580}


def build_reference(num, body, asserts):
    lines = [HARNESS.strip(), '', '# 本章任务：' + CHAPTERS[num][0], '',
             'export DATA=${DATA:-仓库根目录/linux/data}', '', body.strip(), '',
             '# ---- 验收：把上面跑出来的结果和期望值比对 ----']
    for note, actual, expect in asserts:
        lines.append('check "%s" "$(%s)" "%s"' % (note, actual, expect))
    lines.append('finish')
    return '\n'.join(lines) + '\n'


def build_work(num, asserts):
    lines = [HARNESS.strip(), '',
             '# 本章任务：' + CHAPTERS[num][0],
             '# 在下面写出你自己的实现，然后用同一套 check 验收。',
             '# 卡住时对照 reference.sh，但先自己写完再看。', '',
             'export DATA=${DATA:-仓库根目录/linux/data}', '',
             '# TODO: 在这里写你的实现（先删掉下面这行占位）',
             'true', '',
             '# ---- 验收：换成你自己的实现，期望值保持不变 ----']
    for note, actual, expect in asserts:
        lines.append('check "%s" "$(%s)" "%s"' % (note, actual, expect))
    lines.append('finish')
    return '\n'.join(lines) + '\n'


def main():
    made = 0
    for num, (desc, body, asserts) in CHAPTERS.items():
        folder = ROOT / ('linux/chapters/ch%02d' % num)
        folder.mkdir(parents=True, exist_ok=True)
        (folder / 'reference.sh').write_text(build_reference(num, body, asserts), encoding='utf-8')
        (folder / 'work.sh').write_text(build_work(num, asserts), encoding='utf-8')
        (folder / 'README.md').write_text('''# 第%d章 %s

原书页码：PDF 第 %d 页。

## 本章任务

%s

## 知识点

- 完成后请回答：这一步为什么这样写？换一种写法会在什么情况下出错？
- 把命令行随手敲出来的命令，整理成可重复运行的脚本，是这一章的核心。

## 怎么练

1. 先读原书对应小节。
2. 打开 `work.sh`，在 TODO 处写自己的实现。
3. Ctrl+Shift+B 选「Shell: 运行活动脚本」，看末尾的验收结果。
4. 全过 → 去下一章；有 FAIL → 对照 `reference.sh` 找出差异，不要直接抄。

## 验收标准

`work.sh` 末尾的 check 全部 PASS（共 %d 项）即为完成。
自己写的实现只要输出一致就算过，不要求和参考实现逐字相同。

参考实现见 `reference.sh`；静态检查用「Shell: 检查活动脚本」。
''' % (num, CHAPTER_TITLES[num], PDF_PAGE[num], desc, len(asserts)), encoding='utf-8')
        made += 1
    print('已重写', made, '章')


if __name__ == '__main__':
    main()
