#include "sam.hpp"
#include <iostream>
#include <queue>


Sam::Sam(){
    states.emplace_back();
    last = 0;
}

Sam::Sam(const std::string& str){
    for(auto ch : str){
        extend(ch);
    }
}


void Sam::extend(char ch){
    int cur = states.size();
    states.emplace_back();
    states[cur].len = states[last].len + 1;
    states[cur].cnt = 1;
    int p = last;
    while(p != -1 && !states[p].next.count(ch)){
        states[p].next[ch] = cur;
        p = states[p].link;
    }
    if(p == -1){
        states[cur].link = 0;
    }
    else{
        auto q = states[p].next[ch];
        if(states[q].len == states[p].len + 1){
            states[cur].link = q;
        }
        else{
            int clone = states.size();
            states.emplace_back();
            states[clone].len = states[p].len + 1;
            states[clone].next = states[q].next;
            states[clone].link = states[q].link;
            while(p != -1 && states[p].next[ch] == q){
                states[p].next[ch] = clone;
                p = states[p].link;
            }
            states[q].link = states[cur].link = clone;
        }
    }
    last = cur;
}

Sam::State::State(int len, int link, int cnt){
    this->len = len;
    this->link = link;
    this->cnt = cnt;
    this->in = 0;
}

void Sam::countSubstring(std::unordered_map<std::string, int>& statistics){
    for(int i = 0; i < states.size(); i++){
        for(auto p : states[i].next)
            states[p.second].in++;
    }
    std::vector<int> order;
    for(int i = 0; i < states.size(); i++){
        if(states[i].in == 0) order.push_back(i);
    }
    for(int i = 0; i < order.size(); i++){
        int u = order[i] ;
        for(auto p : states[u].next){
            auto v = p.second;
            states[v].in--;
            if(states[v].in == 0)
                order.push_back(v);
        }
        //int v = states[u].link;
        //states[v].in--;
        //states[v].cnt += states[u].cnt;
        //if(states[v].in == 0){
        //    q.push(v);
        //}
    }

    for(int i = order.size() - 1; i >= 0; i--){
        int u = order[i];
        if(states[u].link != -1){
            int v = states[u].link;
            states[v].cnt += states[u].cnt;
        }
    }
    dfs(statistics, "", 0);
}

void Sam::dfs(std::unordered_map<std::string, int>& statistics, std::string str, int cur){
    if(str.size() >= 3){
        statistics[str] += states[cur].cnt;
    }
    for(auto p : states[cur].next){
        dfs(statistics, str + p.first, p.second);
    }
}