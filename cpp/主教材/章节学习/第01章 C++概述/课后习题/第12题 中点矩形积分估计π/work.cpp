// 【本题说明开始】
// 第1章习题12：中点矩形积分估计π
//
// 题目：不读取数据。将半径2的四分之一圆沿x轴分10000个等宽矩形，取每段中点高度求面积，输出π的近似值；绝对误差不超过10^-6。不要把结果再乘4。
// 实现什么：整段由你写，没有给好的函数。读入和错误处理已给出，中间的计算留空。
// 写在哪里：只补下方 BEGIN 1 到 END 1 之间。
// 文本格式：只输出答案本身，行末换行；不要打印输入提示。
// 怎么检查：运行任务「本题：检查作答」，比对本题登记的全部样例。
// 完整题目：README.md。
// 【本题说明结束】
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>
#include <algorithm>

// 输入与校验用的辅助函数：已给出，直接用。
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid number");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected data");}

// 主程序：读入和错误处理已写好，只补中间那段。
int main() {
    try {
        std::cout<<std::setprecision(10);
        end_input();
        /* BEGIN 1：校验、计算与输出 */
        // 提示：本题不读输入，把四分之一圆分成 10000 个等宽矩形，取每段中点的函数值累加再乘宽，直接得到 π 的近似。
        // 写完删掉下面的占位 throw。
        throw std::logic_error("补全区尚未完成");
        /* END 1 */
        return 0;
    } catch(const std::exception&e) {
        std::cerr<<e.what()<<"\n";
        return 2;
    }
}
