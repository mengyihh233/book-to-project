#include "std_lib_facilities.h"
int main(){
    vector<int> numbers{1,2,3};
    int total=0;
    for(int n:numbers)total+=n;
    cout<<"Book support header ready: "<<total<<'\n';
    return total==6?0:1;
}
