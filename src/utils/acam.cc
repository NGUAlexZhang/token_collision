#include <acam.hpp>
#include <queue>
#include <iostream>
#include <cctype>

Acam::Acam(){
    root = 0;
    pidx = 0;
    nodes.emplace_back();
}

void Acam::insert(const std::string& str, int& idx){
    int u = 0;
    for(auto ch : str){
        ch = std::tolower(ch);
        //auto& son = nodes[u].next[ch - 'a'];
        if(nodes[u].next[ch - 'a'] == 0){
            nodes[u].next[ch - 'a'] = nodes.size();
            nodes.emplace_back();
        }
        //if(!son){
        //    int tot = nodes.size();
        //    son = tot;
        //    std::cout << son << std::endl;
        //    nodes.emplace_back();
        //}
        u = nodes[u].next[ch - 'a'];
    }
    if(!nodes[u].idx) nodes[u].idx = ++pidx;
    idx = nodes[u].idx;
}

void Acam::build(){
    std::queue<int> q;
    for(int i = 0; i < 26; i++){
        if(nodes[0].next[i]) q.push(nodes[0].next[i]);
    }
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        for(char i = 0; i < 26; i++){
            if(nodes[u].next[i]){
                nodes[nodes[u].next[i]].fail = nodes[nodes[u].fail].next[i];
                nodes[nodes[nodes[u].fail].next[i]].in++;
                q.push(nodes[u].next[i]);
            }
            else{
                nodes[u].next[i] = nodes[nodes[u].fail].next[i];
            }
        }
    }
}

void Acam::match(const std::string& str){
    int u = 0;
    for(auto ch : str){
        ch = std::tolower(ch);
        if(!(ch <= 'z' && ch >= 'a')){
            u = 0;
            continue;
        }
        u = nodes[u].next[ch - 'a'];
        nodes[u].ans++;
    }
}

Acam::Node::Node(){
    for(int i = 0; i < 26; i++)
        this->next[i] = 0;
    ans = fail = idx = in = depth = 0;
}

void Acam::topu(){
    ans.resize(pidx + 1);
    std::queue<int> q;
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i].in == 0) q.push(i);
    }
    while (!q.empty()){
        int u  = q.front();
        q.pop();
        ans[nodes[u].idx] = nodes[u].ans;
        int v = nodes[u].fail;
        nodes[v].ans += nodes[u].ans;
        if(!(--nodes[v].in)) q.push(v);
    }
    
}

int Acam::getAns(int idx){
    return ans[idx];
}