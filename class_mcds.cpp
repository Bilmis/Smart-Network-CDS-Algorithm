// #include<bits/stdc++.h>
// using namespace std;

// class Exact{
//       public:
//       vector<vector<int>> adj;
//       set<int> clique, independent,D;
//       int n;
//       Exact(vector<vector<int>> adj){
//           this->adj=adj;
//           for (int i = 0; i < n; ++i) {
//               bool is_clique_member = true;
//               for (int j : clique) {
//                   if (find(adj[i].begin(), adj[i].end(), j) == adj[i].end()) {
//                       is_clique_member = false;
//                       break;
//                   }
//               }
//               if (is_clique_member) clique.insert(i);
//               else independent.insert(i);
//           }
//           D=find_one_mcds_split();
//       }

//       // Checks if a set D dominates all vertices
//       bool is_dominating(const set<int> &D) {
//         vector<bool> dominated(n, false);
//         for (int u : D) {
//             dominated[u] = true;
//             for (int v : adj[u]) {
//                 dominated[v] = true;
//             }
//         }
//         return all_of(dominated.begin(), dominated.end(), [](bool d) { return d; });
//       }

//       // Checks if the subgraph induced by D is connected
//       bool is_connected(const set<int> &D) {
//         if (D.empty()) return false;
//         if (D.size() == 1) return true;
        
//         vector<bool> visited(n, false);
//         vector<int> stack = {*D.begin()};
//         visited[*D.begin()] = true;
//         int visited_count = 1;

//         while (!stack.empty()) {
//             int u = stack.back();
//             stack.pop_back();
//             for (int v : adj[u]) {
//                 if (D.count(v) && !visited[v]) {
//                     visited[v] = true;
//                     stack.push_back(v);
//                     visited_count++;
//                 }
//             }
//         }
//         return visited_count == D.size();
//       }

//       // Finds one MCDS in a split graph (clique C, independent set I)
//       set<int> find_one_mcds_split() {
//         // Case 1: Check if the independent set alone is an MCDS (only if |I| = 1 and it dominates)
//         if (independent.size() == 1) {
//             int v = *independent.begin();
//             if (is_dominating({v})) {
//                 return {v};
//             }
//         }

//         // Case 2: Search for the smallest MCDS in the clique
//         // Try all possible subset sizes from 1 to |C|
//         for (int k = 1; k <= clique.size(); ++k) {
//             vector<bool> mask(clique.size(), false);
//             fill(mask.end() - k, mask.end(), true);

//             do {
//                 set<int> D;
//                 int idx = 0;
//                 for (int u : clique) {
//                     if (mask[idx]) D.insert(u);
//                     idx++;
//                 }

//                 if (is_dominating(D) && is_connected(D)) {
//                     // Verify minimality (no proper subset is a CDS)
//                     bool minimal = true;
//                     for (int u : D) {
//                         set<int> D_sub = D;
//                         D_sub.erase(u);
//                         if (is_dominating(D_sub) && is_connected(D_sub)) {
//                             minimal = false;
//                             break;
//                         }
//                     }
//                     if (minimal) {
//                         return D; // Return the first MCDS found
//                     }
//                 }
//             } while (next_permutation(mask.begin(), mask.end()));
//         }

//         return {}; // No MCDS found (should not happen for connected split graphs)
//       }
// };
#include <bits/stdc++.h>
using namespace std;

class Exact {
public:
    vector<vector<int>> adj;
    set<int> clique, independent, D;
    int n;
    
    Exact(vector<vector<int>> adj) : adj(adj) {
        n = adj.size();  // Initialize n first!
        
        // Find clique and independent set
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
        D = find_one_mcds_split();
    }

    bool is_dominating(const set<int> &D) {
        vector<bool> dominated(n, false);
        for (int u : D) {
            dominated[u] = true;
            for (int v : adj[u]) {
                dominated[v] = true;
            }
        }
        return all_of(dominated.begin(), dominated.end(), [](bool d) { return d; });
    }

    bool is_connected(const set<int> &D) {
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

    set<int> find_one_mcds_split() {
        // Case 1: Check independent set
        if (independent.size() == 1) {
            int v = *independent.begin();
            if (is_dominating({v})) {
                return {v};
            }
        }

        // Case 2: Check clique subsets
        vector<int> clique_vec(clique.begin(), clique.end());
        int k = clique_vec.size();

        // Try subsets from smallest to largest
        for (int subset_size = 1; subset_size <= k; ++subset_size) {
            vector<bool> mask(k, false);
            fill(mask.end() - subset_size, mask.end(), true);

            do {
                set<int> candidate;
                for (int i = 0; i < k; ++i) {
                    if (mask[i]) candidate.insert(clique_vec[i]);
                }

                if (is_dominating(candidate) && is_connected(candidate)) {
                    // Verify minimality
                    bool minimal = true;
                    for (int u : candidate) {
                        set<int> temp = candidate;
                        temp.erase(u);
                        if (is_dominating(temp) && is_connected(temp)) {
                            minimal = false;
                            break;
                        }
                    }
                    if (minimal) {
                        return candidate;
                    }
                }
            } while (next_permutation(mask.begin(), mask.end()));
        }

        return {};
    }
};