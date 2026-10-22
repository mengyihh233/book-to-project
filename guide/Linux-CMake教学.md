> 本教程中的CMake任务在Ubuntu/WSL窗口使用；打开有理数项目文件夹或既有WSL学习工作区，任务名称与下文一致。

# Linux CMake：从能编译到能组织一个项目

本教程用[有理数类项目](../cpp/主教材/综合项目/有理数与CMake/README.md)贯穿，不再复制一套 C++。命令在 **Ubuntu-22.04 的 Konsole、Ubuntu原生VS Code终端或Remote WSL终端**执行；不是 Windows PowerShell。先做1—3节即可，调试与变化练习按需补。

## 1. 先分清四个工具

| 工具 | 工作 | 本项目中的例子 |
|---|---|---|
| GCC / g++ | 把C++编译和链接成程序 | 真正处理rational.cpp、demo.cpp |
| CMake | 描述目标、依赖和编译要求，生成构建文件 | 读取CMakeLists.txt，生成build.ninja |
| Ninja | 按生成规则执行构建，只重做受影响的部分 | 由cmake --build调用 |
| CTest | 运行已登记的测试并汇总结果 | rational_contract内有22项检查 |

先在当前 Ubuntu 终端确认：

```bash
g++ --version
cmake --version
ninja --version
```

这些工具已装好，不必重装。项目要求C++17、CMake至少3.16；教程以本机Ubuntu22.04自带版本验收。CMake不是编译器，安装CMake也不会自动把任意缺失的第三方库装好。

## 2. 第一次：用参考程序学构建

这里只观察构建流程，不算自己完成了类设计。源码始终一份，构建产物放Linux缓存目录：

```bash
src=仓库根目录/cpp/主教材/综合项目/有理数与CMake
build="$HOME/.cache/book-learning/cmake/rational-reference-cn"
cmake -S "$src" -B "$build" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBOOK_USE_REFERENCE=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$build" --parallel 2
"$build/rational_demo"
ctest --test-dir "$build" --output-on-failure
```

demo应输出精确和1/1、规范化的-1/2；CTest应显示1个测试通过，该测试内部执行22项契约核对。测试条目数与断言数不是一回事。完整参考和解析可在[项目目录](../cpp/主教材/综合项目/有理数与CMake/README.md)查看。

| 参数 | 含义 |
|---|---|
| -S | 源码目录，里面有CMakeLists.txt |
| -B | 本次构建目录，缓存、目标文件和程序都写这里 |
| -G Ninja | 选择Ninja生成器 |
| -DCMAKE_BUILD_TYPE=Debug | 生成适合GDB的调试构建；适用于这里的单配置Ninja |
| -DBOOK_USE_REFERENCE=ON | 本项目自定义开关，选择参考实现 |
| -DCMAKE_EXPORT_COMPILE_COMMANDS=ON | 导出compile_commands.json，供编辑器或分析工具读取实际编译参数 |

`src`、`build`是当前终端变量；重开终端可重新设置，不代表重新安装。Linux缓存文件放在新Ubuntu的D盘虚拟磁盘里；源码在共享D盘目录，不复制教材。

## 3. 换成自己的作答

编辑[work/rational.cpp](../cpp/主教材/综合项目/有理数与CMake/我的作答/rational.cpp)。使用另一构建目录：

```bash
src=仓库根目录/cpp/主教材/综合项目/有理数与CMake
build="$HOME/.cache/book-learning/cmake/rational-work-cn"
cmake -S "$src" -B "$build" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBOOK_USE_REFERENCE=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$build" --parallel 2
"$build/rational_demo"
ctest --test-dir "$build" --output-on-failure
```

初始模板会报NOT_IMPLEMENTED；说明程序已编译运行、实现还没写。不要改成参考模式来“修好”自己的测试，也不用重装环境。实现中间步骤时，可先运行自己的小样例；22项全部检查要等四则运算都完成。

之后只改.cpp，通常再次执行cmake --build即可；头文件变化会触发相关目标重编译。修改CMakeLists.txt或配置选项时可重新运行配置命令。`-D`值保存在该构建目录的CMakeCache.txt中，省略开关不会自动恢复默认。

## 4. 读懂CMakeLists，不背全套语法

依次打开项目的[CMakeLists.txt](../cpp/主教材/综合项目/有理数与CMake/CMakeLists.txt)，对照这几处：

1. cmake_minimum_required和project声明工具底线及C++语言。
2. option选择work或reference，保证库里只有一份Rational实现。
3. add_library创建静态库rational；它没有main。
4. target_include_directories的PUBLIC让使用库的程序也能找到rational.hpp；target_compile_features把C++17要求一并传递。
5. add_executable分别创建demo与检查程序，各有自己的main；target_link_libraries把它们连到rational。
6. include(CTest)启用测试支持，add_test登记可执行检查程序。

不把所有.cpp通配塞进同一目标，否则可能同时装入两个main或两套Rational实现。头文件声明接口，.cpp实现函数；只include头文件不等于链接了实现文件。静态库的.a文件也不能像程序那样直接运行。[CMake官方目标链接说明](https://cmake.org/cmake/help/v3.22/command/target_link_libraries.html)

## 5. VS Code：使用项目任务与调试配置

在Ubuntu原生VS Code或Remote WSL打开focus-wsl.code-workspace：

- 运行任务 **CMake: 配置有理数作答**，看清WORK mode。
- 运行 **CMake: 构建有理数作答**；只构建，不启动程序。
- 运行 **CMake: 运行有理数作答** 或 **CMake: 检查有理数作答**。
- 在自己的构造或加法实现设置断点，调试下拉选 **CMake: GDB调试有理数作答** 后按F5。该配置先构建项目，再启动rational_demo。

普通“本题：运行作答”用于其他单文件练习；本项目必须把库实现与调用者链接，选CMake任务。无需为这节先安装一堆扩展；已有C/C++扩展即可。会了命令行后，再按需学习CMake Tools扩展。

也可在Ubuntu终端手动调试：

```bash
gdb "$HOME/.cache/book-learning/cmake/rational-work-cn/rational_demo"
```

进入GDB后依次输入 `break main`、`run`、`next`，再看局部变量。quit退出。命令行GDB会单独验收；文档不会把配置存在当作已经替你点击GUI F5。

## 6. 三个小变化，仍用这个项目

每次只选一个，不另外开题：

1. 给demo增加一个负分母例子，预测哪些目标会重编译；用`cmake --build "$build" --verbose`观察，再恢复或保留自己的例子。
2. 用新的rational-release目录配置Release参考，运行相同CTest。本项目测试不依赖assert，Release也必须检查。
3. 在自己的实现中漏掉分母符号归一化，先预测哪个检查失败再运行，随后修复。不要修改共用测试让错误通过。

清理目标产物用 `cmake --build "$build" --target clean`，会保留源码和配置缓存。换编译器、生成器或切到Windows工具链时，新建独立构建目录；不要共用CMakeCache或手删不明目录。项目已拒绝在源码目录原地配置。[CMake命令说明](https://cmake.org/cmake/help/v3.22/manual/cmake.1.html)

## 7. 常见问题

| 提示 | 先核对 |
|---|---|
| CMakeLists.txt不存在 | -S是否指向rational-cmake目录 |
| 生成器与缓存不匹配 | 当前-B是否已被其他生成器使用；改用新的构建目录 |
| fatal error: rational.hpp | 是否用项目目标构建；包含目录由rational的PUBLIC要求提供 |
| undefined reference | 是否把work/rational.cpp链接成库；函数声明与定义签名是否一致 |
| multiple definition/main | 是否错误地同时加入work和reference，或把两个main放一起 |
| NOT_IMPLEMENTED | 正在运行未完成的work；继续实现，不是缺软件 |
| No tests were found | 是否在正确构建目录运行，BUILD_TESTING是否被关闭 |
| 测试看起来通过但没看到22项 | CTest通过时通常隐藏输出；加-V或直接运行rational_checks |

[CTest官方说明](https://cmake.org/cmake/help/v3.22/manual/ctest.1.html) · [C++阶段路线](../cpp/主教材/学习路线.md) · [Ubuntu VS Code说明](Ubuntu内VSCode使用.md)
