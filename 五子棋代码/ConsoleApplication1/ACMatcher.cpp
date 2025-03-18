#include "ACMatcher.h"
#include <queue>
#include <cassert>

ACMatcher::ACMatcher() : maxStateID(0) {
        addNode(-1, 'a');  // 根节点初始化
        nodes[0].failure = -1;
    }

ACMatcher:: ~ACMatcher() {}

void ACMatcher::LoadKeywords(const vector<string>& keywords) {
        this->keywords = keywords;
    }

void ACMatcher::ConstructGotoFunction() {
    assert(!nodes.empty());

    for (int i = 0; i < keywords.size(); ++i) {
        int curr = 0;  // 从根开始搜索
        for (char c : keywords[i]) {   //C++11 标准，c为keywords中的字符，进行循环 类似于python的for i in is;
            if (nodes[curr].next.find(c) == nodes[curr].next.end()) {
                nodes[curr].next[c] = ++maxStateID;
                addNode(curr, c);
            }
            curr = nodes[curr].next[c];
        }
        nodes[curr].output.push_back(i);
    }
}

void ACMatcher::ConstructFailureFunction() {
    assert(!nodes.empty());

    queue<int> q;
    for (auto& pos : nodes[0].next) {
        nodes[pos.second].failure = 0;
        q.push(pos.second);
    }

    while (!q.empty()) {
        int current = q.front(); q.pop();
        for (auto& pos : nodes[current].next) {
            int failState = nodes[current].failure;
            while (failState != -1 && nodes[failState].next.find(pos.first) == nodes[failState].next.end()) {
                failState = nodes[failState].failure;
            }
            if (failState != -1) {
                nodes[pos.second].failure = nodes[failState].next[pos.first];
                nodes[pos.second].output.insert(end(nodes[pos.second].output), begin(nodes[nodes[pos.second].failure].output), end(nodes[nodes[pos.second].failure].output));
            }
            else {
                nodes[pos.second].failure = 0;
            }
            q.push(pos.second);
        }
    }
}

vector<int> ACMatcher::Search(const string& text) {
    vector<int> matches;
    int curr = 0;

    for (int i = 0; i < text.size();) {
        if (nodes[curr].next.find(text[i]) != nodes[curr].next.end()) {
            curr = nodes[curr].next[text[i]];
            ++i;
        }
        else {
            while (curr != -1 && nodes[curr].next.find(text[i]) == nodes[curr].next.end()) {
                curr = nodes[curr].failure;
            }
            if (curr == -1) {
                curr = 0;
                ++i;
            }
        }

        if (!nodes[curr].output.empty()) {
            matches.insert(end(matches), begin(nodes[curr].output), end(nodes[curr].output));
        }
    }

    return matches;
}
void ACMatcher::addNode(int parentIndex, char ch) {
    nodes.emplace_back(parentIndex, ch);
    assert(nodes.size() - 1 == maxStateID);
}
