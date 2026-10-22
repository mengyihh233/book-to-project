# 第6章选做：有理数类 × Linux CMake

[文件和目录怎么用](../../../README.md)：先README，再自己的work，最后解析；自动检查文件由任务读取。

对应[原书6.3有理数，PDF206起](../../../../导入教材.md#这两份文件为什么不在仓库里)，规范化规则见PDF209。这是自编配套和现代 C++17 适配，不是新增原书题号，也不声称复刻历史库。已有[银行账户主练习](../../章节学习/第06章 类的设计/README.md)保留；两组按薄弱点选一组，不必重复刷。

**只编辑 [我的作答/rational.cpp](我的作答/rational.cpp)**。共用接口在 include/rational.hpp，demo.cpp 是调用者，tests.cpp 是核对程序。参考在 参考实现/rational.cpp，[提示解析另放](solution.md)。同一份源码同时用于 C++ 类设计和 CMake，不另复制 Linux 版本。

## 先想，再按三步写

1. **10分钟：规范表示。** 先预测2/-4、-2/-4、0/-7、1/0。实现 normalized 和构造函数：分母正、约分、0统一为0/1；无效分母抛 invalid_argument。先运行构造相关代码，不急着实现四则运算。
2. **15分钟：返回新值。** 实现 +、-、*、/，不改两个操作数。先算1/2+1/3，再算连续相加1/6；除以零有理数须拒绝。构造成功和每次运算成功后都保持同样不变量。
3. **10分钟：边界与说明。** 再测负号、整数极值和结果范围。先提升到int64再乘，不要先用int32乘完才转换。结果约分后存储超出范围抛out_of_range，不能静默绕回。

本适配存储有符号32位分子和正32位分母；中间计算用64位，**不是任意精度分数库**。失败使用标准异常，和原书历史error机制不同。getter、==和流输出接口已提供，重点放在构造、运算与不变量；无须写内存管理或图形后端。

## Linux 中运行

在 Ubuntu 的 Konsole，先阅读 [Linux CMake 教学](../../../../guide/Linux-CMake教学.md)，其中逐项解释 -S/-B、目标、库、Debug、测试和常见错误。

```bash
src=仓库根目录/cpp/主教材/综合项目/有理数与CMake
build="$HOME/.cache/book-learning/cmake/rational-work-cn"
cmake -S "$src" -B "$build" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBOOK_USE_REFERENCE=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$build" --parallel 2
"$build/rational_demo"
ctest --test-dir "$build" --output-on-failure
```

初始 work 能编译，但运行明确报 NOT_IMPLEMENTED，测试失败是尚未作答，不是 CMake 安装失败。22项检查全部通过后，再遮住解析解释至少一个错误输入。参考模式的通过不登记成个人完成。

想先学 CMake，可按教程用独立 rational-reference-cn 构建目录和 BOOK_USE_REFERENCE=ON 看完整程序；回头仍在原 work 中作答。不要把参考代码复制覆盖 work。

## VS Code 入口

Ubuntu 原生 VS Code 或 Remote WSL 打开 focus-wsl.code-workspace，运行任务中有 **CMake: 配置有理数作答 / 构建有理数作答 / 运行有理数作答 / 检查有理数作答**。调试选 **CMake: GDB调试有理数作答**。

这是多文件项目，使用上面 CMake 任务；普通“编译运行当前文件”只编译单文件，不能替代项目链接。编译器与 GDB 仍是 Ubuntu 的工具，不混入 Windows .exe。

## 阅读代码中的原书注释

新模板已按“原书定位 → 概念概括 → 观察点 → TODO”加中文注释：先看类的用户观点、规范表示与构造不变量，再动手实现。注释是中文转述和自编配套，不把未完成代码标成原书答案；完整解法仍在reference和solution，已有学生作答不被批量覆盖。
