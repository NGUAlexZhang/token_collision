#include "sam.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv){
    if(argc < 2){
        return 1;
    }
    Sam sam;
    std::ifstream ifs(argv[1]);
    std::string str;
    while(ifs >> str){
        sam.addSubstrStatistic(str);
        for(auto ch : str){
            sam.extend(ch);
        }
        sam.extend(0);
    }
    //sam.print();
    auto statistic = sam.getStatistic();
    for(auto p : statistic){
        if(p.second + 1 >= 3)
            std::cout << p.first << " " << p.second + 1 << std::endl;
    }
    return 0;
}