#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;


struct Node {
    int next[26];
    int fail;
    vector<int> out;
    Node() {
        fill(next, next + 26, -1);
        fail = 0;
    }
};

vector<Node> trie(1);

void insertPattern(const string &p, int id) {
    int cur = 0;
    for (char c : p) {
        int idx = c - 'A';
        if (trie[cur].next[idx] == -1) {
            trie[cur].next[idx] = trie.size();
            trie.emplace_back();
        }
        cur = trie[cur].next[idx];
    }
    trie[cur].out.push_back(id);
}

void buildAutomaton() {
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        int nxt = trie[0].next[i];
        if (nxt != -1) {
            trie[nxt].fail = 0;
            q.push(nxt);
        } else {
            trie[0].next[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int f = trie[u].fail;

        for (int i = 0; i < 26; i++) {
            int v = trie[u].next[i];
            if (v != -1) {
                trie[v].fail = trie[f].next[i];
                trie[v].out.insert(
                    trie[v].out.end(),
                    trie[trie[v].fail].out.begin(),
                    trie[trie[v].fail].out.end()
                );
                q.push(v);
            } else {
                trie[u].next[i] = trie[f].next[i];
            }
        }
    }
}

int main() {


      string text=
 "AGCTTAGGCTACCTGATCGTACCGTAGCTAGCTAGGCTTACGATCGGATCGATGCTAGCTAGCTAGGCTACGATCGTAGCTAGGCTTACCGATCGTAGCTAGCTGATCGTAGGCTAGCTACCTAGGCTAGGCTTACCGTAGCTAGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCTTAGCTAGCTAGGCTAACCGTAGCTAGGCTAGCTACGATCGTAGGCTAGCTACCTAGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTTACCGATCGTAGCTAGGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGGCTTACCGATCGTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGCTAGCTAGGCTAGCTAGGCTTACCGTAGCTAGCTAGGCTAGCTAGGCT";

    vector<string> patterns;
    patterns.push_back("AGCT");
    patterns.push_back("GCTA");
    patterns.push_back("TACG");
    patterns.push_back("CGTAG");
    patterns.push_back("ACCTGA");

    for (int i = 0; i < (int)patterns.size(); i++)
        insertPattern(patterns[i], i);

    buildAutomaton();

    vector<int> count(patterns.size(), 0);
    vector<vector<pair<int, int> > > matches(patterns.size()); 
    // stores (start,end) positions

    int state = 0;

    for (int i = 0; i < (int)text.size(); i++) {
        int idx = text[i] - 'A';
        state = trie[state].next[idx];

        for (int id : trie[state].out) {
            count[id]++;
            int len = patterns[id].size();
            matches[id].push_back(pair<int,int>(i - len + 1, i));
        }
    }

    cout << "FINAL COUNTS:\n";
    for (int i = 0; i < (int)patterns.size(); i++)
        cout << patterns[i] << " : " << count[i] << " times\n";

    cout << "\nMATCH POSITIONS:\n";
    for (int i = 0; i < (int)patterns.size(); i++) {
        cout << "\n" << patterns[i] << ":\n";
        for (auto &p : matches[i]) {
            cout << "Start: " << p.first << ", End: " << p.second << "\n";
        }
    }



    return 0;
}
