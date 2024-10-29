#include "utils/sam.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>

int main(int argc, char** argv){
    std::ios_base::sync_with_stdio(0);
    std::cout.tie(0);
    if(argc < 3){
        std::cerr << "Usage frequency <filename> <minimum occurance frequency>";
        return 1;
    }
    try{
        auto frequency = std::stoi(argv[2]);
        if(frequency <= 0){
            throw std::runtime_error("frequency must large than 0");
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    auto frequency = std::stoi(argv[2]);
    std::ifstream ifs(argv[1]);
    std::string str;
    if(!ifs.is_open()){
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }
    ifs.tie(0);
    std::unordered_map<std::string, int> res;
    Sam sam;
    while(ifs >> str){
        for(auto ch : str){
            sam.extend(ch);
        }
        sam.countSubstring(res);
        sam.clear();
    }
    for(auto p : res){
        if(p.second >= frequency)
            std::cout << p.first << " " << p.second << std::endl;
    }
    return 0;
}
