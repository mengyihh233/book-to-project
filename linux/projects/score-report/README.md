# 综合练习：成绩CSV报表

把Linux书中的变量、路径引用、退出状态、重定向与awk统计串起来，处理真实文件。

## 输入与输出

输入是UTF-8文本，表头严格为name,score。姓名非空且不重复，成绩是0到100的十进制数。支持CRLF、空行和含空格路径；本练习的简单CSV格式不支持带引号字段、姓名中的逗号、BOM或科学计数法。
输出人数、平均分、最低分、最高分和及格人数。只有表头时输出人数0与暂无成绩；非法数据写到stderr并返回2，不能输出半份正常报告。

在work.sh实现，参考实现为reference.sh与report.awk。样例文件是sample.csv，程序只读输入。

## 在VS Code运行

终端→运行任务→“Linux项目：运行成绩报表”。
任务维护工具tools/check-projects.py（只检查参考项目）会检查正常输入、空数据、重复姓名、越界成绩、CRLF和路径含空格等情况。

在Ubuntu终端也可以执行：

```bash
bash 仓库根目录/linux/projects/score-report/reference.sh
bash 仓库根目录/linux/projects/score-report/reference.sh '仓库根目录/linux/projects/score-report/sample.csv' > my-report.txt
```

## 解题思路

Shell负责参数与路径检查；awk负责逐行解析与统计。先校验表头与每行数据，再更新计数；END中只在没有错误时生成报告。
姓名重复利用关联数组检查。平均分只在人数非零时计算。以退出状态把“合法的空数据”与“非法输入”区分开。

扩展任务：支持完整CSV语法时可使用Python csv模块；要先明确支持范围，再替换解析器并添加引号、逗号与换行字段测试。
