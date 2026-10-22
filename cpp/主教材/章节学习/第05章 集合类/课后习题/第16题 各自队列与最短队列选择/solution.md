# 解析：各自队列与最短队列选择

使用vector<queue<QueueCustomer>>和每个收银员的剩余时长。findShortestQueue只比较等待队列size，严格小于才更新，从而并列保留最早编号；空队列向量必须报错。顾客入队后不因别处空闲而搬家。

每次接人时累加当前t减到达时刻，并增加started；倒计时由1降0时增加finished。每秒最后累计仍在队列里的等待人数。验证arrived=started+waiting、started=finished+busy；不要把原程序nServed直接当作已完成。

样例8秒、2人手算结果：

```text
arrived=4 started=4 finished=4 waiting=0 busy=0
total_wait=5 queue_area=5
mean_wait=1.250000 mean_queue=0.625000
```

参考使用长度不超过10000、最多32个收银员的教学限制，时间O(T*C)，辅助存储O(到达人数+C)。均值只针对指定样本和有限窗口，不能推出所有输入的等待结论。
