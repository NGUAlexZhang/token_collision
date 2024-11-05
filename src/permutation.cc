#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;
int main(int argc, char** argv){
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(argc != 4){
        std::cerr << "Usage: " << argv[0] << " <file1> <file2> <file3> " << std::endl;
        return 1;
    }
    for(int i = 1; i < argc; i++){
        if(!std::filesystem::exists(argv[i])){
            std::cerr << "file " << argv[i] << "do not exist" << std::endl;
            return 1;
        }
    }
    std::vector<std::vector<std::string>> file_str;
    file_str.resize(argc - 1);
    ifstream ifs;
    for(int i = 1; i < argc; i++){
        ifs.open(argv[i]);
        if(!ifs.is_open()){
            std::cerr << "can not open " << argv[i] << std::endl;
            return 1;
        }
        std::string str;
        while(ifs >> str){
            file_str[i - 1].push_back(str);
        }
        ifs.close();
    }
    for(int i = 0; i < file_str[0].size(); i++){
        for(int j = 0; j < file_str[1].size(); j++){
            for(int k = 0; k < file_str[2].size(); k++){
                std::vector<std::string> permutation;
                permutation.push_back(file_str[0][i]);
                permutation.push_back(file_str[1][j]);
                permutation.push_back(file_str[2][k]);
                std::sort(permutation.begin(), permutation.end());
                do{
                    std::cout << permutation[0] + permutation[1] + permutation[2] << "\n";
                }while(std::next_permutation(permutation.begin(), permutation.end()));
            }
        }
    }
    return 0;
}