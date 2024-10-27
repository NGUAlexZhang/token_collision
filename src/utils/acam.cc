#include "acam.hpp"
#include <queue>

Acam::Acam(){
    root = new Node();
    root->fail = root;
}

void Acam::insert(const std::string& str){
    auto cur = root;
    for(auto ch : str){
        if(cur->next[ch - 'a'] == 0){
            cur->next[ch - 'a'] = new Node();
            cur->next[ch - 'a']->depth = cur->depth + 1;
            cur->next[ch - 'a']->fail = root;
        }
        cur = cur->next[ch - 'a'];
    }
    cur->endpos = true;
}

void Acam::build(){
    std::queue<Node*> q;
    for(int i = 0; i < 26; i++){
        if(root->next[i]){
            q.push(root->next[i]);
        }
        else root->next[i] = root;
    }
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        for(char i = 0; i < 26; i++){
            if(u->next[i]){
                u->next[i]->fail = u->fail->next[i];
                q.push(u->next[i]);
            }
            else{
                u->next[i] = u->fail->next[i];
            }
        }
    }
}

void Acam::match(const std::string& str){
    auto cur = root;
    for(int i = 0; i < str.length(); i++){
        cur = cur->next[str[i] - '0'];
        auto iterator = cur;
        while(iterator != root){
            if(iterator->endpos){
                statistics[str.substr(i - iterator->depth + 1, iterator->depth)]++;
            }
            iterator = iterator->fail;
        }
    }
}

std::unordered_map<std::string, int> Acam::getStatistics(){
    return statistics;
}

void Acam::destroy(Node* cur, std::set<Node*>& deleted){
    if(deleted.find(cur) != deleted.end()) return;
    deleted.insert(cur);
    for(int i = 0; i < 26; i++){
        destroy(cur->next[i], deleted);
    }
    delete cur; 
}

Acam::~Acam(){
    std::set<Node*> deleted;
    destroy(root, deleted);
}

Acam::Node::Node(){
    for(int i = 0; i < 26; i++)
        this->next[i] = nullptr;
    fail = nullptr;
    depth = 0;
    endpos = false;
}

