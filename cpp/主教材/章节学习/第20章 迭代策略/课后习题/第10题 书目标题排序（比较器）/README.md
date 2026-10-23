# 第20章 · 习题10：书目标题排序（比较器）

> **要干什么：** 给 `std::sort` 写一个比较器：忽略大小写、忽略除空格外的标点、忽略开头的 a / an / the。

## 1 · 题目是什么

读 n 行书名（每行一条，可以带空格和标点），按下面的规则排序后原样输出：

1. **忽略大小写**；
2. **忽略除空格外的标点**（`,` `!` `.` `'` `"` `:` `;` `?` 等一律不算）；
3. **忽略标题开头的 `a`、`an`、`the`**（只有整词才算，`Theatre` 不是 `the`）；
4. 两条标题「规范化之后」相同的话，按**原字符串**比较，保证输出顺序唯一。

例如 `The Great Gatsby`、`a tale of two cities`、`1984` 排序后：

```text
1984
The Great Gatsby
a tale of two cities
```

原书习题 10（[PDF 第 637 页](../../../../../../books/cpp-roberts.pdf#page=637)）。**这里是题意改写与输入输出约定**：原书用`lessIgnoringCase` 与习题 11 的 `titleComesBefore`，
本区改成从标准输入读、标准输出写，方便自动比对；题目的核心要求不变。

## 2 · 实现什么

`main` 的读入、`std::sort`、输出都已经给好，你要写两个函数：

- `normalize(title)`：转小写 → 去掉标点（空格保留）→ 合并连续空格 → 去掉开头的冠词；
- `titleComesBefore(a, b)`：先比 `normalize` 的结果，相同再比原串。

## 3 · 写在哪里

**work.cpp** 里的 `BEGIN 1` … `END 1`（规范化标题）和 `BEGIN 2` … `END 2`（两级比较）。
头文件、类定义、`main` 骨架都已给出，**只补这两个区**；补完把区里的占位注释（`// @@N@@`）或占位 `throw` 删掉。

保存后运行任务“本题：检查作答”核对。

<!-- dual-work -->
> **本题有两份作答：** `work.cpp` 是补写版（给好骨架，只补补全区），`from-scratch.cpp` 是从零写（只有题头）。
> **两份都能判分**——网页上文件下拉选哪个，就判哪个。

## 4 · 怎么做

1. 先自己写补全区，卡住 20 分钟再去看 `solution.md`。
2. 跑「检查本题」：本题登记 8 组样例，其中 6 组正常输出、2 组是非法输入（要求退出码 2、stdout 为空）。
3. 通过之后自己再造两组：一组边界、一组非法，确认结果仍然对。

## 5 · 文本格式

- 每行一条原始标题（**不做任何改写**，大小写和标点都原样保留），顺序按规则排。
- n 越界、标题为空或超过 100 个字符、行数不足：返回 2，**stdout 为空**。

输入样例：

```text
5
The Great Gatsby
a tale of two cities
An Artist of the Floating World
the old man and the sea
1984
```

期望输出：

```text
1984
An Artist of the Floating World
The Great Gatsby
the old man and the sea
a tale of two cities
```

## 6 · 哪个是判分的

**只有一个：这里的“检查本题”，或 VS Code 任务“本题：检查作答”。** 两处是同一个工具，
比对本题登记的 8 组样例，标准输出和退出码都逐字比对。

1. 打开本题自己的作答文件，保存修改。
2. **运行（不判分）：** 任务“本题：运行作答”，或 `python tools/run-current.py <文件>`。
3. **核对：** 任务“本题：检查作答”，或 `python tools/check-current.py <文件>`。

## 7 · 做完的标准

页面显示“登记样例全部通过”，并且你能自己再造两组输入验证结果。这只是固定样例的结果，
边界情况仍要自己想一遍；工具不会自动记录完成状态。

做完再看：[解析](solution.md) · [参考代码](reference.cpp)
