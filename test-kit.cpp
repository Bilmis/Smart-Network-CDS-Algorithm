/* 
   TestKit: A utility class to verify the properties of a given vertex set in a graph.
   It checks whether a set is a Dominating Set, Minimal Dominating Set, or a Minimum Dominating Set.
   It also provides functions to summarize set properties and minimalize a non-minimal set.
*/


#include <vector>
#include<iostream>
#pragma once

using namespace std;

class TestKit {

  int row;                 // Internal variable (unused)
  bool status;             // Status flag used in subset generation for minimum set check
  vector<vector<int>> adj; // Adjacency list representation of the graph

  // Recursive function to generate all subsets of size 'n' from 'v' vertices
  void generateSubsets(vector<int>& subset, int start, int v, int n) {
    if (subset.size() == n) {
        // If a smaller dominating set is found, mark status as false
        if (isDominating(subset)) 
            status = false;
        return;
    }

    if (!status) return; // Stop recursion if a smaller set is already found

    for (int i = start; i < v; i++) {
        subset.push_back(i);
        generateSubsets(subset, i + 1, v, n);
        subset.pop_back(); // Backtrack
    }
  }

  // Checks if a given vertex set is a Dominating Set
  bool isDominating(const vector<int>& vertex_set) {
    int n = adj.size();
    vector<bool> dominated(n, false);

    // Mark the given set and its neighbors as dominated
    for (int v : vertex_set) {
        dominated[v] = true;
        for (int neighbor : adj[v]) {
            dominated[neighbor] = true;
        }
    }

    // If any node remains undominated, return false
    for (bool v_status : dominated) {
        if (!v_status) return false;
    }
    return true;
  }

  // Checks if a given set is a Minimum Dominating Set (only if graph size ≤ 35)
  int isMinimum(const vector<int>& vertex_set) {
    if (adj.size() > 35) {
        return -1; // Too large to compute exhaustively
    }  
    
    vector<int> subset;
    status = true;
    generateSubsets(subset, 0, adj.size(), vertex_set.size() - 1);
    return status ? 1 : 0; // 1 if minimum, 0 if a smaller set exists
  }

  // Checks if the given set is Minimal (removing any single vertex makes it non-dominating)
  int isMinimal(const vector<int>& vertex_set) {
    int v = vertex_set.size();
    for (int i = 0; i < v; i++) {
        vector<int> temp_set = vertex_set;
        temp_set.erase(temp_set.begin() + i); 

        if (isDominating(temp_set)) {          
            return vertex_set[i]; // Return the removable vertex
        }
    }
    return -1; // The set is minimal
  }

public:

  // Constructor: Initializes the adjacency list and verifies the graph validity
  TestKit(vector<vector<int>> &adj_list) {
    if (adj_list.size() == 0) cout << "Error in TestKit: Invalid graph\n";
    adj = vector<vector<int>>(adj_list);
    row = 0;
  }
  
  // Checks if the given set is a Dominating Set
  bool isDominatingSet(const vector<int>& vertex_set) {
    cout << "Domination test: ";
    bool res = isDominating(vertex_set);
    cout << (res ? "valid" : "invalid") << endl;
    return res;
  }

  // Checks if the given set is a Minimum Dominating Set
  bool isMinimumSet(const vector<int>& vertex_set) {
    cout << "Minimum test: ";
    int res = isMinimum(vertex_set);

    if (res == -1) cout << "Unfinished. Set too large\n";
    if (res == 0) cout << "Found smaller set\n";
    if (res == 1) cout << "Is minimum set\n";

    return res == 1;
  }

  // Checks if the given set is a Minimal Dominating Set
  bool isMinimalSet(const vector<int>& vertex_set) {
    cout << "Minimal test: ";
    int res = isMinimal(vertex_set);
    
    if (res == -1) cout << "Set is minimal\n";
    else cout << "Not minimal. Remove (" << res << ")\n";

    return res == -1;
  }

  // Provides a summary of the given set's properties (Domination, Minimality, Minimum)
  void summarize(const vector<int>& set, vector<int>& res) {
    res.resize(3);
    res[0] = (isDominating(set)); 
    res[1] = (isMinimal(set) == -1); 
    res[2] = (isMinimum(set));      
  }

  // Attempts to reduce the given set to a Minimal Dominating Set by removing unnecessary vertices
  vector<int> minimalise(const vector<int>& set) {
    vector<int> res(set.begin(), set.end());
    int removable = isMinimal(res);
    
    while (removable != -1) {
        res.erase(remove(res.begin(), res.end(), removable), res.end());
        removable = isMinimal(res);
    }

    return res;
  }
};
