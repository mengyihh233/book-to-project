#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

void mergesort(std::vector<int>&v){if(v.size()<2)return;auto mid=v.begin()+v.size()/2;std::vector<int>a(v.begin(),mid),b(mid,v.end());mergesort(a);mergesort(b);std::merge(a.begin(),a.end(),b.begin(),b.end(),v.begin());}
int main(){std::vector<int>v{5,2,2,-1,9};mergesort(v);assert((v==std::vector<int>{-1,2,2,5,9}));std::vector<int>e;mergesort(e);for(int x:v)std::cout<<x<<" ";}
