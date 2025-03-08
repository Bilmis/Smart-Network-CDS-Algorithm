#include<bits/stdc++.h>
#include "solution.cpp"
#include "test-kit.cpp"
#include "solution2.cpp"
#include "compare-kit.cpp"

vector<int> set1, set2;
vector<int> mdg, mdf, wd, rg, mrd, ld;

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
        cout << "\n";
    }
}

void printRow(TestKit &tk, vector<int>& set, string name) {
  vector<int> summary;
  tk.summarize(set, summary);

  cout<<name<<"\t "<<set.size()<<"\t "<<summary[0]<<"\t "<<summary[1]<<"\t "<<summary[2]<<endl;
}

void compareSets(TestKit &tk) {
  cout<<"Algo\t order\t dom\t minl\t min\n";

  printRow(tk, set1, "set1");
  printRow(tk, set2, "set2");
  printRow(tk, mdg, "mdg");
  printRow(tk, mdf, "mdf");
  printRow(tk, wd, "wd");
  printRow(tk, rg, "rg");
  printRow(tk, mrd, "mrd");
  printRow(tk, ld, "ld");

  cout<<endl;
}

int main() {
  vector<vector<int>> adj;
  inputGraphFile(adj);

  TestKit tk(adj);
  CompareKit ck(adj);

  Solution sol;
  Solution2 sol2;

  set1 = sol.dominatingSet(adj);
  set2 = sol2.dominatingSet(adj);

  mdg = ck.maxDegreeGreedy();
  mdf = ck.minDegreeFirst();
  wd = ck.weightedDegree();
  rg = ck.randomGreedy();
  mrd = ck.minResidualDegree();
  ld = ck.lookaheadDegree();

  compareSets(tk);

  // printGraph(adj);

  // Solution sol;
  // vector<int> d_set = sol.dominatingSet(adj);
  // cout<<"\nDominating set: ";
  // if(d_set.size() < 25) for(int d: d_set) cout<<d<<" ";
  // cout<<" {"<<d_set.size()<<"}"<<endl;

  // tk.isDominatingSet(d_set);
  // tk.isMinimalSet(d_set);
  // tk.isMinimumSet(d_set);

  // cout<<"\n------------set 2-------------\n";


  // Solution2 sol2;
  // vector<int> d_set2 = sol2.dominatingSet(adj);
  // cout<<"\nDominating set: ";
  // if(d_set2.size() < 15) for(int d: d_set2) cout<<d<<" ";
  // cout<<" {"<<d_set2.size()<<"}"<<endl;

  // tk.isDominatingSet(d_set2);
  // tk.isMinimalSet(d_set2);
  // tk.isMinimumSet(d_set2);

  // cout<<"\n------------set 3-------------\n";

  // cout<<endl;
  // CompareKit(adj).Run();
  // cout<<endl;

  return 0;
}