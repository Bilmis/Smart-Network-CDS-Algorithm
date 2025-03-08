#include<bits/stdc++.h>
using namespace std;

class Solution2 {

  vector<unordered_set<int>> degree_map;
  vector<vector<int>> adj;
  vector<int> degree, utility;
  vector<bool> visited;

  void initialise(vector<vector<int>> &adj_list, int &max_deg) {
    int v = adj_list.size();
    adj = adj_list;

    degree = vector<int>(v);
    utility = vector<int>(v);
    visited = vector<bool>(v);
    
    for(int i=0; i<v; i++) {
      degree[i] = adj[i].size();
      utility[i] = adj[i].size()+1;
      max_deg = max(max_deg, degree[i]);
    }

    degree_map = vector<unordered_set<int>>(max_deg+1);
    for(int i=0; i<v; i++) {
      degree_map[degree[i]].insert(i);
    }

  }

  void show_stats() {
    int v = adj.size();

    cout<<"\nAdjacency list: \n";
    for (size_t i = 0; i < v; i++) { // Use size_t for safety
      cout << "Vertex " << i << " -> ";
      for (int x : adj[i]) {
          cout << x << " ";
      }
      cout << endl;
    }

    cout<<"\nDegree map:\n";
    for(size_t i=0; i < degree_map.size(); i++) {
      cout << "Deg = " << i << ": ";
      for (int x : degree_map[i]) {
        cout << x << " ";
      }
      cout << endl;
    }

    cout<<"\nver\tvis\tdeg\tutil\n";
    for(size_t i=0; i<v; i++) {
      cout<<i<<"\t"<<visited[i]<<"\t"<<degree[i]<<"\t"<<utility[i]<<endl;
    }

    cout<<endl;
  }

  void visit(int node) {
    // when visiting the node first time
    if(visited[node]) return;

    degree_map[degree[node]].erase(node);
    visited[node] = true;
    utility[node]--;

    // decrease every incoming edge utility
    for(int adj_node: adj[node]) utility[adj_node]--;
  }

  void dominate(int node) {
    visit(node);
    for(int adj_node: adj[node]) visit(adj_node);
  }

  void cover(vector<int>& res, int i) {

    while(!degree_map[i].empty()) {
      int selected = *degree_map[i].begin();

      for(int node: degree_map[i]) {
        if(utility[node] > utility[selected]) selected = node;

        for(int adj_node: adj[node]) {
          if(utility[adj_node] > utility[selected]) selected = adj_node;
        }
      }

      res.push_back(selected);
      dominate(selected);
    }
  }

  public:
  vector<int> dominatingSet(vector<vector<int>> &adj_list) {
    vector<int> res;

    int max_deg = 0;
    initialise(adj_list, max_deg);

    // show_stats();

    for(int i=0; i<=max_deg; i++) {
      cover(res, i);
    }

    return res;
  }
};