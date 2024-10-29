#ifndef __SAM__HPP__
#define __SAM__HPP__

#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <queue>

class Sam{
private:
    struct State{
        int in;
        int len;
        int link;
        int cnt;
        std::map<char, int> next;
        State(int len = 0, int link = -1, int cnt = 0);
    };
    int last;

public:
    std::vector<State> states;
    Sam(const std::string& s);
    Sam();
    void extend(char ch);
    void countSubstring(std::unordered_map<std::string, int>& statistics);
    void dfs(std::unordered_map<std::string, int>& statistics, std::string str, int cur);
};

#endif