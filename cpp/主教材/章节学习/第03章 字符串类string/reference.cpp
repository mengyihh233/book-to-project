// 阅读注释｜原书第3章，PDF100起；以下为中文概括与自编配套观察点。
// 概念：string是抽象数据类型；遍历、字符分类和比较应区分对象本身与筛选后的文本。
// 看代码：本例先过滤并转小写，再比较两端；cctype输入使用unsigned char，避免负char值造成未定义行为。
// 先预测：空串、标点、普通英文分别会留下什么？本例不处理Unicode语义。
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

bool pal(const std::string&s){std::string t;for(unsigned char c:s)if(std::isalnum(c))t+=char(std::tolower(c));return std::equal(t.begin(),t.begin()+t.size()/2,t.rbegin());}
int main(){assert(pal("Never odd or even"));assert(pal(""));assert(!pal("hello"));std::cout<<"palindrome OK\n";}
