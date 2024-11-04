#ifndef __ACAM__HPP__
#define __ACAM__HPP__
#include <string>
#include <vector>
class Acam{ //means AC-automaton
private:
    struct Node{
        int next[26];
        int fail;
        int ans;
        int in;
        int idx;
        Node();
        int depth;
    };
    int pidx;
    std::vector<Node> nodes;
    std::vector<int> ans;
    int root; 
public:
    void insert(const std::string& str, int& idx);
    void build();
    void match(const std::string& str);
    void topu();
    int getAns(int idx);
    Acam();
};

#endif