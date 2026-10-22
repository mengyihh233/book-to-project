from build_workspace import ROOT, write, jwrite, HEAD
import json

# Individually authored solutions for the 12 programming exercises observed
# on C++ PDF pages 48-51 (printed pages 33-36).
answers=[
('摄氏转华氏', 'double c;if(!(std::cin>>c))return 1;std::cout<<std::setprecision(12)<<c*9.0/5.0+32<<"\\n";', [('0\n','32'),('100\n','212'),('-40\n','-40')], '使用9.0/5.0避免整数除法。输出华氏温度。'),
('米转英尺与英寸', 'double m;if(!(std::cin>>m)||m<0)return 1;double total=m/.0254;long long feet=static_cast<long long>(std::floor(total/12));double inches=total-feet*12;if(inches>12-1e-9){++feet;inches=0;}std::cout<<feet<<" "<<std::setprecision(12)<<inches<<"\\n";', [('0.3048\n','1 0'),('0.0254\n','0 1')], '先换算总英寸，再分离整英尺与剩余英寸。题目未要求英寸必须取整数，所以保留小数。拒绝负长度。'),
('1到100求和', 'int sum=0;for(int i=1;i<=100;++i)sum+=i;std::cout<<sum<<"\\n";', [('', '5050')], '循环累加；也可利用配对得到100*101/2。'),
('前N个奇数求和', 'long long n;if(!(std::cin>>n)||n<1||n>1000000)return 1;long long sum=0;for(long long i=0;i<n;++i)sum+=2*i+1;std::cout<<sum<<"\\n";', [('4\n','16'),('1\n','1')], '循环第i步加入2*i+1。结果等于N平方，可作为交叉校验。这里限制N<=1000000避免过长运行。'),
('哨兵输入的最大值', 'constexpr long long SENTINEL=0;long long x,best=0;bool any=false;while(std::cin>>x&&x!=SENTINEL){if(!any||x>best)best=x;any=true;}if(!any)std::cout<<"no data\\n";else std::cout<<best<<"\\n";', [('-5 -2 -9 0\n','-2'),('0\n','no data')], '第一次有效输入初始化最大值，不能用0作为初始最大值；否则全负数会出错。立即输入哨兵时明确报告无数据。'),
('最大与次大', 'long long x,first=0,second=0;int count=0;while(std::cin>>x&&x!=0){if(count==0){first=x;}else if(count==1){second=x;if(second>first)std::swap(first,second);}else if(x>=first){second=first;first=x;}else if(x>second)second=x;++count;}if(count<2)std::cout<<"need two values\\n";else std::cout<<first<<" "<<second<<"\\n";', [('223 251 317 636 766 607 0\n','766 636'),('-2 -5 -9 0\n','-2 -5'),('5 5 0\n','5 5')], '这里按输入位置排序，因此两个相同最大值可占前两位；若要求第二大不同值，应另行去重。至少需要两个有效输入。'),
('平均值与-1哨兵', 'double x,sum=0;long long n=0;while(std::cin>>x&&x!=-1){sum+=x;++n;}if(n==0)std::cout<<"no data\\n";else std::cout<<std::setprecision(12)<<sum/n<<"\\n";', [('80 90 100 -1\n','90'),('-1\n','no data')], '哨兵不计入总和与人数。没有数据时不能除以0。-1作为哨兵意味着它不能同时代表有效数据。'),
('逆序输出数字', 'std::string s;if(!(std::cin>>s)||s.empty())return 1;for(unsigned char c:s)if(!std::isdigit(c))return 1;std::reverse(s.begin(),s.end());std::cout<<s<<"\\n";', [('123456789\n','987654321'),('1200\n','0021'),('0\n','0')], '题目要求逆序输出每一位，这里保留反转后前导0。字符串法避免数值反转溢出。若改用取余法，也应说明1200输出0021还是21。'),
('质因数分解', 'long long n;if(!(std::cin>>n)||n<2)return 1;bool first=true;for(long long p=2;p<=n/p;++p){while(n%p==0){if(!first)std::cout<<" x ";std::cout<<p;first=false;n/=p;}}if(n>1){if(!first)std::cout<<" x ";std::cout<<n;}std::cout<<"\\n";', [('60\n','2 x 2 x 3 x 5'),('97\n','97')], '反复除以当前因子，直到不再整除；剩余大于1的部分也是质因子。p<=n/p避免p*p溢出。'),
('冰雹序列', 'unsigned long long n;if(!(std::cin>>n)||n<1)return 1;std::cout<<n;int steps=0;while(n!=1&&steps<10000){if(n%2==0)n/=2;else{if(n>(std::numeric_limits<unsigned long long>::max()-1)/3){std::cerr<<"overflow\\n";return 2;}n=3*n+1;}std::cout<<" "<<n;++steps;}std::cout<<"\\n";if(n!=1){std::cerr<<"step limit\\n";return 3;}', [('1\n','1'),('3\n','3 10 5 16 8 4 2 1')], '偶数除2，奇数乘3加1。使用溢出检查与步数上限；有限测试不代表证明所有正整数最终到1。'),
('Leibniz级数估计π', 'double sum=0;for(int k=0;k<10000;++k)sum+=(k%2==0?1.0:-1.0)/(2*k+1);std::cout<<std::setprecision(12)<<4*sum<<"\\n";', [('', '3.14149265359')], '先求π/4再乘4。10000项收敛很慢，误差约1e-4，不应宣称高精度。'),
('矩形积分估计π', 'constexpr int N=10000;constexpr double R=2;double dx=R/N,area=0;for(int i=0;i<N;++i){double x=(i+.5)*dx;area+=std::sqrt(R*R-x*x)*dx;}std::cout<<std::setprecision(12)<<area<<"\\n";', [('', '3.14159299803')], '按题意半径2，四分之一圆面积恰为π。使用每个小矩形中点计算高度，用10000个矩形求和。不要再乘4。'),
]
manifest=json.loads((ROOT/'tools/exercises.json').read_text(encoding='utf-8'))
booktests=[]
for i,(title,body,tests,hint) in enumerate(answers,1):
    rel=f'cpp/参考教材/PPP课后习题/ch01/ex{i:02d}'
    write(f'{rel}/reference.cpp',HEAD+'\nint main(){'+body+'}\n')
    write(f'{rel}/work.cpp','#include <iostream>\n// Book chapter 1 exercise '+str(i)+'\nint main(){\n    // TODO: read the original question, then solve it.\n}\n')
    write(f'{rel}/README.md',f'# 原书第1章习题{i}：{title}\n\n原书题干：books/cpp.pdf，PDF第48到51页（书内第33到36页）。\n此处为题意索引，完整条件以原书为准。先写work.cpp，再看solution.md。\n')
    write(f'{rel}/solution.md',f'# 第1章习题{i} 参考解答\n\n{hint}\n\n实现见reference.cpp。此为独立编写的参考解答，非官方答案。\n\n## 验证样例\n'+ '\n'.join(f'- 输入 `{s.strip() or "无"}` → 输出 `{out}`。' for s,out in tests))
    booktests.append({'id':f'cpp-book-ch01-{i:02d}','source':f'{rel}/reference.cpp','cases':tests})
jwrite('tools/book-tests.json',booktests)
write('cpp/参考教材/PPP课后习题/ch01/README.md','# 原书第1章：12道编程习题\n\n已逐页查看PDF第48到51页并编写解答。每题都有work.cpp、参考代码、思路与样例。\n复习题与编程习题分开；本目录仅覆盖12道编程习题，不包含复习题答案。\n\n'+ '\n'.join(f'- [习题{i}：{a[0]}](ex{i:02d}/README.md)' for i,a in enumerate(answers,1)))
print('Created 12 book exercise solutions with test cases.')
