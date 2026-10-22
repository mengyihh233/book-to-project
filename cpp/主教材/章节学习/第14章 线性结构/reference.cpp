// 阅读注释｜原书第14章，PDF429起；以下为中文概括与自编配套观察点。
// 概念：链式表示用链接描述顺序；修改一个链接前，要想清楚后续节点由谁拥有。
// 看代码：本例在表头插入，遍历顺序与输入相反；unique_ptr表达单一所有权，不演示环或共享节点。
// 先预测：依次插入1、2、3之后，为什么头节点是3？
// 本程序不是原书同号答案或全章覆盖证明；assert核对不要用-DNDEBUG关闭。
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

struct Node{int value;std::unique_ptr<Node>next;};
int main(){std::unique_ptr<Node>head;for(int x:{1,2,3})head=std::make_unique<Node>(Node{x,std::move(head)});int sum=0;for(auto*p=head.get();p;p=p->next.get())sum+=p->value;assert(sum==6&&head->value==3);std::cout<<sum<<"\n";}
