// 阅读注释｜原书第16章，PDF478起；以下为中文概括与自编配套观察点。
// 概念：搜索树的不变量连接局部比较与全局查找；遍历次序决定输出次序。
// 看代码：本例维护左小右大的二叉搜索树，中序得到有序结果；相同值被忽略，不是平衡树。
// 先预测：有序输入会把树变成什么形状？能否仍保证对数复杂度？
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

struct Tree{int x;std::unique_ptr<Tree>left,right;};void add(std::unique_ptr<Tree>&t,int x){if(!t){t=std::make_unique<Tree>(Tree{x,nullptr,nullptr});return;}if(x<t->x)add(t->left,x);else if(x>t->x)add(t->right,x);}void walk(const Tree*t,std::vector<int>&v){if(!t)return;walk(t->left.get(),v);v.push_back(t->x);walk(t->right.get(),v);}
int main(){std::unique_ptr<Tree>t;for(int x:{5,2,8,1,3,3})add(t,x);std::vector<int>v;walk(t.get(),v);assert((v==std::vector<int>{1,2,3,5,8}));for(int x:v)std::cout<<x<<" ";}
