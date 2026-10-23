# 第20章 · 习题8：手写 maxElement 与 countIf

> **要干什么：** 不看 `<algorithm>`，自己写两个函数模板：找最大元素的迭代器、统计满足谓词的元素个数。

## 1 · 题目是什么

输入：

```text
n
a1 a2 … an
q
even | odd | pos | neg | gt k | lt k | eq k     （q 行）
```

输出第一行是最大值和它第一次出现的下标，然后每条查询一行计数：

```text
max = 9 at 2
even = 2
gt 5 = 1
```

- 下标从 0 开始；
- `max` 遇到并列时取**第一个**。

原书习题 8（[PDF 第 637 页](../../../../../../books/cpp-roberts.pdf#page=637)）。**这里是题意改写与输入输出约定**：原书用`<algorithm>` 里的 `max_element` 与 `count_if`（习题 8、9），
本区改成从标准输入读、标准输出写，方便自动比对；题目的核心要求不变。

## 2 · 实现什么

两个函数都写成模板，`main` 里用 `lambda` 当谓词传进去：

- `template <typename IterType> IterType maxElement(IterType begin, IterType end);`
- `template <typename IterType, typename Predicate> int countIf(IterType begin, IterType end, Predicate pred);`

## 3 · 写在哪里

**work.cpp** 里的 `BEGIN 1` … `END 1`（maxElement 模板）和 `BEGIN 2` … `END 2`（countIf 模板）。
头文件、类定义、`main` 骨架都已给出，**只补这两个区**；补完把区里的占位注释（`// @@N@@`）或占位 `throw` 删掉。

保存后运行任务“本题：检查作答”核对。

<!-- dual-work -->
> **本题有两份作答：** `work.cpp` 是补写版（给好骨架，只补补全区），`from-scratch.cpp` 是从零写（只有题头）。
> **两份都能判分**——网页上文件下拉选哪个，就判哪个。

## 4 · 怎么做

1. 先自己写补全区，卡住 20 分钟再去看 `solution.md`。
2. 跑「检查本题」：本题登记 7 组样例，其中 4 组正常输出、3 组是非法输入（要求退出码 2、stdout 为空）。
3. 通过之后自己再造两组：一组边界、一组非法，确认结果仍然对。

## 5 · 文本格式

- 第一行 `max = 值 at 下标`，之后每条查询一行 `命令 = 个数`（`gt 5 = 1` 这种带参数的命令也照原样写）。
- n 或 q 越界、数字不够、未知命令、命令缺参数：返回 2，**stdout 为空**。

输入样例：

```text
5
3 -1 9 9 0
4
even
gt 2
lt 0
eq 9
```

期望输出：

```text
max = 9 at 2
even = 1
gt 2 = 3
lt 0 = 1
eq 9 = 2
```

## 6 · 哪个是判分的

**只有一个：这里的“检查本题”，或 VS Code 任务“本题：检查作答”。** 两处是同一个工具，
比对本题登记的 7 组样例，标准输出和退出码都逐字比对。

1. 打开本题自己的作答文件，保存修改。
2. **运行（不判分）：** 任务“本题：运行作答”，或 `python tools/run-current.py <文件>`。
3. **核对：** 任务“本题：检查作答”，或 `python tools/check-current.py <文件>`。

## 7 · 做完的标准

页面显示“登记样例全部通过”，并且你能自己再造两组输入验证结果。这只是固定样例的结果，
边界情况仍要自己想一遍；工具不会自动记录完成状态。

做完再看：[解析](solution.md) · [参考代码](reference.cpp)
