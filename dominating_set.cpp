#include<bits/stdc++.h>
#include<vector>
#include "test-kit.cpp"

using namespace std;

class Solution {
  vector<unordered_set<int>> adj;
  vector<vector<int>> in_adj;
  vector<bool> visited;
  vector<int> bucket, degree;

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

    cout<<"\nver\tvis\tdeg\tbuc\n";
    for(size_t i=0; i<adj.size(); i++) {
      cout<<i<<"\t"<<visited[i]<<"\t"<<degree[i]<<"\t"<<bucket[i]<<endl;
    }

    cout<<endl;
  }

  void initList(const vector<vector<int>>& adj_list) {
    int v = adj_list.size();

    degree = vector<int>(v);
    bucket = vector<int>(v);
    visited = vector<bool>(v, false);
    adj = vector<unordered_set<int>>(v);
    in_adj = vector<vector<int>>(v);

    for (int i = 0; i < v; i++) {
      for (int adj_node : adj_list[i]) {
        adj[i].insert(adj_node);
        in_adj[adj_node].push_back(i);
      }
      degree[i] = adj_list[i].size();
    }

    updateBucket();
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

  void updateBucket() {
    int v = adj.size();

    for (int i = 0; i < v; i++) {
      int cur = INT_MAX;
      for (int adj_node : adj[i]) {
        cur = min(cur, degree[adj_node]);
      }
      bucket[i] = cur;
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
    }
    return cur;
  }

  int dominate(int node) {
    int count = 0;

    vector<int> temp(adj[node].begin(), adj[node].end());
    for (int adj_node : temp) 
       count += visit(adj_node);
    count += visit(node);

    updateBucket();
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

void inputGraph(vector<vector<int>> &adj) {
  int v;
  string line;

  cout << "No. of vertices: ";
  cin >> v;
  cin.ignore(); // Ignore leftover newline

  adj = vector<vector<int>>(v);

  for (int i = 0; i < v; i++) {
      cout << "Adj of vertex " << i << ": ";
      getline(cin, line); // Read the full line

      istringstream iss(line);
      int num;
      while (iss >> num) {
          adj[i].push_back(num);
      }
  }
}

void inputGraphFile(vector<vector<int>> &adj) {
  string filename = "adj_list.txt";
  ifstream ifs(filename);

  if(!ifs.is_open()) {
    cout<<"Error";
    return;
  }

  string line;
  int v;

  while(getline(ifs, line)) {
    if(isdigit(line[0])) {
      v = stoi(line);
      break;
    } 
  }

  getline(ifs, line);
  adj.resize(v);

  for(int i=0; i<v; i++) {
    getline(ifs, line);

    istringstream iss(line);
    int num;
    while (iss >> num) {
        adj[i].push_back(num);
    }
  }
}

void printGraph(const vector<vector<int>> &adj) { // Use 'const' to prevent modification
    cout << "\nAdjacency List:\n";
    for (size_t i = 0; i < adj.size(); i++) { // Use size_t for safety
        cout << "Vertex " << i << " -> ";
        for (int x : adj[i]) {
            cout << x << " ";
        }
        cout << endl;
    }
}

int main() {
  vector<vector<int>> adj;
  inputGraphFile(adj);

  Solution sol;
  vector<int> d_set = sol.dominatingSet(adj);
  cout<<"\ndominating set: ";
  for(int d: d_set) cout<<d<<" ";
  cout<<" { "<<d_set.size()<<" }"<<endl;

  TestKit tk;
  cout<<"verification of minimality: ";
  tk.isMinimalSet(adj, d_set);

  cout<<"\nverification of domination: "<<(tk.isDominatingSet(adj, d_set)?"true":"false");

  cout<<"\nverification of minimum case: ";
  tk.isMinimumSet(adj, d_set);

  return 0;
}