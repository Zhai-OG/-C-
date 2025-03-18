
#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
// trie���ڵ�
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


// AC�㷨��
class ACMatcher {
public:
    ACMatcher();
    ~ACMatcher();
    void LoadKeywords(const vector<string>& patterns);
    void ConstructGotoFunction();
    void ConstructFailureFunction();
    vector<int> Search(const string& text); // ����ƥ�䵽��ģʽ������

private:
    int maxStateID;                                       // ���״̬��
    vector<ACNode> nodes;                           // trie��
    vector<string> keywords;                  // ��Ҫƥ���ģʽ
    void addNode(int parentIndex, char ch);                  // ��ʼ����״̬
};

