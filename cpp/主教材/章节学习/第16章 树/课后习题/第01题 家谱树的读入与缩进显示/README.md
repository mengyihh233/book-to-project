# 第16章 · 习题1：家谱树的读入与缩进显示

> **要干什么：** 把一个「孩子:父亲」的名单建成一棵树，再按辈分逐层缩进打印出来。

## 1 · 题目是什么

第一行是根节点名字；之后每行一个 `孩子:父亲`（冒号两边可以有空格），
**父亲一定在文件的前面出现过**。空行忽略。

例如：

```text
William I
Robert:William I
William II:William I
Adela:William I
Stephen:Adela
Henry I:William I
William:Henry I
Matilda:Henry I
Henry II:Matilda
```

输出时每一代缩进两个空格，同一代按**输入顺序**（不是字典序）排列：

```text
William I
  Robert
  William II
  Adela
    Stephen
  Henry I
    William
    Matilda
      Henry II
```

原书习题 1（[PDF 第 502 页](../../../../../../books/cpp-roberts.pdf#page=502)）。**这里是题意改写与输入输出约定**：原书用`FamilyTreeNode` + `readFamilyTree(filename)` + `displayFamilyTree(tree)`，
本区改成从标准输入读、标准输出写，方便自动比对；题目的核心要求不变。

## 2 · 实现什么

结构体 `FamilyTreeNode`（名字 + 孩子指针数组）已经给好，你要写两个函数：

- `readFamilyTree()`：读根节点、再逐行读 `孩子:父亲`，用一张 `名字 → 结点指针` 的表找到父亲、
  挂上孩子；
- `displayFamilyTree(tree)`：先序递归，深度 × 2 个空格 + 名字。

## 3 · 写在哪里

**work.cpp** 里的 `BEGIN 1` … `END 1`（建树）和 `BEGIN 2` … `END 2`（递归显示）。
头文件、类定义、`main` 骨架都已给出，**只补这两个区**；补完把区里的占位注释（`// @@N@@`）或占位 `throw` 删掉。

保存后运行任务“本题：检查作答”核对。

<!-- dual-work -->
> **本题有两份作答：** `work.cpp` 是补写版（给好骨架，只补补全区），`from-scratch.cpp` 是从零写（只有题头）。
> **两份都能判分**——网页上文件下拉选哪个，就判哪个。

## 4 · 怎么做

1. 先自己写补全区，卡住 20 分钟再去看 `solution.md`。
2. 跑「检查本题」：本题登记 8 组样例，其中 3 组正常输出、5 组是非法输入（要求退出码 2、stdout 为空）。
3. 通过之后自己再造两组：一组边界、一组非法，确认结果仍然对。

## 5 · 文本格式

- 每行 `空格×深度 + 名字`，根节点不缩进。
- 缺根节点行、名字为空、某行没有冒号、父亲还没出现过、同一个名字出现两次：返回 2，**stdout 为空**。

输入样例：

```text
William I
Robert:William I
William II:William I
Adela:William I
Stephen:Adela
Henry I:William I
William:Henry I
Matilda:Henry I
Henry II:Matilda
```

期望输出：

```text
William I
  Robert
  William II
  Adela
    Stephen
  Henry I
    William
    Matilda
      Henry II
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
