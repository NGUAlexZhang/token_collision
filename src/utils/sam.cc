#include "sam.hpp"
#include <iostream>


Sam::Sam(){
    root = new State(0, nullptr);
    last = root;
}

void Sam::extend(char ch){
    auto newState = new State(last->len + 1, nullptr);
    auto itera = last;
    while(itera != nullptr && !itera->next.count(ch)){
        itera->addEdge(ch, newState);
        itera = itera->link;
    }
    if(itera == nullptr){
        newState->link = root;
    }
    else{
        auto linkState = itera->next[ch];
        if(linkState->len == itera->len + 1){
            newState->link = linkState;
        }
        else{
            auto clone = new State(itera->len + 1, linkState->link);
            clone->next = linkState->next;
            while(itera != nullptr && itera->next[ch] == linkState){
                itera->next[ch] = clone;
                itera = itera->link;
            }
            linkState->link = clone;
            newState->link = clone;
        }
    }
    last = newState;
}

void Sam::addSubstrStatistic(const std::string& str){
    auto curNode = root;
    auto substr_len = 0;
    for(size_t i = 0; i < str.size(); i++){
        while(curNode != root && !curNode->next.count(str[i])){
            curNode = curNode->link;
            substr_len = curNode->len;
        }
        if(curNode->next.count(str[i])){
            curNode = curNode->next[str[i]];
            substr_len++;
        }
        if(substr_len >= 3){
            substr_statistic[str.substr(i - substr_len + 1, substr_len)]++;
        }
    }
}

std::unordered_map<std::string, int> Sam::getStatistic(){
    return substr_statistic;
}

void Sam::destroy(State* curState, std::set<State*>& visited){
    if(visited.find(curState) == visited.end()) return;
    visited.insert(curState);
    for(auto edge : curState->next){
        destroy(edge.second, visited);
    }
    delete curState;
}

Sam::~Sam(){
    std::set<State*> visited;    
    destroy(root, visited);
}

Sam::State::State(){
    len = 0;
    link = nullptr;
}

Sam::State::State(int len, State* link){
    this->len = len;
    this->link = link;
}

void Sam::State::addEdge(char ch, State* nextNode){
    next[ch] = nextNode;
}
