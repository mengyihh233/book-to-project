# 机器视觉实践：零件轮廓计数与检测报告

这是结合Learning OpenCV的独立配套项目，不是原书同号习题答案。适合学过Mat、阈值分割、轮廓、矩、文件输入输出后练习。

## 任务与输出

输入背景均匀、零件彼此分离的图片。灰度化后阈值分割，用外轮廓找候选区域，按像素面积过滤，输出计数、包围框、质心、面积，以及mask.png、overlay.png、report.json。合成示例应检出3件，小噪点被过滤。

这是固定光照条件下的教学检测器，没有训练神经网络。接触或重叠零件可能被合并；孔洞不单独计数；像素面积不是物理面积；64MiB压缩文件与25M解码像素限制不能完全防止解码阶段的内存峰值。

## 运行

VS Code运行任务「机器视觉: 零件检测示例」；或在学习区终端：

```powershell
& 'C:/Users/lsy08/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe' tools/inspect-parts.py --demo
```

自己的图片：`tools/inspect-parts.py --input '图片路径' --output '仓库根目录/opencv/output/我的检测01' --config opencv/projects/parts-inspector/config.json`（使用上面的Python解释器）。输出目录必须未存在，不覆盖输入。支持中文与空格路径。

批量检测：把`--input`换成`--batch 图片目录`；只处理第一层PNG/JPG/JPEG/BMP普通文件，不跟随符号链接。单图失败继续其他图，batch-summary.json记录逐图结果，有失败返回2。编号前缀避免同名不同扩展名碰撞。输出不能放进批处理输入目录。

## 固定输入的失败场景

先做[八个失败场景实验](失败场景实验.md)：光照、阈值、粘连、孔洞和缩放配成一组对照；也可直接打开[网页实验](../../../workbench/vision-lab.html)，先预测再核对。

## 六道强化题

1. 为什么BGR到灰度不能直接当成RGB？写出三个Mat的类型与通道数。
2. 白背景黑零件为何选THRESH_BINARY_INV？改为浅色物体时如何配置？
3. 调整threshold为50、100、180，记录检测数和面积；解释为何不能把参数用在所有场景。
4. 提高min_area过滤噪点，推导图像缩放一半后面积阈值应如何变。
5. 把两件零件连接，预测计数变化；比较RETR_EXTERNAL和带层次的轮廓模式。
6. 独立实现报告导出，检查count与objects长度、坐标范围、质心及输出覆盖保护。

## 作答与验收

自己的程序写work/main.cpp；书面推导写work/notes.md。先实现最小链路，再加错误处理。参考解析见[solution.md](solution.md)，源码见[reference.cpp](reference.cpp)。

验收工具为tools/check-focus-projects.py：检查已知3件、空白图、中文路径、坏图、非法参数、既有输出保护与源图哈希，不会把参考通过写成你的学习完成状态。


## 与Linux和C++联合练习

生成report.json后进入[视觉报告核对实操](../../../linux/projects/dataset-audit/视觉报告核对.md)，输出CSV并比较总面积、均值和计数。内部自洽不等于检测正确，轮廓面积也不等于前景像素数量；保留原图与参数用于复盘。
