#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

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
    for (size_t i = 0; i < p.size(); i++) {   
        char c = p[i];
        int idx = c - 'A';
        if (trie[cur].next[idx] == -1) {
            trie[cur].next[idx] = (int)trie.size();
            trie.push_back(Node());          
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

 
                vector<int> &out_v = trie[v].out;
                vector<int> &out_fail = trie[trie[v].fail].out;
                for (size_t j = 0; j < out_fail.size(); j++)
                    out_v.push_back(out_fail[j]);

                q.push(v);
            } else {
                trie[u].next[i] = trie[f].next[i];
            }
        }
    }
}

int main() {
    high_resolution_clock::time_point start = high_resolution_clock::now(); 

    // string text = "ABABCAB";
    // vector<string> patterns;
    // patterns.push_back("A");
    // patterns.push_back("AB");
    // patterns.push_back("ABC");
    // patterns.push_back("BAB");
    // patterns.push_back("BC");

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
    int state = 0;

    //TRAVERSING THE TEXT STRING
    for (size_t i = 0; i < text.size(); i++) {     
        char c = text[i];
        int idx = c - 'A';
        state = trie[state].next[idx];

        vector<int> &out_vec = trie[state].out;
        for (size_t j = 0; j < out_vec.size(); j++)   
            count[out_vec[j]]++;
    }

    cout << "FINAL COUNTS:\n";
    for (int i = 0; i < (int)patterns.size(); i++)
        cout << patterns[i] << " : " << count[i] << " times\n";

    high_resolution_clock::time_point stop = high_resolution_clock::now(); 
    microseconds duration = duration_cast<microseconds>(stop - start);
    cout << "\nExecution Time: " << duration.count() 
         << " microseconds\n";

    return 0;
}