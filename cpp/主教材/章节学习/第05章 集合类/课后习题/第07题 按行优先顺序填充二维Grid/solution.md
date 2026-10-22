# 解析：按行优先顺序填充二维Grid

先明确维度和向量长度，再用双重循环row外、col内，对应values[row*cols+col]。不要把图像的x/y与rows/cols颠倒。IntGrid保留0×N形状，用at检查边界；它是本区受限教学类型，不是安装了Stanford Grid完整接口。复杂度O(rows*cols)。

先手算input.txt，补上正常、边界和错误输入，再在work独立实现。参考实现通过测试只是可运行证据，不是学习完成证明。
