#include <sam.hpp>
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

void Sam::extend(const std::string& str){
    last = 0;
    for(auto ch : str){
        extend(ch);
    }
}

void Sam::extend(char ch){
    if(states[last].next.count(ch)){
        int cur = states[last].next[ch];
        states[cur].cnt++;
        last = cur;
        return;
    }
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

std::unordered_map<std::string, int> Sam::countSubstring(int frequency){
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
    }

    for(int i = order.size() - 1; i >= 0; i--){
        int u = order[i];
        if(states[u].link != -1){
            int v = states[u].link;
            states[v].cnt += states[u].cnt;
        }
    }
    dfs(0, frequency);
    return states[0].statistics;
}

void Sam::dfs(int cur, int frequency){
    if(states[cur].cnt < frequency)
        return;
    states[cur].statistics[""] = states[cur].cnt;
    for(auto p : states[cur].next){
        if(!states[p.second].statistics.size()){
            dfs(p.second, frequency);
        }
        for(auto suffix : states[p.second].statistics){
            states[cur].statistics[p.first + suffix.first] = suffix.second;
        }
    }
}

void Sam::clear(){
    last = 0;
    states.clear();
    states.emplace_back();

}