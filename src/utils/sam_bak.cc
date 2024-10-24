#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <string>
const int N = 1e7 ;
struct Sam{
    int len, link;
    std::map<char, int> next;
};
Sam st[N];
int sz, last;
void sam_init(){
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}
void sam_extend(char c){
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)){
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1){
        st[cur].link = 0;
    }
    else{
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len){
            st[cur].link = q;
        }
        else{
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q){
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void recurse(int now){
    std::cout << st[now].len << std::endl;
    for(auto p : st[now].next){
        recurse(p.second);
    }
}

int main(int argc, char** argv){

    std::ifstream ifs(argv[1]);
    if(!ifs.is_open()){
        std::cerr << "can not open " << argv[1] << std::endl;
        return 1;
    }
    sam_init();
    std::string str;
    std::map<std::string, int> exist_cnt;
    int cnt = 0, tot = 0;
    while(ifs >> str){
        int v = 0, l = 0, bestpos = 0, best = 0;
        for(size_t i = 0; i < str.size(); i++){
            while(v && !st[v].next.count(str[i])){
                v = st[v].link;
                l = st[v].len;
            }
            if(st[v].next.count(str[i])){
                v = st[v].next[str[i]];
                l++;
            }
            if(l >= 3){
//                std::cout << str.substr(i - l + 1, l) << " " << l << "\n";
                if(i - l + 1 < 0) puts("fuk");
                exist_cnt[str.substr(i - l + 1, l)]++;
            }
        }
        for(auto ch : str){
            sam_extend(ch);
        }
        sam_extend(0);
    }
    // for(auto p : exist_cnt){
        // if(p.second >= 4){
            // std::cout << p.first << " " << p.second << "\n";
        // }
    // }
    recurse(0);
    return 0;
}