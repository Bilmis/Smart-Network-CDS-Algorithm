#include <vector>
#pragma once

using namespace std;

class TestKit {

  int row;
  bool status;
  vector<vector<int>> adj;

  void generateSubsets(vector<int>& subset, int start, int v, int n) {
    if (subset.size() == n) {
        
        if(isDominating(subset)) 
        status = false;

        return;
    }

    if(!status) return;

    for (int i = start; i < v; i++) {
        subset.push_back(i);
        generateSubsets(subset, i + 1, v, n);
        subset.pop_back(); // Backtrack
    }
  }

  bool isDominating(const vector<int>& vertex_set) {
    int n = adj.size();
    vector<bool> dominated(n, false);

    for (int v : vertex_set) {
        dominated[v] = true;
        for (int neighbor : adj[v]) {
            dominated[neighbor] = true;
        }
    }

    for (bool v_status : dominated) {
        if (!v_status) return false;
    }
    return true;
  }

  int isMinimum(const vector<int>& vertex_set) {
    
    if(adj.size() > 25) {
      return -1;
    }  
    
    vector<int> subset;
      status = true;
      generateSubsets(subset,0,adj.size(),vertex_set.size()-1);
      return status ? 1 : 0;
  }

  int isMinimal(const vector<int>& vertex_set) {
    
    int v = vertex_set.size();
    for (int i = 0; i < v; i++) {
        vector<int> temp_set = vertex_set;
        temp_set.erase(temp_set.begin() + i); 

        if (isDominating(temp_set)) {          
          return vertex_set[i]; 
        }

    }

    return -1;
  }

public:

  TestKit(vector<vector<int>> &adj_list) {
    if(adj_list.size() == 0) cout<<"Error in testkit. Invalid graph\n";
    adj = vector<vector<int>>(adj_list);
    row = 0;

  }
  
  bool isDominatingSet(const vector<int>& vertex_set) {

    cout<<"Domination test: ";
    bool res = isDominating(vertex_set);
    cout<<(res ? "valid":"invalid")<<endl;

    return res;
  }

  bool isMinimumSet(const vector<int>& vertex_set) {
    cout<<"Minimum test: ";
    int res = isMinimum(vertex_set);

    if(res == -1) cout<<"Unfinished. Set too large\n";
    if(res == 0) cout<<"Found smaller set\n";
    if(res == 1) cout<<"Is minimum set\n";

    return res==1;
  }

  bool isMinimalSet(const vector<int>& vertex_set) {
    cout<<"Minimal test: ";
    int res = isMinimal(vertex_set);
    
    if(res == -1) cout<<"Set is minimal\n";
    else cout<<"Not minimal. Remove (" << res << ")\n";

    return res==-1;
  }

  void summarize(const vector<int>& set, vector<int>& res) {
    res.resize(3);

    res[0] = (isDominating(set));
    res[1] = (isMinimal(set) == -1);
    res[2] = (isMinimum(set));

  }

};
