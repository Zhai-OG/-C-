
#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
// trie树节点
struct ACNode {
    int parent;
    char character;
    int failure;
    map<char, int> next;
    vector<int> output;

    ACNode(int pos, char c) : parent(pos), character(c), failure(-1) {
        int parent;
        char character;
        int failure;
        map<char, int> next;
        vector<int> output;
        }
};


// AC算法类
class ACMatcher {
public:
    ACMatcher();
    ~ACMatcher();
    void LoadKeywords(const vector<string>& patterns);
    void ConstructGotoFunction();
    void ConstructFailureFunction();
    vector<int> Search(const string& text); // 返回匹配到的模式的索引

private:
    int maxStateID;                                       // 最大状态数
    vector<ACNode> nodes;                           // trie树
    vector<string> keywords;                  // 需要匹配的模式
    void addNode(int parentIndex, char ch);                  // 初始化新状态
};

