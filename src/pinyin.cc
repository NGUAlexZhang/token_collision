#include <acam.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <algorithm>

//std::string to_lower(const std::string& str){
//    std::string res;
//    res.reserve(str.size());
//    for(auto ch : str){
//        res += std::tolower(ch);
//    }
//    return res;
//}

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
    ifs.tie(0);
    std::vector<int> idx;
    std::vector<std::string> strs;
    std::string str;
    while(ifs >> str){
        strs.push_back(str);
    }
    idx.resize(strs.size());

    for(int i = 0; i < strs.size(); i++){
        acam.insert(strs[i], idx[i]);
    }
        
    acam.build();

    ifs.close();
    ifs.open(argv[2]);
    while(ifs >> str){
        acam.match(str);
    }
    acam.topu();
    for(int i = 0; i < idx.size(); i++){
        std::cout << strs[i] << " " << acam.getAns(idx[i]) << '\n';
    }
    return 0;
}
