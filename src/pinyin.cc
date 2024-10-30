#include <acam.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <algorithm>

std::string to_lower(const std::string& str){
    std::string res;
    res.reserve(str.size());
    for(auto ch : str){
        res += std::tolower(ch);
    }
    return res;
}

int main(int argc, char** argv){
    std::ios_base::sync_with_stdio(0);
    std::cout.tie(0);
    if(argc < 3){
        std::cerr << "Usage pinyin <database> <text file> <minimum occurance frequency>";
        return 1;
    }
    try{
        auto frequency = std::stoi(argv[3]);
        if(frequency <= 0){
            throw std::runtime_error("frequency must large than 0");
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    auto frequency = std::stoi(argv[3]);
    Acam acam;
    if(!std::filesystem::exists(argv[1])){
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }

    if(!std::filesystem::exists(argv[2])){
        std::cerr << "Cannot open file: " << argv[2] << std::endl;
        return 1;
    }
    std::ifstream ifs(argv[1]);
    std::string str;
    ifs.tie(0);
    while(ifs >> str){
        acam.insert(str);
    }
    acam.build();

    ifs.close();
    ifs.open(argv[2]);
    while(ifs >> str){
        str = to_lower(str);
        acam.match(str);
    }
    auto statistics = acam.getStatistics();
    for(auto p : statistics){
        if(p.second >= frequency)
            std::cout << p.first << " " << p.second << std::endl;
    }
    return 0;
}
