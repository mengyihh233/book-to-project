// 阅读注释｜原书第2章，PDF52起；以下为中文概括与自编配套观察点。
// 概念：函数接口描述调用者可用的操作；引用参数允许函数修改调用者对象。
// 看代码：交换时临时变量保存尚未被覆盖的旧值；同一变量同时传给两个引用参数也要能解释。
// 先预测：swapValues(a,a)为什么不能靠直觉假定两个对象不同？
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

void swapValues(int&a,int&b){int t=a;a=b;b=t;}
int main(){int a=-3,b=8;swapValues(a,b);assert(a==8&&b==-3);swapValues(a,a);assert(a==8);std::cout<<a<<" "<<b<<"\n";}
