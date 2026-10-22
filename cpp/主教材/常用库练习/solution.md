# 常用库分组练习：核对与解析

先写自己的调用与预测，再看本页；以下是自编配套，不是官方答案。每组参考可独立运行。[返回分组入口](README.md)。

## 数学库

abs(-2.5)=2.5；floor(-1.2)=-2、ceil=-1；向量(-1,1)方向135°。

[本组参考](参考实现/math.cpp)。

## 字符处理

空格可打印且为空白；换行不可打印但为空白；字符分类可以重叠。

[本组参考](参考实现/characters.cpp)。

## 字符串

修改后image_008.png.bak；find失败为npos；a\0b的string长度3、strlen长度1。

[本组参考](参考实现/strings.cpp)。

## 流与格式

setw只影响下一个字段；其他状态可能保留；clear清状态，ignore丢坏行，两者职责不同。

[本组参考](参考实现/streams.cpp)。

## 容器常用接口

reserve不改变size；栈后进先出、队列先进先出；map[]可能插入，find不插入；set去重。

[本组参考](参考实现/containers.cpp)。

## STL算法与回调

结果依次1 1 2 3 3 → 1 2 3 → 1 4 9 → 1 4。unique/remove_if返回逻辑尾，不缩容器；erase才改size。

[本组参考](参考实现/algorithms.cpp)。

## 类与所有权

(1,2)+(3,4)=(4,6)，原对象不变；move后原unique_ptr为空，新所有者仍指向7。

[本组参考](参考实现/objects.cpp)。

## 容易误判的边界

sqrt/log先查定义域；三角函数使用弧度，浮点数以容限核对。cctype用unsigned char输入，返回值只判断非0。find返回end或npos不能解引用。at会抛out_of_range，不用越界[]测试运气。string保存嵌入零字符，C字符串在第一个零处结束。

vector扩容可能使迭代器失效，故示例修改后重新获取begin，不保留旧迭代器继续访问。reserve可能给更多容量，不能断言capacity恰好等于请求值。stack/queue的pop没有返回值；先取值再pop，先判空。map[]读取缺失键也会插入，find仅查询。

流组中showpoint配fixed和precision(0)得到2.，noshowpoint后默认格式得到2。uppercase/nouppercase切换科学计数的E/e。clear重置流标志，但坏字符仍在；ignore到换行丢掉坏行后才能继续读取42。严格整数转换用局部值，失败不提交给调用者。

unique/remove_if后的尾部内容不作为答案核对；只处理返回的逻辑尾以前的区间，再erase。lower_bound不保证一定找到目标，仍需检查是否到end及元素是否相等。本例使用有序小整数，未声称适用于任意比较器或所有数值范围。

Point的成员私有，const查询不能修改对象，operator+返回新值。unique_ptr移动后旧所有者为空；不解引用它，也不对get()手动delete。RAII示例不代表已实现教材全部动态容器。

## 教材 strlib 适配调用

数字和文本是不同类型，转换返回新值；转换失败须区分语法与范围。toUpperCase返回副本，只处理ASCII小写字母。[题目、契约与解析](stanford-strings.md) · [18组参考核对](参考实现/stanford-strings.cpp)。本组共享自编适配头，不把它当作原始Stanford库的验收。
