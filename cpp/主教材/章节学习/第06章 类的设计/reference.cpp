// 阅读注释｜原书第6章，PDF193起；以下为中文概括与自编配套观察点。
// 概念：类用接口隔离表示；构造和公开操作负责维护不变量，const查询不应修改对象。
// 看代码：银行账户用整数分表示小额金额；拒绝取款不改余额，负存款抛异常。示例未覆盖大额加法溢出。
// 先预测：失败操作前后的余额是否完全相同？有理数选做把规范表示和CMake接起来。
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

class BankAccount{long long cents=0;public:void deposit(long long n){if(n<0)throw std::invalid_argument("negative");cents+=n;}bool withdraw(long long n){if(n<0||n>cents)return false;cents-=n;return true;}long long balance()const{return cents;}};
int main(){BankAccount a;a.deposit(1000);assert(!a.withdraw(1001));assert(a.withdraw(250));assert(a.balance()==750);std::cout<<a.balance()<<"\n";}
