#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#include <sys/stat.h>
#else
#include <unistd.h>
#endif
inline std::string readAsciiFile(const std::string& name) {
    if(name.empty()) throw std::invalid_argument("empty input path");
    std::ifstream in(std::filesystem::u8path(name),std::ios::binary);
    if(!in) throw std::runtime_error("cannot open input");
    std::string data;char c;
    while(in.get(c)) {
        if(static_cast<unsigned char>(c)>127) throw std::invalid_argument("ASCII content required");
        if(data.size()>=16*1024*1024) throw std::length_error("input exceeds 16 MiB");
        data+=c;
    }
    if(in.bad()) throw std::runtime_error("read failure");
    return data;
}
inline void writeNewFile(const std::string& name,const std::string& text) {
    if(name.empty()) throw std::invalid_argument("empty output path");
    auto path=std::filesystem::u8path(name);
#ifdef _WIN32
    int fd=_wopen(path.c_str(),_O_WRONLY|_O_CREAT|_O_EXCL|_O_BINARY,_S_IREAD|_S_IWRITE);
#else
    int fd=::open(path.c_str(),O_WRONLY|O_CREAT|O_EXCL,0666);
#endif
    if(fd<0) throw std::runtime_error("output exists or cannot be created");
    bool failed=false;
    for(std::size_t pos=0;pos<text.size();) {
        auto count=static_cast<unsigned int>(std::min<std::size_t>(text.size()-pos,1048576));
#ifdef _WIN32
        auto written=_write(fd,text.data()+pos,count);
#else
        auto written=::write(fd,text.data()+pos,count);
#endif
        if(written<0 && errno==EINTR) continue;
        if(written<=0) {failed=true;break;}
        pos+=static_cast<std::size_t>(written);
    }
#ifdef _WIN32
    if(_close(fd)!=0) failed=true;
#else
    if(::close(fd)!=0) failed=true;
#endif
    if(failed) {
        std::error_code ignored;std::filesystem::remove(path,ignored);
        throw std::runtime_error("write failure");
    }
}
