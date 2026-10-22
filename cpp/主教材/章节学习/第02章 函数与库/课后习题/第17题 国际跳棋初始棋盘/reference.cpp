#include "canvas.h"
#include <algorithm>
void draw(Canvas& canvas) {
    const double size = .85*std::min(canvas.width,canvas.height);
    const double left = (canvas.width-size)/2, top = (canvas.height-size)/2, cell = size/8;
    canvas.rect(0,0,canvas.width,canvas.height,"#ffffff");
    for (int row=0;row<8;++row) for (int col=0;col<8;++col) {
        const bool dark = (row+col)%2==1;
        canvas.rect(left+col*cell,top+row*cell,cell,cell,dark ? "#6d4c41" : "#fff3e0");
        if (dark && (row<3 || row>=5))
            canvas.oval(left+(col+.5)*cell,top+(row+.5)*cell,.36*cell,.36*cell,row<3 ? "#c0392b" : "#30343b");
    }
}
int main() {
    try { int width,height; dimensions(width,height); Canvas canvas(width,height); draw(canvas); canvas.write(); }
    catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; }
}
