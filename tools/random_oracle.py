class MT:
    def __init__(self,seed):
        self.a=[seed]
        for i in range(1,624):self.a.append((1812433253*(self.a[-1]^(self.a[-1]>>30))+i)&0xffffffff)
        self.index=624
    def next(self):
        if self.index==624:
            for i in range(624):
                y=(self.a[i]&0x80000000)|(self.a[(i+1)%624]&0x7fffffff)
                self.a[i]=self.a[(i+397)%624]^(y>>1)^(0x9908b0df if y&1 else 0)
            self.index=0
        y=self.a[self.index];self.index+=1
        y^=y>>11;y^=(y<<7)&0x9d2c5680;y^=(y<<15)&0xefc60000;y^=y>>18
        return y&0xffffffff
def oracle(n,seed,count=1000):
    m=MT(seed)
    unit=lambda:(m.next()+0.5)/4294967296
    if n==12:return f'{sum(unit() for _ in range(count))/count:.10f}'
    if n==13:
        atoms=10000;out=['0 10000'];year=0
        while atoms:
            atoms=sum(m.next()>=2**31 for _ in range(atoms));year+=1;out.append(f'{year} {atoms}')
        return '\n'.join(out)
    if n==14:
        inside=0
        for _ in range(10000):
            x=2*unit()-1;y=2*unit()-1;inside+=x*x+y*y<1
        return f'{inside} {4*inside/10000:.4f}'
    streak=0;out=[]
    while streak<3:
        heads=m.next()<2**31;streak=streak+1 if heads else 0;out.append('HEADS' if heads else 'TAILS')
    return '\n'.join(out+[f'TOTAL {len(out)}'])
