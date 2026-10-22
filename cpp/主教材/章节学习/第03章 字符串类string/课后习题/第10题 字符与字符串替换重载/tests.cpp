#include "lesson.h"
#include <cassert>
#include <iostream>
int main() { std::string s="aaa"; assert(replaceAll(s,'a','b')=="bbb" && s=="aaa"); assert(replaceAll(s,std::string("aa"),std::string("b"))=="ba"); assert(replaceAll("aa",std::string("a"),std::string("aa"))=="aaaa"); assert(replaceAll("abc",std::string("b"),std::string())=="ac"); bool bad=false; try { replaceAll("abc",std::string(),std::string("x")); } catch(const std::invalid_argument&) { bad=true; } assert(bad); bad=false; try { replaceAll(std::string(1001,'a'),std::string("a"),std::string(1000,'b')); } catch(const std::length_error&) { bad=true; } assert(bad); std::cout<<"contracts passed\n"; }
