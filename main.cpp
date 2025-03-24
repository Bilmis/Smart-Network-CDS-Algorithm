#include<bits/stdc++.h>
#include "solution.cpp"
#include "test-kit.cpp"
#include "solution2.cpp"
#include "compare-kit.cpp"

vector<int> set2;
//, set3;
vector<int> mdg, mdf, wd, rg, mrd, ld;

// Function to take graph input from the user
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

// Function to validate if the input graph is undirected, with no self-loops or parallel edges
bool isValid(vector<vector<int>> &adj) {
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
        cout <<adj_node << " " << i << endl;
        return false;
      }
    }
  }

  return true; 
}

// Function to read the adjacency list from file "adj_list.txt"
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

// Function to print the adjacency list representation of the graph
void printGraph(const vector<vector<int>> &adj) {
    cout << "\nAdjacency List:\n";
    for (size_t i = 0; i < adj.size(); i++) { 
        cout << "Vertex " << i << " -> ";
        for (int x : adj[i]) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

// Function to print evaluation results in tabular form
void printRow(TestKit &tk, vector<int>& set, string name) {
  vector<int> summary;
  tk.summarize(set, summary);

  cout<<name<<"\t "<<set.size()<<"\t "<<summary[0]<<"\t "<<summary[1]<<"\t "<<summary[2]<<endl;
}

// Function to compare different dominating set algorithms
void compareSets(TestKit &tk) {
  cout<<"Algo\t Order\t Dom\t MinL\t Min\n";
  printRow(tk, set2, "set");
  //printRow(tk, set3, "set3");
  printRow(tk, mdg, "mdg");
  printRow(tk, mdf, "mdf");
  printRow(tk, wd, "wd");
  printRow(tk, rg, "rg");
  printRow(tk, mrd, "mrd");
  printRow(tk, ld, "ld");
  cout<<endl;
}

// Function to print a given set
void printSet(vector<int>& set) {
  cout<<"Order = "<<set.size()<<endl;
  for(int x: set) cout<< x << " ";
  cout<<endl;
}

int main() {
  vector<vector<int>> adj;

  // Read the graph from file and validate it
  inputGraphFile(adj);
  if(!isValid(adj)) return 1;
  cout<<"Graph verified. Size = "<<adj.size()<<endl;

  // Initialize testing and comparison kits
  TestKit tk(adj);
  CompareKit ck(adj);
  Solution2 sol2;

  // Compute dominating sets using different approaches
  set2 = sol2.dominatingSet(adj);
  //set3 = tk.minimalise(set2);
  mdg = ck.maxDegreeGreedy();
  mdf = ck.minDegreeFirst();
  wd = ck.weightedDegree();
  rg = ck.randomGreedy();
  mrd = ck.minResidualDegree();
  ld = ck.lookaheadDegree();

  // Compare results
  compareSets(tk);

  // Print the results if the set is within a reasonable size
  if(set2.size() > 0 && set2.size() < 100){
    cout<<"MCDS: ";
    printSet(set2);
  }
  
  return 0;
}
