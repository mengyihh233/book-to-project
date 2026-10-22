#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <string>
// 独立教学适配器：只提供矩形、椭圆和轮廓，输出SVG，不依赖Stanford库。
class Canvas {
    std::ostringstream shapes;
public:
    const int width, height;
    Canvas(int w, int h): width(w), height(h) { shapes << std::fixed << std::setprecision(6); }
    void rect(double x,double y,double w,double h,const std::string& color) {
        shapes << "<rect x=\""<<x<<"\" y=\""<<y<<"\" width=\""<<w<<"\" height=\""<<h<<"\" fill=\""<<color<<"\"/>\n";
    }
    void oval(double cx,double cy,double rx,double ry,const std::string& color) {
        shapes << "<ellipse cx=\""<<cx<<"\" cy=\""<<cy<<"\" rx=\""<<rx<<"\" ry=\""<<ry<<"\" fill=\""<<color<<"\"/>\n";
    }
    void outline(double cx,double cy,double radius) {
        shapes << "<ellipse cx=\""<<cx<<"\" cy=\""<<cy<<"\" rx=\""<<radius<<"\" ry=\""<<radius<<"\" fill=\"none\" stroke=\"#000000\" stroke-width=\"1\"/>\n";
    }
    void write() const {
        std::cout << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""<<width<<"\" height=\""<<height
                  <<"\" viewBox=\"0 0 "<<width<<' '<<height<<"\">\n"<<shapes.str()<<"</svg>\n";
    }
};
inline void dimensions(int& width,int& height) {
    std::cin >> std::ws;
    if (std::cin.eof()) { width=640; height=400; return; }
    std::string extra;
    if (!(std::cin>>width>>height) || (std::cin>>extra) || width<200 || width>1600 || height<200 || height>1600)
        throw std::invalid_argument("expected width height, both 200..1600");
}
