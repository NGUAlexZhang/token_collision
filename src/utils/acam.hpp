#include <string>
#include <unordered_map>
#include <set>
class Acam{ //means AC-automaton
private:
    struct Node{
        Node* next[26];
        bool endpos;
        Node* fail;
        Node();
        int depth;
    };
    Node* root; 
    std::unordered_map<std::string, int> statistics;
    void destroy(Node* cur, std::set<Node*>& deleted);
public:
    void insert(const std::string& str);
    void build();
    void match(const std::string& str);
    std::unordered_map<std::string, int> getStatistics();
    Acam();
    ~Acam();
};