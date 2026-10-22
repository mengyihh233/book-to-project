"""与C++实现独立的Python字符串模型；练习输入限定ASCII。"""
import re,itertools
def expected(n,parts):
 s=parts[0]
 if n==1:return str(s.endswith(parts[1])).lower()
 if n==2:return s.strip(' \t\r\n\v\f')
 if n==3:return s[int(parts[1]):] if parts[2]=='ALL' else s[int(parts[1]):int(parts[1])+int(parts[2])]
 if n==4:return s[:1].upper()+s[1:].lower()
 if n==5:
  groups={'AEILNORSTU':1,'DG':2,'BCMP':3,'FHVWY':4,'K':5,'JX':8,'QZ':10}
  table={c:v for group,v in groups.items() for c in group}
  return str(sum(table.get(c,0) for c in s.upper()))
 if n==6:return ''.join(w[0].upper() for w in re.findall('[A-Za-z]+',s))
 if n==9:return ''.join(c for c,_ in itertools.groupby(s))
 if n==10:
  mode,s,a,b=parts;return s.replace(a,b)
 if n==11:
  letters=re.sub('[^a-z]','',s.lower());return str(letters==letters[::-1]).lower()
 if n==12:
  if s.endswith(('s','x','z','ch','sh')):return s+'es'
  if len(s)>1 and s.endswith('y') and s[-2] not in 'aeiou':return s[:-1]+'ies'
  return s+'s'
 if n==13:
  value=int(s);return str(value)+('th' if 10<value%100<14 else {1:'st',2:'nd',3:'rd'}.get(value%10,'th'))
 if n==14:return re.sub(r'(?<=\d)(?=(?:\d{3})+$)',',',s)
 if n==15:
  def pig(match):
   word=match[0];v=re.search('[aeiou]',word,re.I)
   if v is None:return word
   lower=word.lower();i=v.start();out=lower+'way' if i==0 else lower[i:]+lower[:i]+'ay'
   return out[:1].upper()+out[1:] if word[0].isupper() else out
  return re.sub('[A-Za-z]+',pig,s)
 if n==16:return ''.join(('ob' if c in 'aeiou' and (i==0 or s[i-1] not in 'aeiou') and not(i==len(s)-1 and c=='e') else '')+c for i,c in enumerate(s))
 if n==17:return ''.join(chr(65+(ord(c.upper())-65+int(parts[1]))%26) if c.isalpha() else c for c in s)
 if n==18:return parts[1].upper().translate(str.maketrans('ABCDEFGHIJKLMNOPQRSTUVWXYZ',s.upper()))
 if n==19:return ''.join(chr(65+s.upper().index(c)) for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ')
 if n==20:return str(parts[1].upper().find(s.upper().translate(str.maketrans('ACGT','TGCA')),0 if parts[2]=='DEFAULT' else int(parts[2])))
 return s.translate(str.maketrans('','',parts[1]))
