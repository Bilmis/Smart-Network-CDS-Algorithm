/* 
   A utility class implementing multiple heuristic algorithms for finding Dominating Sets (DS) in a graph.
   Useful for performance comparison and benchmarking different approaches.
*/

#include <bits/stdc++.h>
#include "test-kit.cpp"
using namespace std;

class CompareKit {
    vector<vector<int>> adj;  // Adjacency list representation of the graph
    vector<bool> visited;     // Tracks visited (dominated) nodes
    vector<int> degree;       // Stores degree of each node

    // Resets the visited status of all nodes
    void reset() {
        fill(visited.begin(), visited.end(), false);
    }

    // Marks a node and its neighbors as visited (dominated)
    int visit(int node) {
        if (visited[node]) return 0;
        visited[node] = true;
        for (int neighbor : adj[node]) 
            visited[neighbor] = true;
        return 1;
    }

public:

    // Constructor: Initializes the adjacency list and computes node degrees
    CompareKit(vector<vector<int>>& graph) {
        adj = graph;
        int n = adj.size();
        visited.assign(n, false);
        degree.resize(n);
        for (int i = 0; i < n; i++)
            degree[i] = adj[i].size();
    }

    // Greedy algorithm: Selects nodes with the highest degree first
    vector<int> maxDegreeGreedy() {
        reset();
        vector<int> domSet;
        set<pair<int, int>, greater<>> pq; // (degree, node)

        for (int i = 0; i < adj.size(); i++)
            pq.insert({degree[i], i});

        while (!pq.empty()) {
            int node = pq.begin()->second;
            pq.erase(pq.begin());
            if (visited[node]) continue;
            domSet.push_back(node);
            visit(node);
        }

        return domSet;
    }

    // Greedy algorithm: Selects nodes with the lowest degree first
    vector<int> minDegreeFirst() {
        reset();
        vector<int> domSet;
        set<pair<int, int>> pq; // (degree, node)

        for (int i = 0; i < adj.size(); i++)
            pq.insert({degree[i], i});

        while (!pq.empty()) {
            int node = pq.begin()->second;
            pq.erase(pq.begin());
            if (visited[node]) continue;
            domSet.push_back(node);
            visit(node);
        }

        return domSet;
    }

    // Greedy algorithm: Selects nodes based on weighted degree (sum of neighbors' degrees)
    vector<int> weightedDegree() {
        reset();
        vector<int> domSet;
        vector<int> weightedDeg(adj.size());

        for (int i = 0; i < adj.size(); i++)
            for (int neighbor : adj[i])
                weightedDeg[i] += degree[neighbor];

        set<pair<int, int>, greater<>> pq; // (weighted degree, node)
        for (int i = 0; i < adj.size(); i++)
            pq.insert({weightedDeg[i], i});

        while (!pq.empty()) {
            int node = pq.begin()->second;
            pq.erase(pq.begin());
            if (visited[node]) continue;
            domSet.push_back(node);
            visit(node);
        }

        return domSet;
    }

    // Greedy algorithm: Randomized selection of nodes
    vector<int> randomGreedy() {
        reset();
        vector<int> domSet;
        vector<int> nodes(adj.size());
        iota(nodes.begin(), nodes.end(), 0);
        random_shuffle(nodes.begin(), nodes.end());

        for (int node : nodes) {
            if (!visited[node]) {
                domSet.push_back(node);
                visit(node);
            }
        }

        return domSet;
    }

    // Greedy algorithm: Selects nodes with the smallest residual degree
    vector<int> minResidualDegree() {
        reset();
        vector<int> domSet;
        vector<int> residualDeg = degree;

        while (true) {
            int minNode = -1, minVal = INT_MAX;
            for (int i = 0; i < adj.size(); i++) {
                if (!visited[i] && residualDeg[i] < minVal) {
                    minVal = residualDeg[i];
                    minNode = i;
                }
            }
            if (minNode == -1) break;
            domSet.push_back(minNode);
            visit(minNode);
        }

        return domSet;
    }

    // Lookahead greedy algorithm: Selects nodes based on maximum coverage of unvisited nodes
    vector<int> lookaheadDegree() {
        reset();
        vector<int> domSet;

        while (true) {
            int bestNode = -1, maxCoverage = -1;
            for (int i = 0; i < adj.size(); i++) {
                if (visited[i]) continue;
                int coverage = 0;
                for (int neighbor : adj[i])
                    if (!visited[neighbor]) coverage++;

                if (coverage > maxCoverage) {
                    maxCoverage = coverage;
                    bestNode = i;
                }
            }
            if (bestNode == -1) break;
            domSet.push_back(bestNode);
            visit(bestNode);
        }

        return domSet;
    }
};

/* ============================== */
/*      IGNORE BELOW CODE         */
/* ============================== */

// Function to generate a random graph with given probability
// vector<vector<int>> generateRandomGraph(int n, double prob) {
//     vector<vector<int>> graph(n);
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_real_distribution<> dis(0, 1);

//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             if (dis(gen) < prob) {
//                 graph[i].push_back(j);
//                 graph[j].push_back(i);
//             }
//         }
//     }
//     return graph;
// }

// Function to run all heuristics and compare performance
// int RunAll() {
//     vector<int> mdg = maxDegreeGreedy();
//     vector<int> mdf = minDegreeFirst();
//     vector<int> wd = weightedDegree();
//     vector<int> rg = randomGreedy();
//     vector<int> mrd = minResidualDegree();
//     vector<int> ld = lookaheadDegree();

//     TestKit tk(adj);

//     cout << "Max Degree Greedy: " << mdg.size() << "\t";
//     tk.isDominatingSet(mdg);

//     cout << "Min Degree First: " << mdf.size() << "\t";
//     tk.isDominatingSet(mdf);

//     cout << "Weighted Degree: " << wd.size() << "\t";
//     tk.isDominatingSet(wd);

//     cout << "Random Greedy: " << rg.size() << "\t";
//     tk.isDominatingSet(rg);

//     cout << "Min Residual Degree: " << mrd.size() << "\t";
//     tk.isDominatingSet(mrd);

//     cout << "Lookahead Degree: " << ld.size() << "\t";
//     tk.isDominatingSet(ld);

//     return 0;
// }
