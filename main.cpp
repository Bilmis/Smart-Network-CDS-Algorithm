#include<bits/stdc++.h>
#include "solution.cpp"
#include "test-kit.cpp"


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
  // printGraph(adj);

  Solution sol;
  vector<int> d_set = sol.dominatingSet(adj);
  cout<<"\ndominating set: ";
  for(int d: d_set) cout<<d<<" ";
  cout<<" {"<<d_set.size()<<"}"<<endl;

  TestKit tk;
  tk.isDominatingSet(adj, d_set);
  tk.isMinimalSet(adj, d_set);
  tk.isMinimumSet(adj, d_set);

  return 0;
}