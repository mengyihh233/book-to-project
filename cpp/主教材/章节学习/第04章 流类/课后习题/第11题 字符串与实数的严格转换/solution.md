# 解析：字符串与实数的严格转换

不要只检查第一次>>是否成功。读入double后跳过尾部空白，再确认EOF，才能拒绝12abc和1 2。用isfinite排除NaN/Infinity。realToString用ostringstream，不把小数固定成两位。用stringToReal(realToString(x))检查往返；比较double值而不是原始文字，因为1.0与1e0可以表示同一值。

## 实操

先手算input.txt的输出，再检查空输入、空字符串、尾部空白、错误格式和EOF。将真实图像清单中的路径交给文件名函数，解释字符串处理与磁盘文件操作的差别。更多整合见[文件与数据清单实操](../../文件与数据清单实操.md)。
