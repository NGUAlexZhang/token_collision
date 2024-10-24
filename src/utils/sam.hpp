#ifndef __SAM__HPP__
#define __SAM__HPP__

#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>

class Sam{
private:
    struct State{
        int len;
        State* link;
        std::map<char, State*> next;
        State();
        State(int len, State* link);
        void addEdge(char ch, State* nextState);
    };
    void destroy(State* curState, std::set<State*>& visited);
    State* root;
    State* last;
    std::unordered_map<std::string, int> substr_statistic;
public:
    void recurse(State* cur){
        std::cout << cur->len << std::endl;
        for(auto p : cur->next){
            recurse(p.second);
        }
    }
    void print(){
       recurse(root);
    }
    Sam();
    void extend(char ch);
    void addSubstrStatistic(const std::string& str);
    std::unordered_map<std::string, int> getStatistic();
    ~Sam();
};

#endif