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

// Checks if a set D dominates all vertices
bool is_dominating(const set<int>& D) {
    vector<bool> dominated(n, false);
    for (int u : D) {
        dominated[u] = true;
        for (int v : adj[u]) {
            dominated[v] = true;
        }
    }
    return all_of(dominated.begin(), dominated.end(), [](bool d) { return d; });
}

// Checks if the subgraph induced by D is connected
bool is_connected(const set<int>& D) {
    if (D.empty()) return false;
    if (D.size() == 1) return true;
    
    vector<bool> visited(n, false);
    vector<int> stack = {*D.begin()};
    visited[*D.begin()] = true;
    int visited_count = 1;

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        for (int v : adj[u]) {
            if (D.count(v) && !visited[v]) {
                visited[v] = true;
                stack.push_back(v);
                visited_count++;
            }
        }
    }
    return visited_count == D.size();
}

// Finds one MCDS in a split graph (clique C, independent set I)
set<int> find_one_mcds_split(const set<int>& clique, const set<int>& independent) {
    // Case 1: Check if the independent set alone is an MCDS (only if |I| = 1 and it dominates)
    if (independent.size() == 1) {
        int v = *independent.begin();
        if (is_dominating({v})) {
            return {v};
        }
    }

    // Case 2: Search for the smallest MCDS in the clique
    // Try all possible subset sizes from 1 to |C|
    for (int k = 1; k <= clique.size(); ++k) {
        vector<bool> mask(clique.size(), false);
        fill(mask.end() - k, mask.end(), true);

        do {
            set<int> D;
            int idx = 0;
            for (int u : clique) {
                if (mask[idx]) D.insert(u);
                idx++;
            }

            if (is_dominating(D) && is_connected(D)) {
                // Verify minimality (no proper subset is a CDS)
                bool minimal = true;
                for (int u : D) {
                    set<int> D_sub = D;
                    D_sub.erase(u);
                    if (is_dominating(D_sub) && is_connected(D_sub)) {
                        minimal = false;
                        break;
                    }
                }
                if (minimal) {
                    return D; // Return the first MCDS found
                }
            }
        } while (next_permutation(mask.begin(), mask.end()));
    }

    return {}; // No MCDS found (should not happen for connected split graphs)
}

int main() {
    ifstream fin("adj_list.txt");
    if (!fin.is_open()) {
        cerr << "Error: Could not open adj_list.txt" << endl;
        return 1;
    }

    // Read input graph
    string line;
    while (getline(fin, line)) {
        if (line.empty() || line.find("//") != string::npos) continue;
        n = stoi(line);
        break;
    }

    adj.resize(n);
    for (int i = 0; i < n; ++i) {
        while (getline(fin, line)) {
            if (line.empty() || line.find("//") != string::npos) continue;
            break;
        }
        size_t pos = 0;
        string token;
        while ((pos = line.find(' ')) != string::npos) {
            token = line.substr(0, pos);
            if (!token.empty()) adj[i].push_back(stoi(token));
            line.erase(0, pos + 1);
        }
        if (!line.empty()) adj[i].push_back(stoi(line));
    }

    // Heuristic: Assume the first high-degree vertex is in the clique
    set<int> clique, independent;
    for (int i = 0; i < n; ++i) {
        bool is_clique_member = true;
        for (int j : clique) {
            if (find(adj[i].begin(), adj[i].end(), j) == adj[i].end()) {
                is_clique_member = false;
                break;
            }
        }
        if (is_clique_member) clique.insert(i);
        else independent.insert(i);
    }

    // Find one MCDS
    set<int> mcds = find_one_mcds_split(clique, independent);

    // Output the result
    if (mcds.empty()) {
        cout << "No MCDS found (graph might be disconnected)." << endl;
    } else {
        cout << "Found an MCDS of size " << mcds.size() << ": { ";
        for (int v : mcds) cout << v << " ";
        cout << "}" << endl;
    }

    return 0;
}