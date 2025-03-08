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

bool isValid(vector<vector<int>> &adj) {
  // Test if graph given is undirected and contains no self loop or parallel edge
  int v = adj.size();
  vector<unordered_set<int>> map(v);

  for(int i=0; i<v; i++) {
    for(int adj_node: adj[i]) {

      if(i == adj_node) {
        cout<<"Self Loop found at "<<i<<"\n";
        return false;
      }

      if(map[i].find(adj_node) != map[i].end()) {
        cout<<"Parallel Edge found \n";
        return false;
      }

      map[i].insert(adj_node);
    }
  }

  for(int i=0; i<v; i++) {
    for(int adj_node: map[i]) {
      if(map[adj_node].find(i) == map[adj_node].end()) {
        cout<<"Directed edge found\n";
        return false;
      }
    }
  }

  return true; 
}

bool inputGraphFile(vector<vector<int>> &adj) {
  string filename = "adj_list.txt";
  ifstream ifs(filename);

  if(!ifs.is_open()) {
    cout<<"Error";
    return false;
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

  return true;
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
  cout<<"Algo\t Order\t Dom\t MinL\t Min\n";

  printRow(tk, set2, "set2");
  printRow(tk, mdg, "mdg");
  printRow(tk, mdf, "mdf");
  printRow(tk, wd, "wd");
  printRow(tk, rg, "rg");
  printRow(tk, mrd, "mrd");
  printRow(tk, ld, "ld");

  cout<<endl;
}

void printSet(vector<int>& set) {
  cout<<"Order = "<<set.size()<<endl;
  for(int x: set) cout<< x << " ";
  cout<<endl;
}

int main() {
  vector<vector<int>> adj;
  inputGraphFile(adj);
  if(!isValid(adj)) return 1;
  cout<<"Graph verified. Size = "<<adj.size()<<endl;


  TestKit tk(adj);
  CompareKit ck(adj);

  Solution2 sol2;

  set2 = sol2.dominatingSet(adj);

  mdg = ck.maxDegreeGreedy();
  mdf = ck.minDegreeFirst();
  wd = ck.weightedDegree();
  rg = ck.randomGreedy();
  mrd = ck.minResidualDegree();
  ld = ck.lookaheadDegree();

  compareSets(tk);

  if(set2.size() < 100){
    cout<<"Set 2: ";
    printSet(set2);
  }
  
  return 0;
}


// for(int i=0; i<v; i++) {
//   vector<int> temp(adj[i].begin(), adj[i].end());
//   sort(temp.begin(), temp.end());

//   if(binary_search(temp.begin(), temp.end(), i)) {
//     cout<<"Contains self loop. Exit\n";
//     return false;
//   }

//   for(int j=0; j<temp.size(); j++) {
//     if(j > 0 && temp[j-1] == temp[j]) {
//       cout<<"Contains parallel edges. Exit\n";
//       return false;
//     }

//     int node = temp[j];
//     if(count(adj[node].begin(), adj[node].end(), i) == 0) {
//       cout<<"Directed graph. No"<<node<<" -> "<<i<<". Exit\n";
//       return false;
//     }
//   }