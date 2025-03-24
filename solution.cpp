/* 
  This is an earlier version of the solution algorithm.
  It is more complex and less efficient compared to Solution2,
  which provides a more optimized and streamlined implementation.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
  vector<unordered_set<int>> adj;
  vector<vector<int>> in_adj;
  vector<bool> visited;
  vector<int> bucket, degree, rank;
  int max_degree=0;

  void show_stats(int val = -1) {
    cout<<"-------------------------------\n";

    if(val != -1) cout<<"selected "<<val<<"\n";

    cout<<"adjacency list: \n";
    for (size_t i = 0; i < adj.size(); i++) { // Use size_t for safety
      cout << "Vertex " << i << " -> ";
      for (int x : adj[i]) {
          cout << x << " ";
      }
      cout << endl;
    }

    cout<<"\nin_adj list:\n";
    for (size_t i = 0; i < adj.size(); i++) { // Use size_t for safety
      cout << "Vertex " << i << " -> ";
      for (int x : in_adj[i]) {
          cout << x << " ";
      }
      cout << endl;
    }

    cout<<"\nver\tvis\tdeg\tbuc\trank\n";
    for(size_t i=0; i<adj.size(); i++) {
      cout<<i<<"\t"<<visited[i]<<"\t"<<degree[i]<<"\t"<<bucket[i]<<"\t"<<rank[i]<<endl;
    }

    cout<<endl;
  }

  void initList(const vector<vector<int>>& adj_list) {
    int v = adj_list.size();

    degree = vector<int>(v);
    bucket = vector<int>(v);
    rank = vector<int>(v);

    visited = vector<bool>(v, false);
    adj = vector<unordered_set<int>>(v);
    in_adj = vector<vector<int>>(v);

    for (int i = 0; i < v; i++) {
      for (int adj_node : adj_list[i]) {
        if(adj_node == i) cout<<"self-loop\n";
        if(adj[i].find(adj_node) != adj[i].end()) cout<<"multipath\n";

        adj[i].insert(adj_node);
        in_adj[adj_node].push_back(i);
      }
      degree[i] = adj_list[i].size();
      max_degree = max(max_degree, degree[i]);
    }

    updateRank();
  }

  int visit(int node) {
    if (visited[node]) return 0;

    visited[node] = true;
    for (int in_node : in_adj[node]) {
      adj[in_node].erase(node);
      degree[in_node]--;
    }

    in_adj[node].clear();
    return 1;
  }

  void updateRank() {
    int v = adj.size(), n=max_degree;

    for (int i = 0; i < v; i++) {
      int cur = max_degree;
      for (int adj_node : adj[i]) {
        cur = min(cur, degree[adj_node]);
      }
      bucket[i] = cur;
      rank[i] = (n*n*(n - bucket[i]) + n*degree[i]);
      if(!visited[i]) rank[i]++;
    }
  }

  int getVertex() {
    int cur = -1, v = adj.size();
    for (int i = 0; i < v; i++) {
      if (visited[i] && degree[i] == 0) continue;
      if (!visited[i] && in_adj[i].empty()) return i;

      if (cur == -1 || bucket[i] < bucket[cur] || (bucket[i] == bucket[cur] && degree[i] > degree[cur]) || (bucket[i] == bucket[cur] && degree[i] == degree[cur] && visited[cur])) {
        cur = i;
      }

      // if(cur == -1 || rank[i] > rank[cur]) cur = i;

    }
    return cur;
  }

  int dominate(int node) {
    int count = 0;

    vector<int> temp(adj[node].begin(), adj[node].end());
    for (int adj_node : temp) 
       count += visit(adj_node);
    count += visit(node);

    updateRank();
    return count;
  }

public:
  vector<int> dominatingSet(vector<vector<int>>& adj_list) {
    vector<int> set;
    initList(adj_list);

    int rem = adj_list.size();
    while (rem > 0) {
      int cur_node = getVertex();
      if (cur_node == -1) break;
      int new_visit = dominate(cur_node);

      // show_stats(cur_node);
      if (new_visit > 0) {
        set.push_back(cur_node);
        rem -= new_visit;
      }
    }

    return set;
  }
};

