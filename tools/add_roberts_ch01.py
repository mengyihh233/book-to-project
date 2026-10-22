"""核对PDF48-49页后的第1章原书习题1—9，添加独立参考答案和样例。"""
from pathlib import Path
import json,csv
R=Path(__file__).resolve().parents[1]
header='''#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>
#include <algorithm>
long long integer(){long long x;if(!(std::cin>>x))throw std::runtime_error("invalid integer");return x;}
double real(){double x;if(!(std::cin>>x)||!std::isfinite(x))throw std::runtime_error("invalid number");return x;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("unexpected data");}
'''
def program(body):return header+'\nint main(){try{std::cout<<std::setprecision(10);'+body+'\nreturn 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\\n";return 2;}}\n'
items=[
 (1,'摄氏转华氏','读一个摄氏温度，输出对应华氏温度。',program('double c=real();end_input();double f=c*9.0/5+32;if(!std::isfinite(f))throw std::runtime_error("overflow");std::cout<<f<<"\\n";'),[('0','32',0),('100','212',0),('-40','-40',0),('abc','',2)],'用浮点常量9.0/5避免整数除法；零度、沸点与-40度可作为手工核验。'),
 (2,'米转英尺和英寸','读入非负米数，输出整英尺和剩余英寸，格式为feet inches。',program('double m=real();end_input();if(m<0||m>1e9)throw std::runtime_error("length range");double total=m/.0254;long long feet=static_cast<long long>(std::floor(total/12));double inches=total-feet*12;if(std::abs(inches)<1e-8)inches=0;if(std::abs(inches-12)<1e-8){++feet;inches=0;}std::cout<<feet<<" "<<inches<<"\\n";'),[('0','0 0',0),('.0254','0 1',0),('.3048','1 0',0),('1','3 3.37007874',0),('-1','',2)],'先除0.0254得到总英寸，再除12取整得到英尺，余量才是英寸。对接近0或12的浮点舍入作小范围规整。本实现教学长度上限1e9米，属额外输入约定。'),
 (3,'计算1到100之和','用循环计算1到100之和，不读入数据。',program('end_input();int sum=0;for(int i=1;i<=100;++i)sum+=i;std::cout<<sum<<"\\n";'),[('','5050',0)],'循环不漏掉100；再用100*101/2交叉验证，避免只把5050硬编码成答案。'),
 (4,'前N个奇数的和','读正整数N，计算前N个奇数之和。本实现限制N不超过1000000。',program('long long n=integer();end_input();if(n<1||n>1000000)throw std::runtime_error("N out of range");long long sum=0;for(long long i=0;i<n;++i)sum+=2*i+1;std::cout<<sum<<"\\n";'),[('1','1',0),('4','16',0),('1000000','1000000000000',0),('0','',2),('-1','',2)],'第i个（从0计）奇数是2*i+1；用long long累计。规律N平方可用于独立检验循环结果。'),
 (5,'信号量终止的最大值','读取整数直到0；0不计入数据。输出最大值。空序列、缺失终止符和非整数报错。',program('bool any=false;long long largest=0;for(;;){long long x=integer();if(x==0)break;if(!any||x>largest)largest=x;any=true;}end_input();if(!any)throw std::runtime_error("empty list");std::cout<<largest<<"\\n";'),[('17 42 11 0','42',0),('-8 -2 -9 0','-2',0),('0','',2),('1 2','',2),('1 x 0','',2)],'不能把最大值初始化为0后直接比较，否则全负数时错误。使用是否已读入首项的标记。将0声明为信号量常量是作答的可读性改进方向。'),
 (6,'最大值和次大值','读取整数直到0，输出最大值和次大值。本实现按两个观测位置排序，重复值可占两位；不足两个值报错。',program('bool first=false,second=false;long long a=0,b=0;for(;;){long long x=integer();if(x==0)break;if(!first){a=x;first=true;}else if(x>=a){b=a;a=x;second=true;}else if(!second||x>b){b=x;second=true;}}end_input();if(!second)throw std::runtime_error("need two observations");std::cout<<a<<" "<<b<<"\\n";'),[('251 317 636 766 607 0','766 636',0),('-3 -1 -2 0','-1 -2',0),('5 5 0','5 5',0),('5 0','',2)],'新值大于等于最大值时，原最大值先移到次大值。题干未明确重复值语义，本解采用多重集合次大；若要求第二大不同值，需改比较条件并补测试。'),
 (7,'成绩均值与-1信号量','读取数值直到-1，计算不含信号量的平均值。空数据报错。',program('long double sum=0;std::size_t count=0;for(;;){double x=real();if(x==-1)break;sum+=x;++count;}end_input();if(!count)throw std::runtime_error("empty list");std::cout<<sum/count<<"\\n";'),[('80 90 100 -1','90',0),('0 100 -1','50',0),('-1','',2),('20','',2)],'信号量是-1而非0，因为0可能是合法成绩。用浮点累计并只在count非零时相除。'),
 (8,'整数数字逆序','读非负64位整数，按while循环逆序其十进制数字。逆序后超出long long范围时报错。',program('long long n=integer();end_input();if(n<0)throw std::runtime_error("nonnegative required");long long reversed=0;do{int digit=static_cast<int>(n%10);if(reversed>(std::numeric_limits<long long>::max()-digit)/10)throw std::runtime_error("reverse overflow");reversed=reversed*10+digit;n/=10;}while(n);std::cout<<reversed<<"\\n";'),[('123456789','987654321',0),('1200','21',0),('0','0',0),('-2','',2),('8085774586302733229','',2)],'反复取余10得到末位、除10去掉末位。数字逆序不会保留前导零，1200得到21。乘10前先做溢出检查。'),
 (9,'质因数分解','读整数2到10^12，按从小到大输出质因数，保留重数，用空格分隔。',program('long long n=integer();end_input();if(n<2||n>1000000000000LL)throw std::runtime_error("factor range");bool first=true;for(long long p=2;p<=n/p;++p)while(n%p==0){if(!first)std::cout<<" ";std::cout<<p;first=false;n/=p;}if(n>1){if(!first)std::cout<<" ";std::cout<<n;}std::cout<<"\\n";'),[('60','2 2 3 5',0),('97','97',0),('2','2',0),('1','',2),('1000000000001','',2)],'每找到一个因子就不断除尽，再考察下一个。用p<=n/p避免p*p溢出；退出后若n>1，它就是最后的质因子。10^12上限为教学运行时限制，非题干规定。')]
path=R/'tools/book-tests.json';tests=json.loads(path.read_text(encoding='utf-8-sig'))
with (R/'guide/学习进度.csv').open(encoding='utf-8-sig',newline='') as f:rows=list(csv.DictReader(f))
for n,title,prompt,code,cases,answer in items:
 folder=R/f'cpp/主教材/章节学习/第01章 C++概述/课后习题/第{n:02}题';folder.mkdir(parents=True,exist_ok=True);pdfpage=48 if n<=2 else 49
 files={'reference.cpp':code,'work.cpp':'// 我的Roberts原书习题作答\n#include <iostream>\nint main(){return 0;}\n','input.txt':cases[0][0]+'\n',
 'README.md':f'# Roberts 第1章习题{n}：{title}\n\n[核对原书题干](../../../../books/cpp-roberts.pdf#page={pdfpage})（PDF页码，纸书第{pdfpage-15}页）。\n\n题意概述：{prompt}\n\n保留题意，输出格式为自动验收约定，提示语不参与标准输出。数值输入完整、有限；非法输入写stderr并返回2，成功返回0。先在work.cpp作答，参考代码仅供对照。\n\n运行tools/practice.py 当前work.cpp可检查已登记样例；每题cases为输入输出样例。\n',
 'solution.md':'# 参考解析\n\n'+answer+'\n\n先根据题干手算，再运行边界和错误样例。不要以能背出参考实现代替独立完成。\n'}
 for name,text in files.items():
  p=folder/name
  if not p.exists():p.write_text(text,encoding='utf-8')
 (folder/'cases').mkdir(exist_ok=True)
 for i,(inp,out,exitcode) in enumerate(cases,1):
  for ext,text in [('in',inp+'\n'),('out',out+'\n' if out else '')]:
   p=folder/'cases'/f'{i:02}.{ext}'
   if not p.exists():p.write_text(text,encoding='utf-8')
 ident=f'roberts-ch01-{n:02}'
 if not any(x['id']==ident for x in tests):tests.append(dict(id=ident,title=f'Roberts 第1章习题{n}：{title}',book='books/cpp-roberts.pdf',pdf_page=pdfpage,source=(folder/'reference.cpp').relative_to(R).as_posix(),cases=[[a+'\n',b] for a,b,c in cases],expected_exit_codes=[c for a,b,c in cases]))
 if not any(x['题号']==ident for x in rows):
  with (R/'guide/学习进度.csv').open('a',encoding='utf-8',newline='') as f:csv.DictWriter(f,fieldnames=list(rows[0])).writerow(dict(zip(rows[0],[ident,'原书习题','未开始','','',''])))
path.write_text(json.dumps(tests,ensure_ascii=False,indent=2),encoding='utf-8')
print('Roberts chapter1 exercises1-9 added; source pages visually checked.')
