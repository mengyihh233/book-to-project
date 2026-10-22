# OpenCV中文入门与学习安排

## 和现有学习线怎么搭配

C++提供语言与数据结构基础；OpenCV处理已有图像、视频和观测数据；OpenGL用来绘制图像与三维场景。两者可以组合，但数据格式、坐标原点和颜色顺序需要显式转换。
先熟悉C++的函数、类、vector、引用与基本文件读写，再系统学OpenCV。现在可以先运行入门程序观察结果，每周增加一次30到60分钟视觉实验，不必重新打乱原有主线。

## 第一课：让图像经过完整流程

打开opencv/quickstart/main.cpp，按Ctrl+Shift+B编译运行。输入图像由程序生成，所以可以重复实验并准确比较。

处理顺序：

1. Mat保存300行、400列、3通道的8位图像。
2. rectangle、circle生成已知形状。
3. cvtColor把BGR转换为灰度。
4. GaussianBlur降低高频变化。
5. Canny根据梯度与阈值提取边缘。
6. hconcat把原图与结果拼接，imwrite保存PNG。

结果位于[opencv/output/first-edges.png](../opencv/output/first-edges.png)。固定示例的边缘像素数为1100；修改阈值或形状后，结果可能改变，这正是实验需要记录的内容。

先做三个变化：把矩形缩小；把高斯核从5x5改成3x3；提高Canny阈值。每次只改变一个条件，记录前后差异。

## 关键概念

| 英文/API | 中文解释 | 容易犯的错误 |
|---|---|---|
| Mat | 保存矩阵/图像的对象，包含形状、类型和数据管理信息 | 赋值通常是共享数据，不是完整复制 |
| rows / cols | 行数/列数，对应高度/宽度 | 将x,y误写成行、列 |
| depth / channels | 每个通道的数值类型/每个像素的通道数 | 把CV_8UC3当成三个像素 |
| BGR / RGB | 不同的颜色分量顺序 | OpenCV图像默认常为BGR，直接给OpenGL可能红蓝颠倒 |
| ROI | 感兴趣区域，是原图的一块视图 | 修改ROI可能同时修改原图；ROI不保证连续存储 |
| clone | 复制像素数据 | 想保留原图却只做Mat赋值 |
| kernel | 卷积核/结构元素，具体含义取决于函数 | 所有kernel都理解成同一种运算 |
| threshold | 阈值 | 不看灰度范围就照抄参数 |
| contour | 轮廓点集 | 轮廓面积与白色像素数混为一谈 |
| keypoint / descriptor | 关键点位置/局部外观编码 | 二进制描述子用了不合适的匹配距离 |
| intrinsic / extrinsic | 相机内参/外参 | 像素坐标和归一化相机坐标混用 |
| train / test | 训练/测试 | 用测试集拟合或调参数，导致评估泄漏 |

Mat通常使用行(y)、列(x)访问；Point常使用(x,y)。每次写坐标前先说明采用哪一种约定。

## OpenCV3教材与本机4.13环境

本机同时存在opencv4与opencv5头文件目录。学习编译任务显式指定opencv4，当前导入库链接到-413.dll，并已通过版本与实际算法运行检查。没有改动现有OpenCV5文件，也没有再安装另一套OpenCV。

背景减除、光流和HOG通过DNN模块间接依赖Protobuf。原环境的libprotobuf.dll缺少OpenCV所需的三个导出符号，导致程序在启动时以0xc0000139退出。已从MSYS2官方仓库下载并校验Protobuf36.2软件包，将其中的DLL隔离放在vendor/opencv-deps/ucrt64/bin。只为本学习区OpenCV程序及对应调试任务优先使用此目录，没有替换全局DLL。原始软件包保留在MSYS2包缓存中。

| 书中可能遇到的形式 | 本学习区使用方式 |
|---|---|
| CV_LOAD_IMAGE_COLOR等旧常量 | cv::IMREAD_COLOR |
| CV_BGR2GRAY等旧颜色常量 | cv::COLOR_BGR2GRAY |
| IplImage、cvLoadImage等旧C接口 | cv::Mat、cv::imread等C++接口；部分旧C接口已移除 |
| CvSVM等旧机器学习类 | cv::ml::SVM::create()及train/predict |
| 已变动的特征模块或构造方式 | 每个例子按4.13实际可编译API改写，不能假设所有旧代码原样可用 |
| 当时的未来预测 | 作为历史材料阅读，现状另查当前官方资料 |

不要用5.x头文件搭配4.x导入库，也不要把MSVC的.lib与本机MinGW编译链混用。重新升级OpenCV后先运行环境验证，再继续练习。

## 分阶段安排

| 阶段 | 章节 | 小项目 |
|---|---|---|
| 入门 | 1—6 | 合成图片、像素访问、颜色转换、标注 |
| 图像处理 | 8、10—14 | 图像文件与参数、滤波、变换、边缘、模板与轮廓 |
| 时间序列 | 15—17 | 合成运动、背景减除与稀疏光流 |
| 几何 | 18—19 | 已知内参投影、理想双目三角化，再准备真实标定 |
| 学习与检测 | 20—22 | 训练/测试分离、SVM、HOG与检测器检查 |
| 补充 | 7、9、23 | 函数对象、回调逻辑、版本与复现记录 |

每章先写work/main.cpp，再对照solution.md和reference.cpp。原书题另建book-exNN.cpp，不使用CV-L编号冒充原书题号。

## 常见问题

- 找不到opencv2头文件：使用OpenCV目录里的编译任务，或检查include是否指向D:/c++/MYSYS2/ucrt64/include/opencv4。
- 链接错误：使用同一UCRT64编译器和OpenCV4导入库；不要手工套用网上MSVC配置。
- 程序提示DLL缺失：从工作区任务运行，任务会给子进程设置现有UCRT64运行库路径。
- 图片为空：先检查路径和empty，再调用cvtColor等函数。
- 中文路径保存失败：本机该OpenCV文件接口对UTF-8中文路径的处理未通过，因此输出文件使用英文路径。确需中文文件名时可采用imencode配合支持Unicode的文件写入方式。
- [新增图片处理综合项目](../opencv/projects/image-pipeline/README.md)已经实现上述文件流方案，可读取中文输入路径并保存中文输出路径；旧quickstart仍使用简单的英文输出文件名。
- 窗口一闪而过：先使用不依赖窗口的图像输出实验；主动使用imshow时理解waitKey与窗口事件处理。
- 结果与书中照片不同：先核对输入、图像类型、参数与版本，再判断算法差异。

## 验证与资料

[本机23章验证记录](OpenCV验证记录.json)记录每个参考程序的执行结果，不代表原书全部习题已解答，也不代表真实数据上的精度评估完成。

- [OpenCV4官方图像操作教程](https://docs.opencv.org/4.10.0/d5/d98/tutorial_mat_operations.html)
- [OpenCV官方迁移指南](https://docs.opencv.org/4.5.5/db/dfa/tutorial_transition_guide.html)
- [OpenCV4.0发布与接口调整说明](https://opencv.org/opencv-4-0-/)
