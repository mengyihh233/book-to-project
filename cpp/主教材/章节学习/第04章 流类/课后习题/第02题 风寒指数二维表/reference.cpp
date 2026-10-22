#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
double windChill(double temperature, double speed) {
    if(speed==0) return temperature;
    return 35.74+0.6215*temperature-35.75*std::pow(speed,0.16)
           +0.4275*temperature*std::pow(speed,0.16);
}
int main() {
    std::cout << std::setw(5) << "mph/F";
    for(int t=40;t>=-45;t-=5) std::cout << std::setw(5) << t;
    std::cout << '\n' << std::setw(5) << "calm";
    for(int t=40;t>=-45;t-=5) std::cout << std::setw(5) << t;
    std::cout << '\n';
    for(int v=5;v<=60;v+=5) {
        std::cout << std::setw(5) << v;
        for(int t=40;t>=-45;t-=5)
            std::cout << std::setw(5) << std::lround(windChill(t,v));
        std::cout << '\n';
    }
}
