#include<bits\stdc++.h>
using namespace std;

class Exact {
  bool isConnectedDominatingSet(vector<vector<int>> &adj, set<int> &subset) {
    int n = adj.size();
    vector<bool> dominated(n, false);
    vector<bool> visited(n, false);

    if (subset.empty()) return false;

    // Mark nodes in the subset as dominated and visited
    for (int u : subset) {
        dominated[u] = true;
        visited[u] = true;
        for (int v : adj[u]) {
            dominated[v] = true;
        }
    }

    // BFS to check connectivity
    vector<int> queue(subset.begin(), subset.end());
    int front = 0;
    while (front < queue.size()) {
        int u = queue[front++];
        for (int v : adj[u]) {
            if (subset.count(v) && !visited[v]) {
                visited[v] = true;
                queue.push_back(v);
            }
        }
    }

    // Check if all vertices are dominated
    if (!all_of(dominated.begin(), dominated.end(), [](bool d) { return d; })) return false;

    // Check if the subset forms a connected subgraph
    return all_of(subset.begin(), subset.end(), [&visited](int u) { return visited[u]; });
}

public:
// Backtracking function to enumerate minimal connected dominating sets
void enumerateMCDS(vector<vector<int>> &adj, set<int> &currentSet, set<int> &bestSet, int index) {
    int n = adj.size();

    if (currentSet.size() >= bestSet.size()) return;  // Prune if already worse

    if (isConnectedDominatingSet(adj, currentSet)) {
        bestSet = currentSet;
        return;
    }

    for (int i = index; i < n; i++) {
        if (currentSet.count(i)) continue;
        currentSet.insert(i);
        enumerateMCDS(adj, currentSet, bestSet, i + 1);
        currentSet.erase(i);
    }
}
};