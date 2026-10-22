// 阅读注释｜原书第5章，PDF148起；以下为中文概括与自编配套观察点。
// 概念：选择集合类型要先看需要的操作和顺序；栈的后进先出适合匹配尚未闭合的括号。
// 看代码：栈保存当前未匹配左括号；遇到右括号先判断空栈，再检查顶部类型。
// 先预测：([)]为什么字符数量相同却不合法？
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

bool balanced(const std::string&s){std::stack<char>st;const std::string left="([{",right=")]}";for(char c:s){if(left.find(c)!=std::string::npos)st.push(c);else{auto k=right.find(c);if(k!=std::string::npos){if(st.empty()||st.top()!=left[k])return false;st.pop();}}}return st.empty();}
int main(){assert(balanced("a{[()]}"));assert(!balanced("([)]"));assert(!balanced("("));assert(balanced(""));std::cout<<"balanced OK\n";}
