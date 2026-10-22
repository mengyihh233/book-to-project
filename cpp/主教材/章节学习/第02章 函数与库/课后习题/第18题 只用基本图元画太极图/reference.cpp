#include "canvas.h"
#include <algorithm>
void draw(Canvas& canvas) {
    const double cx=canvas.width*.5, cy=canvas.height*.5;
    const double radius=.38*std::min(canvas.width,canvas.height);
    canvas.rect(0,0,canvas.width,canvas.height,"#ffffff");
    canvas.oval(cx,cy,radius,radius,"#000000");
    canvas.rect(cx-radius,cy-radius,radius,2*radius,"#ffffff");
    canvas.oval(cx,cy-radius/2,radius/2,radius/2,"#ffffff");
    canvas.oval(cx,cy+radius/2,radius/2,radius/2,"#000000");
    canvas.oval(cx,cy-radius/2,radius/8,radius/8,"#000000");
    canvas.oval(cx,cy+radius/2,radius/8,radius/8,"#ffffff");
    canvas.outline(cx,cy,radius);
}
int main() {
    try { int width,height; dimensions(width,height); Canvas canvas(width,height); draw(canvas); canvas.write(); }
    catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; }
}
