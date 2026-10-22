// 阅读注释｜原书第8章，PDF252起；以下为中文概括与自编配套观察点。
// 概念：递归枚举需要保持部分解合法，再继续扩展；终止条件与选择条件各有责任。
// 看代码：本例只在左括号未用完时添加左括号，只在已开括号多于已闭括号时添加右括号。
// 先预测：为什么合法前缀不能先多放一个右括号？输入n为非负且需限制规模。
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

void gen(int n,int l,int r,std::string s,std::vector<std::string>&o){if(r==n){o.push_back(s);return;}if(l<n)gen(n,l+1,r,s+"(",o);if(r<l)gen(n,l,r+1,s+")",o);}
int main(){std::vector<std::string> o;gen(3,0,0,"",o);assert(o.size()==5);std::vector<std::string> z;gen(0,0,0,"",z);assert(z.size()==1);for(auto&s:o)std::cout<<s<<"\n";}
