// 阅读注释｜原书第10章，PDF306起；以下为中文概括与自编配套观察点。
// 概念：算法分析关心输入规模增长时工作量怎样变化；二分查找依赖有序区间。
// 看代码：本例用[lo,hi)半开范围，失败返回-1；steps统计循环比较轮数，不是精确机器指令数。
// 先预测：为什么hi可等于size，而不能直接访问a[hi]？
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

int search(const std::vector<int>&a,int x,int&steps){int lo=0,hi=int(a.size());while(lo<hi){++steps;int m=lo+(hi-lo)/2;if(a[m]==x)return m;if(a[m]<x)lo=m+1;else hi=m;}return -1;}
int main(){std::vector<int>a(1024);std::iota(a.begin(),a.end(),0);int s=0;assert(search(a,700,s)==700);assert(s<=11);s=0;assert(search(a,-1,s)==-1);std::cout<<s<<"\n";}
