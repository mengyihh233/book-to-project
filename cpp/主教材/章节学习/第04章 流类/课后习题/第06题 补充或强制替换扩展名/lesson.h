#include "../../../../教学辅助/input_line.h"
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#include <locale>
inline std::string::size_type extensionPosition(const std::string& name) {
    auto slash=name.find_last_of("/\\");
    auto dot=name.find_last_of('.');
    return dot!=std::string::npos && (slash==std::string::npos || dot>slash) ? dot : std::string::npos;
}
inline std::string getRoot(const std::string& name) {
    auto pos=extensionPosition(name);
    return pos==std::string::npos ? name : name.substr(0,pos);
}
inline std::string getExtension(const std::string& name) {
    auto pos=extensionPosition(name);
    return pos==std::string::npos ? "" : name.substr(pos);
}
inline std::string defaultExtension(const std::string& name,std::string ext) {
    bool force=!ext.empty() && ext.front()=='*';
    if(force) ext.erase(0,1);
    if(!ext.empty() && (ext.front()!='.' || ext.find_first_of("/\\*")!=std::string::npos))
        throw std::invalid_argument("extension must be empty or start with dot");
    return force ? getRoot(name)+ext : (getExtension(name).empty() ? name+ext : name);
}
