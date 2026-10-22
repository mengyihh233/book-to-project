// 阅读注释｜原书第17章，PDF509起；以下为中文概括与自编配套观察点。
// 概念：集合强调成员与运算；同一数学集合可以有不同内部表示。
// 看代码：本例使用标准set及有序集合算法，输入顺序满足比较前提；不是原始Stanford Set实现。
// 先预测：集合并与交分别应保留哪些值？重复输入怎样处理？
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

int main(){std::set<int>a{1,2,3},b{3,4},u,i;std::set_union(a.begin(),a.end(),b.begin(),b.end(),std::inserter(u,u.end()));std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),std::inserter(i,i.end()));assert(u.size()==4&&i==std::set<int>{3});std::cout<<u.size()<<" "<<i.size()<<"\n";}
