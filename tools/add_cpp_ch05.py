"""已核对离线原书第5章习题2—7；仅添加缺失文件与索引，不覆盖作答。"""
from pathlib import Path
import json,csv
R=Path(__file__).resolve().parents[1]
common='''#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
double number(){double v;if(!(std::cin>>v)||!std::isfinite(v))throw std::runtime_error("invalid number");return v;}
void end_input(){std::cin>>std::ws;if(!std::cin.eof())throw std::runtime_error("extra input");}
'''
def main(body):return '\nint main(){try{std::cout<<std::setprecision(12);'+body+'\nreturn 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\\n";return 2;}}\n'
items=[
 (2,'修正摄氏到开尔文的程序',common+'double ctok(double c){return c+273.15;}\n'+main('double c=number();end_input();std::cout<<ctok(c)<<"\\n";'),
 [('0','273.15'),('100','373.15'),('-300','-26.85'),('abc',''),('1 2','')],[0,0,0,2,2],
 '先对照原书错误程序逐处找出声明、变量名、类型和调用错误。本题只修正程序与数值输入；绝对零度的物理约束在习题3添加。输入一个摄氏数，输出开尔文数。',
 'ctok返回double，参数c和返回表达式使用一致变量。读取cin而不是cout，结果变量和打印变量对应。273.15不能存进int而丢掉小数。-300在本题仍得到-26.85，正好引出下一题。'),
 (3,'在主程序检查绝对零度',common+'double ctok(double c){return c+273.15;}\n'+main('double c=number();end_input();if(c< -273.15)throw std::runtime_error("below absolute zero");std::cout<<ctok(c)<<"\\n";'),
 [('0','273.15'),('-273.15','0'),('-273.16',''),('bad','')],[0,0,2,2],
 '在习题2基础上，输入低于-273.15摄氏度时报告错误。本题把判断放在main中，下一题再移入函数。',
 '先判断c < -273.15，再转换；等于边界合法。不要用c<=-273.15，否则误拒绝绝对零度。测试正常、恰好边界、略低于边界和非数字。'),
 (4,'把温度约束移进函数',common+'double ctok(double c){if(!std::isfinite(c)||c< -273.15)throw std::runtime_error("below absolute zero");return c+273.15;}\n'+main('double c=number();end_input();std::cout<<ctok(c)<<"\\n";'),
 [('20','293.15'),('-273.15','0'),('-999',''),('','')],[0,0,2,2],
 '让ctok自身拒绝无效温度，调用方在main捕获异常。思考如果另一个函数调用ctok，为什么比只在main校验可靠。',
 '有效范围属于ctok的前置条件，放在函数入口可以保护所有调用者。main负责展示错误并返回非零状态，转换函数不承担终端提示。'),
 (5,'摄氏与开尔文双向转换',common+'double ctok(double c){if(c< -273.15)throw std::runtime_error("below absolute zero");return c+273.15;}\ndouble ktoc(double k){if(k<0)throw std::runtime_error("negative kelvin");return k-273.15;}\n'+main('double x=number();char unit;if(!(std::cin>>unit))throw std::runtime_error("missing unit");end_input();if(unit==\'C\')std::cout<<ctok(x)<<"\\n";else if(unit==\'K\')std::cout<<ktoc(x)<<"\\n";else throw std::runtime_error("use C or K");'),
 [('0 C','273.15'),('273.15 K','0'),('0 K','-273.15'),('-1 K',''),('10 X',''),('10','')],[0,0,0,2,2,2],
 '扩展习题4，实现双向转换。为便于自动测试，本实现约定输入数值后跟单位C或K；原书并未规定必须使用这个命令格式。',
 '先按单位分派，C调用ctok，K调用ktoc。不同单位的边界分别是-273.15和0。对未知单位和缺失单位单独报错。'),
 (6,'摄氏与华氏双向转换及估算',common+main('double x=number();char u;if(!(std::cin>>u))throw std::runtime_error("missing unit");end_input();double y;if(u==\'C\')y=x*9.0/5+32;else if(u==\'F\')y=(x-32)*5.0/9;else throw std::runtime_error("use C or F");if(!std::isfinite(y))throw std::runtime_error("result overflow");std::cout<<y<<"\\n";'),
 [('0 C','32'),('100 C','212'),('32 F','0'),('-40 F','-40'),('98.6 F','37'),('20 K','')],[0,0,0,0,0,2],
 '实现摄氏与华氏双向转换，并按原书要求用估算检验结果。本实现输入数值和C/F；本题不额外加入原书未要求的物理范围约束。',
 '使用9.0/5而非整除9/5；反向先减32再乘5.0/9。估算：0摄氏约32华氏、100摄氏约212华氏、体温约37摄氏。-40是两种温标交点。'),
 (7,'一元二次方程与异常',common+'''#include <algorithm>
void roots(long double a,long double b,long double c){
 if(a==0)throw std::runtime_error("not quadratic");
 long double scale=std::max({std::abs(a),std::abs(b),std::abs(c)});a/=scale;b/=scale;c/=scale;
 long double d=b*b-4*a*c;
 if(d<0)throw std::runtime_error("no real roots");
 long double x,y;
 if(d==0)x=y=-b/(2*a);
 else{long double q=-.5L*(b+std::copysign(std::sqrt(d),b));x=q/a;y=c/q;}
 if(!std::isfinite(x)||!std::isfinite(y))throw std::runtime_error("root overflow");
 if(x>y)std::swap(x,y);
 std::cout<<x<<" "<<y<<"\\n";
}
'''+main('double a=number(),b=number(),c=number();end_input();roots(a,b,c);'),
 [('1 -3 2','1 2'),('1 2 1','-1 -1'),('1 0 -4','-2 2'),('1 0 1',''),('0 2 1',''),('1 bad 3',''),('1 -100000000 1','1e-08 100000000')],[0,0,0,2,2,2,0],
 '实现求实根的函数，判别式为负时抛异常并在调用端处理。输入a b c，按从小到大输出两个根。a=0按非二次方程报告错误；不擅自改成线性求解。',
 '参考实现先缩放系数再算判别式，用q=-0.5*(b+copysign(sqrt(d),b))，再算q/a与c/q，减轻相近数相减造成的精度损失；重根单独处理。代回a*x*x+b*x+c时应看相对残差，不能只看根打印几位。浮点近重根依然有条件数问题，本实现按计算出的d符号判断，不随意把小负数改成零。')]
manifest=R/'tools/book-tests.json';tests=json.loads(manifest.read_text(encoding='utf-8-sig'))
with (R/'guide/学习进度.csv').open(encoding='utf-8-sig',newline='') as f:progress=list(csv.DictReader(f))
for n,title,src,cases,codes,prompt,answer in items:
 folder=R/f'cpp/参考教材/PPP课后习题/ppp-ch05/ex{n:02}';folder.mkdir(parents=True,exist_ok=True)
 content={'reference.cpp':src,'work.cpp':'// 我的原书第5章习题'+str(n)+'作答\n#include <iostream>\nint main(){return 0;}\n',
 'README.md':f'# 原书第5章习题{n}：{title}\n\n[原书习题](../../../../reader/cpp-five/OEBPS/text00438.html)\n\n{prompt}\n\n先在work.cpp独立作答，再读solution.md。只概述题意，完整题干与原始错误代码请看原书。\n\n约定：标准输出仅结果；错误写stderr并返回2；合法返回0。所有输入须完整，不接受多余参数或非有限数。\n\n运行VS Code「原书作答检查」任务会按已登记样例验收，不自动更新学习状态。测试输入见input.txt与cases目录。\n',
 'solution.md':f'# 参考解析\n\n{answer}\n\n本解法是参考，不是唯一答案。先手工推导至少两个正常值与一个失败案例，再用验收工具对照。\n','input.txt':cases[0][0]+'\n'}
 for name,text in content.items():
  p=folder/name
  if not p.exists():p.write_text(text,encoding='utf-8')
 (folder/'cases').mkdir(exist_ok=True)
 for i,(inp,out) in enumerate(cases,1):
  for suffix,text in [('in',inp+'\n'),('out',out+'\n' if out else '')]:
   p=folder/'cases'/f'{i:02}.{suffix}'
   if not p.exists():p.write_text(text,encoding='utf-8')
 ident=f'ppp-ch05-{n:02}'
 if not any(t['id']==ident for t in tests):tests.append({'id':ident,'source':(folder/'reference.cpp').relative_to(R).as_posix(),'cases':[[a+'\n',b] for a,b in cases],'expected_exit_codes':codes})
 if not any(t['题号']==ident for t in progress):
  with (R/'guide/学习进度.csv').open('a',encoding='utf-8',newline='') as f:csv.DictWriter(f,fieldnames=list(progress[0])).writerow(dict(zip(progress[0],[ident,'原书习题','未开始','','',''])))
manifest.write_text(json.dumps(tests,ensure_ascii=False,indent=2),encoding='utf-8')
print('Added chapter 5 exercises 2-7; existing work preserved.')
