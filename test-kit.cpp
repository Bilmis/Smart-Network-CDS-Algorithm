#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class TestKit {

  bool status;

  void generateSubsets(vector<int>& subset, int start, int v, int n, const vector<vector<int>>& adj_list) {
    if (subset.size() == n) {

        for(int x: subset) cout<<x<<" ";
        
        if(isDominatingSet(adj_list, subset)) 
        status = false;

        cout<<(status ? "true" : "false")<<endl;
        return;
    }

    if(!status) return;

    for (int i = start; i < v; i++) {
        subset.push_back(i);
        generateSubsets(subset, i + 1, v, n, adj_list);
        subset.pop_back(); // Backtrack
    }
  }


public:
  bool isDominatingSet(const vector<vector<int>>& adj_list, const vector<int>& vertex_set) {
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

  bool isMinimumSet(const vector<vector<int>>& adj_list, const vector<int>& vertex_set) {
      vector<int> subset;
      status = true;
      generateSubsets(subset,0,adj_list.size(),vertex_set.size()-1, adj_list);

      return status;
  }

  bool isMinimalSet(const vector<vector<int>> &adj_list, const vector<int>& vertex_set) {
    int v = vertex_set.size();

    for (int i = 0; i < v; i++) {
        vector<int> temp_set = vertex_set;
        temp_set.erase(temp_set.begin() + i); // Remove one element

        for(int x: temp_set) cout<<x<<" ";

        if (isDominatingSet(adj_list, temp_set)) {
            cout<<"false"<<endl;
            return false; // Not minimal since a smaller set still dominates
        }

        cout<<"true"<<endl;
    }

    return true; // If no subset dominates, it's minimal
  }
};

// int main() {
//     vector<vector<int>> adj_list = {
//         {1, 2}, 
//         {0, 2, 3}, 
//         {0, 1, 3}, 
//         {1, 2} 
//     };

//     TestKit tk;
//     vector<int> vertex_set = {1, 3}; // Example dominating set

//     if (tk.isDominatingSet(vertex_set)) {
//         cout << "The given set is a dominating set." << endl;
//         if (tk.isMinimumSet(adj_list, vertex_set)) {
//             cout << "The set is the minimum dominating set." << endl;
//         } else {
//             cout << "The set is NOT the minimum dominating set." << endl;
//         }
//     } else {
//         cout << "The given set is NOT a dominating set." << endl;
//     }

//     return 0;
// }