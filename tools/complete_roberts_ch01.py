"""补第1章习题10—12，题意核对PDF50—51页；其余文件不覆盖。"""
from add_roberts_ch01 import R,program
import json,csv,math
items=[(10,'冰雹序列',program('long long n=integer();end_input();if(n<1)throw std::runtime_error("positive required");std::vector<long long> values{n};while(n!=1){if(values.size()>1000000)throw std::runtime_error("step limit");if(n%2==0)n/=2;else{if(n>(std::numeric_limits<long long>::max()-1)/3)throw std::runtime_error("overflow");n=3*n+1;}values.push_back(n);}for(std::size_t i=0;i<values.size();++i){if(i)std::cout<<" ";std::cout<<values[i];}std::cout<<"\\n";'),[('6','6 3 10 5 16 8 4 2 1',0),('1','1',0),('0','',2),('9223372036854775807','',2)],None,
 '读正整数，偶数除2、奇数乘3加1，直到1。本实现按发生顺序输出所有数值，空格分隔，每一对相邻值记录一步变化。另设64位溢出与100万步限制，失败不输出半份正常结果。','逐步根据奇偶性更新；用vector暂存以避免失败时留下半份成功输出。题中最终终止性不是已证明定理，不能声称对所有正整数一定终止，因此保留步数上限。'),
 (11,'莱布尼茨级数估计π',program('end_input();long double sum=0;for(int i=0;i<10000;++i)sum+=(i%2?-1.L:1.L)/(2*i+1);std::cout<<4*sum<<"\\n";'),[('',str(math.pi),0)],.000101,
 '按原书要求累加10000项交错级数，乘4得到π近似值，不读数据。验收相对真实π的绝对误差不超过0.000101。','交错级数余项绝对值不超过第一项被舍弃项，所以π误差不超过4/20001，严格更紧的本例实际误差约0.0001；本验收界0.000101基于本例10000项的实际可验证精度，不是通用余项上界。参考值约3.141492654，别把它当精确π。'),
 (12,'中点矩形积分估计π',program('end_input();const int rectangles=10000;const long double radius=2,width=radius/rectangles;long double sum=0;for(int i=0;i<rectangles;++i){long double x=(i+.5L)*width;sum+=width*std::sqrt(radius*radius-x*x);}std::cout<<sum<<"\\n";'),[('',str(math.pi),0)],.000001,
 '半径2的四分之一圆，分10000个等宽矩形，以中点高度累计面积。不读数据；面积正好近似π，验收绝对误差1e-6。','矩形宽度2/10000，中点横坐标(i+0.5)*width，高度sqrt(4-x*x)。半径2的四分之一圆面积为π，不要再乘4；把端点法误写为中点法会改变收敛误差。')]
manifest=R/'tools/book-tests.json';tests=json.loads(manifest.read_text(encoding='utf-8'))
with (R/'guide/学习进度.csv').open(encoding='utf-8-sig',newline='') as f:rows=list(csv.DictReader(f))
for n,title,code,cases,tolerance,prompt,solution in items:
 folder=R/f'cpp/主教材/章节学习/第01章 C++概述/课后习题/第{n:02}题';folder.mkdir(parents=True,exist_ok=True)
 for name,text in {'reference.cpp':code,'work.cpp':'// 我的Roberts第1章作答\nint main(){return 0;}\n','input.txt':cases[0][0]+'\n','README.md':f'# Roberts 第1章习题{n}：{title}\n\n[原书题干](../../../../books/cpp-roberts.pdf#page=50)，习题12接PDF51页。\n\n{prompt}\n\n先在work.cpp作答；输出格式为验收约定，非法输入返回2并写stderr。近似计算的cases/out保存π目标值，比较时使用题目指定容差而非字符串相等。\n','solution.md':'# 参考解析\n\n'+solution+'\n'}.items():
  p=folder/name
  if not p.exists():p.write_text(text,encoding='utf-8')
 (folder/'cases').mkdir(exist_ok=True)
 for i,(inp,out,code_) in enumerate(cases,1):
  for ext,text in [('in',inp+'\n'),('out',out+'\n' if out else '')]:
   p=folder/'cases'/f'{i:02}.{ext}'
   if not p.exists():p.write_text(text,encoding='utf-8')
 ident=f'roberts-ch01-{n:02}'
 if not any(t['id']==ident for t in tests):
  t=dict(id=ident,title=f'Roberts 第1章习题{n}：{title}',book='books/cpp-roberts.pdf',pdf_page=50,source=(folder/'reference.cpp').relative_to(R).as_posix(),cases=[[a+'\n',b] for a,b,c in cases],expected_exit_codes=[c for a,b,c in cases])
  if tolerance:t.update(rel_tol=0,abs_tol=tolerance)
  tests.append(t)
 if not any(t['题号']==ident for t in rows):
  with (R/'guide/学习进度.csv').open('a',encoding='utf-8',newline='') as f:csv.DictWriter(f,fieldnames=list(rows[0])).writerow(dict(zip(rows[0],[ident,'原书习题','未开始','','',''])))
manifest.write_text(json.dumps(tests,ensure_ascii=False,indent=2),encoding='utf-8')
