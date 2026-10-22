(function(root){
 'use strict';
 const finite=(x,min,max,integer=false)=>{if(!Number.isFinite(x)||x<min||x>max||(integer&&!Number.isInteger(x)))throw Error('参数超出允许范围，请检查输入。');return x};
 const series=(a,b,n,fn)=>Array.from({length:n+1},(_,i)=>{const x=a+(b-a)*i/n;return[x,fn(x)]});
 function compute(mode,p){
  if(mode==='ode'){
   const n=finite(+p.n,2,200,true),k=finite(+p.k,0,3),y0=finite(+p.y0,0,5),K=finite(+p.K,1,5),T=4,h=T/n;
   if(!['growth','decay','logistic'].includes(p.kind))throw Error('请选择方程。');
   const f=y=>p.kind==='growth'?k*y:p.kind==='decay'?-k*y:k*y*(1-y/K);
   const exact=t=>p.kind==='growth'?y0*Math.exp(k*t):p.kind==='decay'?y0*Math.exp(-k*t):y0===0?0:K/(1+(K/y0-1)*Math.exp(-k*t));
   const numerical=[[0,y0]];let y=y0,truncated=false;
   for(let i=1;i<=n;i++){y+=h*f(y);if(!Number.isFinite(y)||Math.abs(y)>10000){truncated=true;break}numerical.push([i*h,y])}
   const analytic=series(0,T,200,exact),ymax=Math.max(1,...analytic.map(x=>x[1]),y0)*1.2;
   const partial=truncated||numerical.some(x=>x[1]<0||x[1]>ymax);
   return{title:'微分方程：精确解与欧拉折线',formula:p.kind==='logistic'?"y′ = ky(1−y/K)":p.kind==='growth'?"y′ = ky":"y′ = −ky",explanation:'欧拉法用当前点斜率外推一步。步数增加通常改善这个光滑案例的近似；大步长可能造成振荡或发散。曲线重合不能证明误差为零。',domain:[0,T,0,ymax],field:Array.from({length:63},(_,i)=>{const t=(i%9+1)*T/10,v=Math.floor(i/9)*ymax/6;return[t,v,f(v)]}),curves:[{name:'精确解',points:analytic},{name:'欧拉法',points:numerical,dash:true}],columns:['t','欧拉值','精确值'],rows:numerical.filter((_,i)=>i%Math.max(1,Math.floor(n/8))===0||i===n).map(([t,v])=>[t,v,exact(t)]),metrics:[['步长',h],['t=4精确值',exact(T)],['t=4欧拉值',truncated?'未完成':y],['末端误差',truncated?'未完成':y-exact(T)]],partial:partial?'大步长使部分欧拉结果超出画面或合理范围；已保留可计算部分。增加步数再比较。':'',values:{exact:exact(T),euler:truncated?null:y,h}};
  }
  if(mode==='polar'){
   const a=finite(+p.a,0,3);if(!['circle','cardioid','rose3'].includes(p.kind))throw Error('请选择曲线。');
   const end=p.kind==='rose3'?Math.PI:2*Math.PI,r=t=>p.kind==='circle'?a:p.kind==='cardioid'?a*(1+Math.cos(t)):a*Math.sin(3*t),n=720;
   const points=Array.from({length:n+1},(_,i)=>{const t=end*i/n,v=r(t);return[v*Math.cos(t),v*Math.sin(t)]});
   let area=0;for(let i=0;i<n;i++)area+=r((i+.5)*end/n)**2*end/n/2;
   const exact=Math.PI*a*a*(p.kind==='circle'?1:p.kind==='cardioid'?1.5:.25),extent=Math.max(1,a*(p.kind==='cardioid'?2.2:1.2));
   return{title:'极坐标：同一个点，不止一种表示',formula:p.kind==='circle'?'r = a':p.kind==='cardioid'?'r = a(1+cosθ)':'r = a sin3θ',explanation:p.kind==='rose3'?'三瓣玫瑰线在0到π已描完一次。继续到2π会重复，不能把面积再加一遍。':'使用弧度制；x=r cosθ，y=r sinθ。负半径把位置翻到反方向。',domain:[-extent,extent,-extent,extent],curves:[{name:'极坐标曲线',points}],columns:['θ（弧度）','r','x','y'],rows:Array.from({length:9},(_,i)=>{const t=end*i/8,v=r(t);return[t,v,v*Math.cos(t),v*Math.sin(t)]}),metrics:[['描绘上限',end],['近似面积',area],['解析面积',exact]],partial:'',values:{area,exact,end}};
  }
  if(mode==='limits'){
   const exponent=finite(+p.exponent,-12,-1,true);if(!['hole','jump','squeeze'].includes(p.kind))throw Error('请选择函数。');
   const a=p.kind==='hole'?1:0,h=10**exponent,fn=x=>p.kind==='hole'?(x===1?7:x+1):p.kind==='jump'?(x<0?-1:1):x===0?0:x*Math.sin(1/x);
   const curves=p.kind==='squeeze'?[{name:'函数',points:series(-1,1,1000,fn)},{name:'上界 |x|',points:series(-1,1,100,Math.abs),dash:true},{name:'下界 −|x|',points:series(-1,1,100,x=>-Math.abs(x)),dash:true}]:[{name:'左侧',points:series(a-1,a-1e-5,200,fn)},{name:'右侧',points:series(a+1e-5,a+1,200,fn),dash:true}];
   return{title:'极限：看左右，区分点值',formula:p.kind==='hole'?'f(x)=x+1（x≠1），f(1)=7':p.kind==='jump'?'f(x)=−1（x<0），f(x)=1（x≥0）':'f(x)=x sin(1/x)（x≠0），f(0)=0',explanation:p.kind==='hole'?'点值7没有改变去心邻域中的极限2。空心点表示趋近位置，实心点表示函数值。':p.kind==='jump'?'左右分别趋于−1和1，所以双侧极限不存在。再密的单侧采样也不能补上另一侧。':'−|x|≤x sin(1/x)≤|x|，夹逼给出极限0。图像有限采样只作观察，不是证明。',domain:[a-1,a+1,p.kind==='hole'?0:-1.5,p.kind==='hole'?8:1.5],curves,markers:p.kind==='hole'?[[1,2,true],[1,7,false]]:[],columns:['h','f(a−h)','f(a+h)'],rows:Array.from({length:8},(_,i)=>{const d=10**(-i-1);return[d,fn(a-d),fn(a+d)]}),metrics:[['当前h',h],['左侧值',fn(a-h)],['右侧值',fn(a+h)],['双侧极限',p.kind==='hole'?'2':p.kind==='jump'?'不存在':'0']],partial:'',values:{left:fn(a-h),right:fn(a+h),limit:p.kind==='hole'?2:p.kind==='jump'?null:0}};
  }
  if(mode==='sequence'){
   const n=finite(+p.n,8,200,true);if(!['reciprocal','alternating','recursive','series'].includes(p.kind))throw Error('请选择序列。');
   const term=i=>p.kind==='reciprocal'?1/i:p.kind==='alternating'?(i%2?1:-1)*i/(i+1):p.kind==='recursive'?6-4/2**(i-1):3**(1-i);
   const points=Array.from({length:n},(_,i)=>[i+1,term(i+1)]),curves=[{name:p.kind==='series'?'通项':'序列点',points,dots:true}];
   if(p.kind==='series')curves.push({name:'部分和',points:Array.from({length:n},(_,i)=>[i+1,1.5*(1-3**(-i-1))]),dots:true});
   const rows=points.slice(0,8).map(([i,v])=>p.kind==='series'?[i,v,1.5*(1-3**(-i))]:[i,v]);
   return{title:'下册：序列与级数不能混淆',formula:p.kind==='reciprocal'?'aₙ=1/n':p.kind==='alternating'?'aₙ=(−1)ⁿ⁻¹ n/(n+1)':p.kind==='recursive'?'a₁=2，aₙ₊₁=(aₙ+6)/2':'aₙ=(1/3)ⁿ⁻¹，Sₙ=前n项之和',explanation:p.kind==='alternating'?'奇数子列趋1，偶数子列趋−1，所以全序列发散。连接离散点的折线不会成为原来的数列。':p.kind==='series'?'通项趋0；这个几何级数的部分和趋3/2。其他通项趋0的级数未必收敛。':'前几项只能帮助观察；还需要显式公式、单调有界或极限法则给出证明。',domain:[0,n+1,p.kind==='alternating'?-1.3:0,p.kind==='recursive'?6.5:1.8],curves,columns:p.kind==='series'?['n','aₙ','Sₙ']:['n','aₙ'],rows,metrics:[['项数',n],['末项',term(n)],['极限结论',p.kind==='alternating'?'不存在':p.kind==='recursive'?'6':p.kind==='series'?'通项0；部分和3/2':'0']],partial:'',values:{last:term(n),partialSum:p.kind==='series'?1.5*(1-3**(-n)):null}};
  }
  if(mode==='tails'){
   const pvalue=finite(+p.p,.5,5),N=finite(+p.n,2,2000,true),exponent=finite(+p.exponent,-8,-1,true),eps=10**exponent;
   if(!['p','log'].includes(p.kind))throw Error('请选择级数。');
   const start=p.kind==='p'?1:2,converges=pvalue>1;
   const f=n=>p.kind==='p'?n**(-pvalue):1/(n*Math.log(n)**pvalue);
   const tail=n=>(p.kind==='p'?n:Math.log(n))**(1-pvalue)/(pvalue-1);
   let sum=0,correction=0;const sums=[],lower=[],upper=[],data=[];
   for(let n=start;n<=N;n++){
    const adjusted=f(n)-correction,next=sum+adjusted;correction=(next-sum)-adjusted;sum=next;sums.push([n,sum]);
    if(converges){const l=tail(n+1),u=tail(n);lower.push([n,sum+l]);upper.push([n,sum+u]);data.push([n,sum,sum+l,sum+u])}
    else data.push([n,sum,'不适用','不适用']);
   }
   const curves=[{name:'部分和 Sₙ',points:sums,dots:sums.length===1}];if(converges)curves.push({name:'和的下界 Sₙ+Lₙ',points:lower,dash:true,dots:lower.length===1},{name:'和的上界 Sₙ+Uₙ',points:upper,dash:true,dots:upper.length===1});
   const maxY=Math.max(1,...sums.map(x=>x[1]),...upper.map(x=>x[1]));
   const rows=data.filter((_,i)=>i===0||i===data.length-1||i%Math.max(1,Math.floor(data.length/6))===0);
   const exact=p.kind==='p'&&pvalue===2?Math.PI**2/6:p.kind==='p'&&pvalue===4?Math.PI**4/90:null;
   const metrics=[['收敛判断',converges?'收敛（p>1）':'发散（p≤1）'],['Sₙ数值',sum],['本次计算项数',N-start+1],['仅用Sₙ的误差要求',eps]];
   let l=null,u=null,mid=null,midError=null,requiredLog10=null,requiredIndex=null,partial='';
   if(converges){
    l=tail(N+1);u=tail(N);mid=sum+(l+u)/2;midError=(u-l)/2;
    const lnScale=-Math.log((pvalue-1)*eps)/(pvalue-1);
    requiredLog10=p.kind==='p'?lnScale/Math.LN10:lnScale-Math.log(Math.LN10)>Math.log(Number.MAX_VALUE)?null:Math.exp(lnScale-Math.log(Math.LN10));
    if(requiredLog10!==null&&requiredLog10<Math.log10(Number.MAX_SAFE_INTEGER))requiredIndex=Math.max(2,Math.ceil(10**requiredLog10));
    const size=requiredIndex!==null?String(requiredIndex):requiredLog10===null?'指数也超出浮点范围；见解析公式':`约10^(${requiredLog10.toPrecision(7)})`;
    metrics.push(['尾项界 Lₙ ≤ Rₙ ≤ Uₙ',`${l.toPrecision(6)} ≤ Rₙ ≤ ${u.toPrecision(6)}`],['总和下界',sum+l],['总和上界',sum+u],['区间中点估计',mid],['中点理论误差界',midError],['只用Sₙ时的充分N估计（非最小）',size]);
    if(exact!==null)metrics.push(['已知精确和（核对用）',exact]);
    if(u-l<=64*Number.EPSILON*Math.max(1,Math.abs(sum)))partial='区间宽度接近浮点分辨率，数值端点不构成严格舍入认证。以解析界为准，不把重合小数当误差0。';
    else if(Number((sum+l).toPrecision(7))===Number((sum+u).toPrecision(7)))partial='当前显示精度把两个不同端点舍入成相同小数。解析界仍有宽度，不代表误差0。';
    if(requiredIndex===null)partial+=(partial?' ':'')+'所需下标过大，已用对数规模表示；不要真的循环累加到该项。';
   }
   return{title:'下册：部分和、总和与尾项界',formula:p.kind==='p'?'Σ n⁻ᵖ（从n=1开始）':'Σ 1/[n(ln n)ᵖ]（从n=2开始）',explanation:converges?'连续、正、递减时，积分从N+1到∞给尾项下界，从N到∞给上界。主图上下两线围的是总和，部分和线在其下方。理论界以精确Sₙ为前提；本页浮点显示没有严格舍入认证，不能当成证明。':'p≤1时这两类级数发散，不使用收敛级数的有限尾项界。部分和增长缓慢、通项趋0，均不能代替收敛证明。',domain:[0,N+1,0,maxY*1.12],curves,columns:['末项n','Sₙ','总和下界','总和上界'],rows,metrics,partial,values:{sum,lowerTail:l,upperTail:u,lowerSum:l===null?null:sum+l,upperSum:u===null?null:sum+u,mid,midError,exact,requiredLog10,requiredIndex,converges,start,N,eps}};
  }

  if(mode==='gradient'){
   const x=finite(+p.x,-2,2),y=finite(+p.y,-2,2),angle=finite(+p.angle,0,360),t=angle*Math.PI/180,gx=2*x,gy=4*y,d=gx*Math.cos(t)+gy*Math.sin(t),h=finite(p.h===undefined?.1:+p.h,-1,1),cx=Math.cos(t),sy=Math.sin(t),linear=h*d,remainder=h*h*(cx*cx+2*sy*sy),actual=(x+h*cx)**2+2*(y+h*sy)**2-(x*x+2*y*y),quotient=h===0?null:actual/h,curves=[];
   for(const level of [1,2,4,8])curves.push({name:'等高线 '+level,points:series(0,2*Math.PI,160,q=>q).map(([q])=>[Math.sqrt(level)*Math.cos(q),Math.sqrt(level/2)*Math.sin(q)]),dash:true});
   const norm=Math.hypot(gx,gy);curves.push({name:'梯度方向（归一化显示）',points:[[x,y],[x+(norm?gx/norm:0),y+(norm?gy/norm:0)]]},{name:'单位观察方向',points:[[x,y],[x+Math.cos(t),y+Math.sin(t)]],dash:true});
   return{title:'下册：梯度、位移与线性近似',formula:'f(x,y)=x²+2y²，∇f=(2x,4y)',explanation:'梯度指向局部增长最快的方向；方向导数是梯度与单位方向的点积。图上梯度只归一化显示方向，实际大小见数值。空心点是沿单位方向移动h后的点。df是一阶预测；本二次函数的精确余项为h²(uₓ²+2uᵧ²)，不能推广到任意曲面。图像行向下，需区分数学y方向。',domain:[-3.5,3.5,-3.5,3.5],curves,markers:[[x,y,false],[x+h*cx,y+h*sy,true]],columns:['x','y','∂f/∂x','∂f/∂y','方向导数'],rows:[[x,y,gx,gy,d]],metrics:[['梯度大小',norm],['方向导数',d],['f(x,y)',x*x+2*y*y],['有符号位移h',h],['一阶增量df = hDᵤf',linear],['实际增量Δf（浮点计算）',actual],['精确二次余项 h²(uₓ²+2uᵧ²)',remainder],['位移差商 Δf/h',quotient===null?'h=0，差商未定义':quotient]],partial:h!==0&&Math.abs(h)<1e-6?'h很小时直接作差受浮点相消影响；用解析余项理解误差，数值差商不代替证明。':'',values:{gx,gy,d,norm,h,linear,remainder,actual,quotient}};
  }
  throw Error('实验不存在，请重新选择。');
 }
 const api={compute};root.CalculusModels=api;if(typeof module==='object'&&module.exports)module.exports=api;
})(globalThis);
