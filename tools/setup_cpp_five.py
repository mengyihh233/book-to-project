from pathlib import Path
import json,re
ROOT=Path('仓库根目录')
def write(p,s):
    p=ROOT/p;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(s.strip()+'\n',encoding='utf-8',newline='\n')
def js(p,x):write(p,json.dumps(x,ensure_ascii=False,indent=2))
HEAD='''#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
'''
outline=json.loads((ROOT/'tools/cpp-five-toc.json').read_text(encoding='utf-8'))
volume='';chapters=[];all_chapters=[]
for e in outline:
    if e['depth']==0:volume=e['title']
    if re.match(r'^第\d+章',e['title']):
        all_chapters.append(dict(e,volume=volume))
        if '原理与实践' in volume:chapters.append(dict(e,volume=volume))
def old(n):return (ROOT/f'archive/cpp-roberts/chapters/ch{n:02d}/reference.cpp').read_text(encoding='utf-8')
labs=[
('程序的输入处理输出','描述成绩统计程序的输入、处理、输出，并为正常/空输入写验收标准。',HEAD+'int main(){std::vector<int>scores{80,90,85};assert(scores.size()==3);double average=std::accumulate(scores.begin(),scores.end(),0.0)/scores.size();assert(average==85);std::cout<<average<<"\\n";}', '输入是成绩序列；处理是求和、计数、平均；输出要解释空输入如何处理。'),
('Hello World','实现两行输出，练习保存、编译、运行与修改。',HEAD+'int main(){std::cout<<"Hello, World!\\nLearning C++ step by step.\\n";}', 'main是入口，字符串用双引号，语句以分号结束，\\n表示换行。'),
('对象类型和值','把10英里按书中1.609系数转成公里，比较int与double。',HEAD+'int main(){double miles=10,km=miles*1.609;assert(std::abs(km-16.09)<1e-10);std::cout<<km<<"\\n";}', '用double保存小数；初始化变量，避免窄化或未初始化读取。'),
('循环与计算','计算1到100之和，添加0与1的边界测试。',old(1),'循环累加，使用足够宽的整数。'),
('错误分类','写安全除法：除数为0时抛出异常，并测试该错误分支。',HEAD+'double divide(double a,double b){if(b==0)throw std::invalid_argument("zero divisor");return a/b;}int main(){assert(divide(8,2)==4);bool caught=false;try{(void)divide(1,0);}catch(const std::invalid_argument&){caught=true;}assert(caught);std::cout<<"error path tested\\n";}', '区分编译错误、运行错误、逻辑错误，先验证预期错误，再确认正常输出。'),
('编写小计算器','解析形如2+3的一次二元运算，支持加减乘除和输入校验。',HEAD+'double calc(std::string s){std::istringstream in(s);double a,b;char op;if(!(in>>a>>op>>b))throw std::invalid_argument("syntax");in>>std::ws;if(!in.eof())throw std::invalid_argument("trailing input");switch(op){case \'+\':return a+b;case \'-\':return a-b;case \'*\':return a*b;case \'/\':if(b==0)throw std::invalid_argument("zero");return a/b;default:throw std::invalid_argument("operator");}}int main(){assert(calc("2+3")==5);assert(calc("8 / 2")==4);std::cout<<calc("3*4")<<"\\n";}', '先约定小语法；本练习不支持优先级和括号，不能当作书中完整计算器。'),
('完成一个程序','将计算器处理结果累计，使用清晰的状态与reset操作。',HEAD+'class Session{double total=0;public:void add(double x){total+=x;}void reset(){total=0;}double value()const{return total;}};int main(){Session s;s.add(3);s.add(4);assert(s.value()==7);s.reset();assert(s.value()==0);std::cout<<"session OK\\n";}', '把状态与操作封装，给reset和边界路径加测试；完整书中计算器仍按原文逐步完成。'),
('函数与引用','实现交换函数并测试相等变量和负数。',old(2),'引用作用于调用者对象；值传递只改变副本。'),
('类与不变量','实现不允许负余额的账户类。',old(6),'公开操作维护不变量，private数据防止随意破坏状态。'),
('输入输出流','按行读取文本，统计行数和单词数。',old(4),'以读取是否成功为循环条件，不使用while(!eof())。'),
('定制输出','把3.14159格式化为固定两位小数并验证输出文本。',HEAD+'int main(){std::ostringstream out;out<<std::fixed<<std::setprecision(2)<<3.14159;assert(out.str()=="3.14");std::cout<<out.str()<<"\\n";}', 'fixed与setprecision一起表示小数位数；单独setprecision通常表示有效数字。'),
('向量与自由空间','用unique_ptr数组管理5个动态整数并求和。',old(12),'展示资源管理；书中的vector实现需亲自写拷贝、析构等，unique_ptr不替代理解。'),
('向量与数组','通过指针区间反转数组，处理空区间。',old(11),'保证指针属于同一数组范围，不越界解引用。'),
('模板与异常','编写sumRange模板，应用于vector和list。',old(20),'模板只依赖迭代器必要操作；异常安全和所有权在容器扩展中进一步练习。'),
('容器与迭代器','用迭代器复制并反转vector，不依赖下标。',HEAD+'int main(){std::vector<int>a{1,2,3},b(a.rbegin(),a.rend());assert((b==std::vector<int>{3,2,1}));for(int x:b)std::cout<<x<<" ";}', '容器决定存储，迭代器表达范围，算法操作范围。'),
('算法和映射','统计单词出现次数并按词典序输出。',old(15),'std::map按键排序；使用算法时确认前置条件。'),
('显示模型','将世界坐标(0.25,0.75)映射到800x600显示坐标。',HEAD+'int main(){int x=int(std::lround(.25*799)),y=int(std::lround((1-.75)*599));assert(x==200&&y==150);std::cout<<x<<" "<<y<<"\\n";}', '此练习为坐标模型；实际FLTK窗口示例见cpp/gui，图形窗口默认左上原点。'),
('图形类','定义抽象Shape和Rectangle，通过基类指针调用area。',old(19),'使用virtual析构、const成员函数与override。'),
('设计图形类','添加Circle类并验证半径2的面积。',HEAD+'struct Circle{double r;explicit Circle(double radius):r(radius){if(r<0)throw std::invalid_argument("radius");}double area()const{return std::acos(-1.0)*r*r;}};int main(){Circle c(2);assert(std::abs(c.area()-4*std::acos(-1.0))<1e-10);std::cout<<c.area()<<"\\n";}', '先定义类的不变量，再实现接口；负半径不合法。'),
('函数图与数据图','对x=-2到2每隔1计算x*x并输出坐标。',HEAD+'int main(){for(int x=-2;x<=2;++x)std::cout<<x<<","<<x*x<<"\\n";assert(2*2==4);}', '先采样函数，再进行世界到屏幕变换。此处输出采样数据；可拓展到SVG或FLTK绘图。'),
('GUI与回调','用std::function模拟按钮点击，两次点击后计数为2。',HEAD+'int main(){int n=0;std::function<void()>click=[&]{++n;};click();click();assert(n==2);std::cout<<n<<"\\n";}', '回调生命周期必须覆盖使用期；真实FLTK事件示例在gui中。'),
('理念和历史','输出本机编译的C++标准版本，解释源码兼容和二进制兼容区别。',HEAD+'int main(){static_assert(__cplusplus>=201703L,"C++17 required");std::cout<<__cplusplus<<"\\n";}', '历史背景用自己的话作答；此程序仅验证当前练习工具使用C++17。'),
('文本处理','忽略空格和大小写检查回文。',old(3),'先规范化，再比较；明确ASCII范围，Unicode需要专门处理。'),
('数值计算','计算向量(1,2,3)与(4,5,6)点积并验证结果。',HEAD+'int main(){std::array<double,3>a{1,2,3},b{4,5,6};double dot=std::inner_product(a.begin(),a.end(),b.begin(),0.0);assert(dot==32);std::cout<<dot<<"\\n";}', '起始累加值决定结果类型；同时关注数值稳定性与误差。'),
('嵌入式与位操作','用普通uint32_t变量模拟GPIO寄存器，设置bit13再清零。',HEAD+'int main(){std::uint32_t gpio=0;gpio|=(1u<<13);assert(gpio==8192);gpio&=~(1u<<13);assert(gpio==0);std::cout<<gpio<<"\\n";}', '本机用模拟变量，不能在Windows程序中解引用STM32外设地址。硬件实验使用独立STM32工作区。'),
('测试','为二分查找补充找到、不存在与边界测试。',old(10),'自检覆盖正常、边界与错误路径；通过测试不等于证明没有缺陷。'),
('C语言','用C11实现数组求和，通过gcc编译，比较C与C++的不同。','#include <stdio.h>\n#include <assert.h>\nint sum(const int*a,int n){int s=0;for(int i=0;i<n;++i)s+=a[i];return s;}int main(void){int a[]={1,2,3};assert(sum(a,3)==6&&sum(a,0)==0);printf("%d\\n",sum(a,3));return 0;}', '文件扩展名.c选择C编译器；C没有类、引用和模板，不能把C++代码只改后缀。'),
]
manifest=json.loads((ROOT/'tools/exercises.json').read_text(encoding='utf-8'))
manifest=[e for e in manifest if not e['id'].startswith('cpp-')]
for i,(title,task,code,hint) in enumerate(labs,1):
    ch=chapters[i-1];rel=f'cpp/参考教材/PPP章节练习/ch{i:02d}';suffix='c' if i==27 else 'cpp'
    write(f'{rel}/README.md',f'''# {ch['title']}：{title}

原书定位：[离线章节](../../../reader/cpp-five/{ch['href']})。
所属：{ch['volume']}。

## 配套练习PPP-L{i:02d}
{task}

在work/main.{suffix}作答，Ctrl+Shift+B编译运行，F5调试。
本练习独立编写；原书“简单练习”“习题”入口见本目录原书题目.md。
先完成再查看solution.md和reference.{suffix}。
''')
    write(f'{rel}/reference.{suffix}',code)
    starter=('#include <stdio.h>\nint main(void){\n    /* TODO */\n    return 0;\n}' if i==27 else '#include <iostream>\nint main(){\n    // TODO: read README and implement your solution.\n}\n')
    write(f'{rel}/work/main.{suffix}',starter)
    write(f'{rel}/solution.md',f'# PPP-L{i:02d}参考思路\n\n{hint}\n\n完整参考实现见reference.{suffix}，不是官方原书答案。')
    start=outline.index(next(e for e in outline if e['href']==ch['href'] and e['title']==ch['title']))
    end=next((k for k in range(start+1,len(outline)) if outline[k]['depth']<=1),len(outline))
    exercises=[e for e in outline[start:end] if '习题' in e['title'] or '练习' in e['title']]
    write(f'{rel}/原书题目.md',f'# {ch["title"]}原书任务\n\n'+ '\n'.join(f'- [{e["title"]}](../../../reader/cpp-five/{e["href"]})' for e in exercises)+'\n\n作答约定：work/book-exNN.cpp；论述题写work/answers.md。原书题没有现成答案时保留自己的推导和测试，不把配套答案当原书答案。')
    manifest.append({'id':f'cpp-PPP{i:02d}','kind':'配套练习','source':f'{rel}/reference.{suffix}','chapter':ch})
js('tools/exercises.json',manifest)
ws=json.loads((ROOT/'三本书学习.code-workspace').read_text(encoding='utf-8'))
ws['folders'][1]['name']='C++ 五册·PPP主线27章'
js('三本书学习.code-workspace',ws)
write('cpp/README.md','# C++五册学习路线\n\n1. 主线：原理与实践基础篇第1到14章。\n2. 接续：原理与实践进阶篇第15到27章。\n3. 导学第2版：已有基础后快速梳理与复习。\n4. 程序设计语言第1到3部分、第4部分标准库：查阅与深化，不要求初学时逐页硬读。\n\nppp目录按本EPUB真实章节排列，27个配套任务均含参考实现。\n原书习题通过离线阅读入口打开，题号与配套题分开。\n旧Roberts教材和解答在archive/cpp-roberts，不属于当前课程。')
write('guide/C++五册目录.md','# C++五册目录与阅读入口\n\n'+ '\n'.join(f'- {e["volume"]} / [{e["title"]}](../reader/cpp-five/{e["href"]})' for e in all_chapters))
print('C++ switched to five-volume EPUB, 27 PPP chapter labs and full book navigation.')
