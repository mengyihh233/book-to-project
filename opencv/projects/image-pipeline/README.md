# 综合练习：处理自己的图片

本项目把OpenCV书中的文件、矩阵、颜色转换、滤波与边缘检测串成命令行工具。
main.cpp提供完整参考实现；你可以另建work.cpp，按下列规格独立实现。

## 功能

- 参数控制输入图片、输出PNG、Canny高低阈值和高斯核尺寸。
- 默认拒绝覆盖已有输出；显式传--overwrite才允许覆盖。
- 无论是否允许覆盖，都拒绝把结果写回输入文件。
- 检查参数、文件存在性、解码结果和写入状态，失败时返回2。
- 通过Windows宽字符命令行、C++文件流与imdecode/imencode支持中文及含空格路径。

## 使用

在VS Code运行任务“OpenCV项目：运行图片处理样例”，会处理合成测试图片，结果写到本目录output。
任务维护工具tools/check-projects.py（只检查参考项目）会测试缺失文件、坏图片、非法参数、中文路径与覆盖保护。
直接Ctrl+Shift+B运行main.cpp时没有参数，会得到用法错误；使用上述样例任务或下面的命令。

```powershell
$python = 'C:\Users\lsy08\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
& $python D:\Book-Learning\tools\run-project.py image --input 'D:\我的图片\练习.png' --output 'D:\Book-Learning\opencv\output\我的边缘.png' --low 50 --high 120 --blur 5
```

为便于教学，输入压缩文件限制64MiB，输出仅接受小写.png扩展名。该限制不等于解码内存上限，不要用来源不明的巨大图片进行实验。
输出保留边缘图，原图不变；参数和尺寸打印在终端，可重定向保存实验记录。

## 学习顺序与参考思路

先验证参数，再读取字节并解码，再处理像素，最后编码与保存。把“文件打不开”“不是图片”“参数非法”“覆盖冲突”当成不同失败路径。
中文路径问题应在路径到字节流这层处理，而不是修改图像矩阵。大多数简单的OpenCV算法只需要合法的Mat，不关心文件名。
本工具不访问摄像头，不提供实际检测准确率评估。
