# 解析：共用队列的多收银员仿真

用一个公共queue，收银员只保存自己的剩余服务时长。先把本秒顾客入队，按编号访问各收银员；忙的只减时长，原先闲的才从公共队首接人。多个收银员不能重复取同一顾客。

每次接人时累加当前t减到达时刻，并增加started；倒计时由1降0时增加finished。每秒最后累计仍在队列里的等待人数。验证arrived=started+waiting、started=finished+busy；不要把原程序nServed直接当作已完成。

样例8秒、2人手算结果：

```text
arrived=4 started=4 finished=4 waiting=0 busy=0
total_wait=2 queue_area=2
mean_wait=0.500000 mean_queue=0.250000
```

参考使用长度不超过10000、最多32个收银员的教学限制，时间O(T*C)，辅助存储O(到达人数+C)。均值只针对指定样本和有限窗口，不能推出所有输入的等待结论。
