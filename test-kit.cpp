#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class TestKit {

  bool status;

  void generateSubsets(vector<int>& subset, int start, int v, int n, const vector<vector<int>>& adj_list) {
    if (subset.size() == n) {
        
        if(isDominating(adj_list, subset)) 
        status = false;

        return;
    }

    if(!status) return;

    for (int i = start; i < v; i++) {
        subset.push_back(i);
        generateSubsets(subset, i + 1, v, n, adj_list);
        subset.pop_back(); // Backtrack
    }
  }

  bool isDominating(const vector<vector<int>>& adj_list, const vector<int>& vertex_set) {
    int n = adj_list.size();
    vector<bool> dominated(n, false);

    for (int v : vertex_set) {
        dominated[v] = true;
        for (int neighbor : adj_list[v]) {
            dominated[neighbor] = true;
        }
    }

    for (bool v_status : dominated) {
        if (!v_status) return false;
    }
    return true;
}

public:
  
  bool isDominatingSet(const vector<vector<int>>& adj_list, const vector<int>& vertex_set) {

    cout<<"Domination test: ";
    bool res = isDominating(adj_list, vertex_set);
    cout<<(res ? "valid":"invalid")<<endl;

    return res;
  }

  bool isMinimumSet(const vector<vector<int>>& adj_list, const vector<int>& vertex_set) {
    
    cout<<"Mininum set test: ";
    if(adj_list.size() > 25) {
      cout<<"File too large\n";
      return true;
    }  
    
    vector<int> subset;
      status = true;
      generateSubsets(subset,0,adj_list.size(),vertex_set.size()-1, adj_list);

      cout<<(status ? "It is minimum" : "It is not min")<<endl;
      return status;
  }

  bool isMinimalSet(const vector<vector<int>> &adj_list, const vector<int>& vertex_set) {
    
    cout<<"Minimality test: ";
    int v = vertex_set.size();

    for (int i = 0; i < v; i++) {
        vector<int> temp_set = vertex_set;
        temp_set.erase(temp_set.begin() + i); // Remove one element

        if (isDominating(adj_list, temp_set)) {
          cout<<" Found smaller set, remove {"<<vertex_set[i]<<"}\n";
          
          return false; // Not minimal since a smaller set still dominates
        }

    }
    cout<<"Minimality verified\n";
    return true; // If no subset dominates, it's minimal
  }
};
