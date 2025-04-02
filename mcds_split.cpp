#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

vector<vector<int>> adj;
int n;

bool is_dominating(const set<int>& D) {
    vector<bool> dominated(n, false);
    for (int u : D) {
        dominated[u] = true;
        for (int v : adj[u]) {
            dominated[v] = true;
        }
    }
    for (bool d : dominated) {
        if (!d) return false;
    }
    return true;
}

bool is_minimal_dominating(set<int> D) {
    if (!is_dominating(D)) return false;
    
    for (int u : D) {
        set<int> D_copy = D;
        D_copy.erase(u);
        if (is_dominating(D_copy)) {
            return false;
        }
    }
    return true;
}

bool is_connected(const set<int>& D) {
    if (D.empty()) return false;
    if (D.size() == 1) return true;
    
    vector<bool> visited(n, false);
    vector<int> component;
    int start = *D.begin();
    component.push_back(start);
    visited[start] = true;
    
    for (size_t i = 0; i < component.size(); ++i) {
        int u = component[i];
        for (int v : adj[u]) {
            if (D.count(v) && !visited[v]) {
                visited[v] = true;
                component.push_back(v);
            }
        }
    }
    
    return component.size() == D.size();
}

void find_mcds_split(set<int>& clique, set<int>& independent, vector<set<int>>& all_mcds) {
    // Case 1: Check if independent set alone is MCDS (only if |I| = 1 and it dominates)
    if (independent.size() == 1) {
        int v = *independent.begin();
        set<int> D = {v};
        if (is_dominating(D)) {
            all_mcds.push_back(D);
        }
    }
    
    // Case 2: MCDS is a subset of the clique
    // We'll try all possible subsets of the clique in order of increasing size
    bool found = false;
    for (size_t k = 1; k <= clique.size() && !found; ++k) {
        vector<bool> mask(clique.size(), false);
        fill(mask.end() - k, mask.end(), true);
        
        do {
            set<int> D;
            int idx = 0;
            for (int u : clique) {
                if (mask[idx]) {
                    D.insert(u);
                }
                idx++;
            }
            
            if (is_dominating(D) && is_connected(D)) {
                // Check if it's minimal
                bool minimal = true;
                for (int u : D) {
                    set<int> D_copy = D;
                    D_copy.erase(u);
                    if (is_dominating(D_copy) && is_connected(D_copy)) {
                        minimal = false;
                        break;
                    }
                }
                if (minimal) {
                    all_mcds.push_back(D);
                    found = true; // We can stop after finding the smallest ones
                }
            }
        } while (next_permutation(mask.begin(), mask.end()));
        
        if (found) break;
    }
}

bool is_split_graph(set<int>& clique, set<int>& independent) {
    // Check if clique is indeed a clique
    for (int u : clique) {
        for (int v : clique) {
            if (u != v && find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
                return false;
            }
        }
    }
    
    // Check if independent set is indeed independent
    for (int u : independent) {
        for (int v : independent) {
            if (u != v && find(adj[u].begin(), adj[u].end(), v) != adj[u].end()) {
                return false;
            }
        }
    }
    
    return true;
}

void find_clique_and_independent(set<int>& clique, set<int>& independent) {
    // Simple heuristic to find a large clique and its complement as independent set
    // This may not always find the maximum clique, but should work for our purposes
    
    vector<int> degrees(n);
    for (int i = 0; i < n; ++i) {
        degrees[i] = adj[i].size();
    }
    
    // Try to find a clique starting with high-degree vertices
    clique.clear();
    for (int i = 0; i < n; ++i) {
        bool can_add = true;
        for (int u : clique) {
            if (find(adj[u].begin(), adj[u].end(), i) == adj[u].end()) {
                can_add = false;
                break;
            }
        }
        if (can_add) {
            clique.insert(i);
        }
    }
    
    // The rest goes to independent set
    independent.clear();
    for (int i = 0; i < n; ++i) {
        if (clique.count(i) == 0) {
            independent.insert(i);
        }
    }
    
    // If we didn't find a good split, try complement
    if (clique.size() < independent.size()) {
        set<int> new_clique;
        set<int> new_independent;
        
        // Try to find a maximal independent set
        vector<bool> in_set(n, false);
        for (int i = 0; i < n; ++i) {
            if (!in_set[i]) {
                new_independent.insert(i);
                in_set[i] = true;
                for (int neighbor : adj[i]) {
                    in_set[neighbor] = true;
                }
            }
        }
        
        // The rest goes to clique
        for (int i = 0; i < n; ++i) {
            if (!in_set[i]) {
                new_clique.insert(i);
            }
        }
        
        // Choose the better split (larger clique)
        if (new_clique.size() > clique.size()) {
            clique = new_clique;
            independent = new_independent;
        }
    }
}

int main() {
    ifstream fin("adj_list.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file adj_list.txt" << endl;
        return 1;
    }
    
    string line;
    // Read number of vertices
    while (getline(fin, line)) {
        if (line.empty() || line[0] == '/') continue;
        n = stoi(line);
        break;
    }
    
    adj.resize(n);
    
    // Read adjacency list
    for (int i = 0; i < n; ++i) {
        while (getline(fin, line)) {
            if (line.empty() || line[0] == '/') continue;
            break;
        }
        
        size_t pos = 0;
        string token;
        while ((pos = line.find(' ')) != string::npos) {
            token = line.substr(0, pos);
            if (!token.empty()) {
                int v = stoi(token);
                adj[i].push_back(v);
            }
            line.erase(0, pos + 1);
        }
        if (!line.empty()) {
            int v = stoi(line);
            adj[i].push_back(v);
        }
    }
    
    // Find clique and independent set (assuming split graph)
    set<int> clique, independent;
    find_clique_and_independent(clique, independent);
    
    if (!is_split_graph(clique, independent)) {
        cout << "The input graph is not a split graph." << endl;
        return 1;
    }
    
    vector<set<int>> all_mcds;
    find_mcds_split(clique, independent, all_mcds);
    
    if (all_mcds.empty()) {
        cout << "No MCDS found (graph might be disconnected)." << endl;
    } else {
        // Find the smallest MCDS
        size_t min_size = INT_MAX;
        for (const auto& mcds : all_mcds) {
            if (mcds.size() < min_size) {
                min_size = mcds.size();
            }
        }
        
        cout << "Minimal Connected Dominating Sets (size " << min_size << "):" << endl;
        for (const auto& mcds : all_mcds) {
            if (mcds.size() == min_size) {
                cout << "{ ";
                for (int v : mcds) {
                    cout << v << " ";
                }
                cout << "}" << endl;
            }
        }
    }
    
    return 0;
}