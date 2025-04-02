#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>

#include "solution2.cpp"
#include "compare-kit.cpp"
#include "class_mcds.cpp"

#define LOOP 100

using namespace std;

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



void printRow(vector<int> &set, string name, int min_val) {
  cout<<name<<"\t"<<set.size()<<"\t"<< 1.0*min_val/set.size()<<"\n";
}

void printDetails(vector<vector<int>> &results) {
  int min_size = results[0].size();
  cout<<"Exact min set size: "<< min_size <<"\n";
  cout<<"Algo\tSize\tRatio\n";

  printRow(results[1], "res", min_size);
  printRow(results[2], "mdg", min_size);
  printRow(results[3], "mdf", min_size);
  printRow(results[4], "wd", min_size);
  printRow(results[5], "rg", min_size);
  printRow(results[6], "mrd", min_size);
  printRow(results[7], "ld", min_size);
}

void PrintSet(vector<int> &set, string name = "d-set") {
  // cout<<"\nSize of "<<name<<": "<<set.size()<<endl;
  if(set.size() > 50) return;

  cout<<"\nVertices in "<<name<<":\n";
  for(int x: set) cout<<x<<" ";
  cout<<"\n";
}

void saveStats(vector<vector<int>> &results, vector<double> &stats) {
  int min_val = results[0].size();

  for(int i=0; i<stats.size(); i++) {
    stats[i] += 1.0*min_val/results[i+1].size();
  }
}

void viewStats(vector<double> &stats) {
  cout<<"\nNumber of iterations: "<<LOOP<<endl;
  cout<<"Algorithm:\tres\tmdg\tmdf\twd\trg\tmrd\tld\n";
  cout<<"avg-ratio:\t";
  for(double stat:stats) cout<< setprecision(3) <<stat/LOOP<<"\t";
  cout<<endl;
}

int main()
{

  vector<double> stats(7);

  for(int i=0; i<LOOP; i++) {

    int result = system("python GraphGenerators\\split.py false"); // Execute Python script
    if (result != 0)
    {
      cerr << "Error executing Python script\n";
    }

    vector<vector<int>> adj;
    inputGraphFile(adj);
    
    cout<<"Loop "<<i+1<<", graph size = "<<adj.size()<<endl;

    vector<int> d_set;
    Solution2 sol;
    CompareKit ck(adj);
    Exact ex(adj);

    set<int> bestSet=ex.D;  
    //for (int i = 0; i < adj.size(); i++) bestSet.insert(i);  
    set<int> currentSet;
    //ex.enumerateMCDS(adj, currentSet, bestSet, 0);

    vector<int> exact(bestSet.begin(), bestSet.end());
    vector<vector<int>> results;

    results.push_back(exact);
    results.push_back(sol.dominatingSet(adj));
    results.push_back(ck.maxDegreeGreedy());
    results.push_back(ck.minDegreeFirst());
    results.push_back(ck.weightedDegree());
    results.push_back(ck.randomGreedy());
    results.push_back(ck.minResidualDegree());
    results.push_back(ck.lookaheadDegree());

    saveStats(results, stats);

    if(LOOP > 10) continue;

    printDetails(results);
    PrintSet(exact, "exact-min-set");
    PrintSet(results[1], "res-set");
    cout<<"\n\n";
  }

  viewStats(stats);

  return 0;
}