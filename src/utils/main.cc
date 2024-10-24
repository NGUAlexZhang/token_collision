#include "sam.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv){
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    if(argc < 2){
        std::cout << "Usage analyzer <filename>";
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
