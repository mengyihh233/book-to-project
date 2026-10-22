#include "canvas.h"
#include <algorithm>
void draw(Canvas& canvas) {
    const char* colors[] = {"#e53935","#fb8c00","#fdd835","#43a047","#1e88e5","#8e24aa","#87ceeb"};
    canvas.rect(0,0,canvas.width,canvas.height,"#87ceeb");
    for (int band=0;band<7;++band)
        canvas.oval(canvas.width*.5,canvas.height*1.35,
                    canvas.width*(.9-.035*band),canvas.height*(1.2-.055*band),colors[band]);
}
int main() {
    try { int width,height; dimensions(width,height); Canvas canvas(width,height); draw(canvas); canvas.write(); }
    catch(const std::exception& error) { std::cerr<<error.what()<<"\n"; return 2; }
}
