#include <iostream>
#include <list>
#include <string>
#include <algorithm>

int Print(int & text){
    std::cout<<text<<std::endl;
    return 0;
}

int main(){
    std::list<int> Karo;
    Karo.push_back(67);
    Karo.push_back(43);
    Karo.push_back(927);
    
    for_each(Karo.begin(), Karo.end(), Print );
    return 0;
}