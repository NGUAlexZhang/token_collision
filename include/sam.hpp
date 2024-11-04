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
        std::unordered_map<std::string, int> statistics;
    };
    void dfs(int cur, int frequency);
    int last;

public:
    std::vector<State> states;
    Sam(const std::string& s);
    Sam();
    void extend(char ch);
    void extend(const std::string& str);
    std::unordered_map<std::string, int> countSubstring(int frequency = 10);
    void clear();
};

#endif