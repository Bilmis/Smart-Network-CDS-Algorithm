#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include<bits\stdc++.h>
using namespace std;

// Function to read the adjacency list from the input file
bool inputGraphFile(vector<vector<int>> &adj) {
    string filename = "adj_list.txt";
    ifstream ifs(filename);

    if (!ifs.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    int v;

    // Find the number of vertices
    while (getline(ifs, line)) {
        if (isdigit(line[0])) {
            v = stoi(line);
            break;
        }
    }

    // Skip the adjacency list comment line
    getline(ifs, line);
    adj.resize(v);

    // Read adjacency list
    for (int i = 0; i < v; i++) {
        getline(ifs, line);
        istringstream iss(line);
        int num;
        while (iss >> num) {
            adj[i].push_back(num);
        }
    }

    return true;
}

// Function to check if a given set is a connected dominating set
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

int main() {
    vector<vector<int>> adj;

    if (!inputGraphFile(adj)) {
        return 1;
    }

    set<int> bestSet;  
    for (int i = 0; i < adj.size(); i++) {  
        bestSet.insert(i);  
    }
    set<int> currentSet;

    enumerateMCDS(adj, currentSet, bestSet, 0);

    cout << "Size of Minimal Connected Dominating Set: " << bestSet.size() << endl;
    cout << "Vertices in the set: ";
    for (int v : bestSet) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
