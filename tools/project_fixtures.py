from PIL import Image,ImageDraw
from study import ROOT
def prepare():
    p=ROOT/'opencv/projects/image-pipeline/data/练习 图片.png'
    p.parent.mkdir(parents=True,exist_ok=True)
    if not p.exists():
        image=Image.new('RGB',(160,120),(15,15,15))
        draw=ImageDraw.Draw(image);draw.rectangle((20,20,70,95),fill=(30,210,80));draw.ellipse((90,30,140,80),fill=(30,100,230))
        image.save(p)
    return p
