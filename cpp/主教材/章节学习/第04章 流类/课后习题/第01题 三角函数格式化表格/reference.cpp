#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
int main() {
    const double pi=std::acos(-1.0);
    std::cout << "theta | sin(theta) | cos(theta)\n";
    for(int degree=-90; degree<=90; degree+=15) {
        double s=std::sin(degree*pi/180), c=std::cos(degree*pi/180);
        if(std::abs(s)<0.00000005) s=0;
        if(std::abs(c)<0.00000005) c=0;
        std::cout << std::setw(5) << degree << " | " << std::fixed
                  << std::setprecision(7) << std::setw(10) << s << " | "
                  << std::setw(10) << c << '\n';
    }
}
