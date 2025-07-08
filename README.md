# Optimal Algorithm- Minimal Connected Dominating Set in Split Graphs

This repository is dedicated to testing and developing algorithms for finding a minimal dominating set(MCDS) in a random graph. Currently, the algorithm is designed for **small, undirected, and unweighted graphs** and is not yet optimized for performance.

Through this Orginal Algorithm we were able to devise a polynomial-time O(V+E) algorithm for the NP-Complete Problem of finding a Minimal Connnected Dominating Set in Split Graphs

👉[Check out the Algorithm Report](https://drive.google.com/file/d/1Zq58jHW5a0obCcVvh65G6b6pctpDcfeS/view?usp=drive_link)

## Minimal Connected Dominating Set Overview
![](https://github.com/Bilmis/Smart-Network-CDS-Algorithm/blob/main/images/MCDS.png)

## Split Graphs
![](https://github.com/Bilmis/Smart-Network-CDS-Algorithm/blob/main/images/input_graph.jpg)

## Algorithm
![](https://github.com/Bilmis/Smart-Network-CDS-Algorithm/blob/main/images/Algorithm2.png)

## Complexity Comparison
Complexity of the devised algorithm: O(N^2)

Complexity of the existing algorithm: O(1.308^N)

![](https://github.com/Bilmis/Smart-Network-CDS-Algorithm/blob/main/images/comparison_graph.png)

## Result Analysis
Split graph with 80 nodes

![Split graph with 80 nodes](https://github.com/Bilmis/Smart-Network-CDS-Algorithm/blob/main/images/80nodes.png)


Split graph with 100 nodes

![Split graph with 100 nodes](https://github.com/Bilmis/Smart-Network-CDS-Algorithm/blob/main/images/100nodes.png)



## How to Run


### 1️⃣ Prepare the Input Graph

There are **two ways** to provide the adjacency list for the graph:

#### **Option 1: Manually Edit `adj_list.txt`**

1. Open `adj_list.txt` and follow this format:
   - **First line**: Number of vertices.
   - **Following lines**: Adjacency list for each vertex.

#### **Option 2: Auto-Generate Using Python Scripts**

Alternatively, you can generate a random graph using the provided Python scripts in the `GraphGenerators` folder:

- **For Split Graphs** → Run `split.py`
- **For Undirected Graphs** → Run `undirected.py`

**Steps:**

1. Set the `MIN_VERTICES` and `MAX_VERTICES` constants in the respective Python script.
2. Run the script.
3. It will automatically generate `adj_list.txt` with a viable graph.

---

### 2️⃣ Compile and Run the Program

Once `adj_list.txt` is ready:

1. **Compile** the program:
   ```sh
   g++ main.cpp -o main
   ```
2. **Run** the compiled executable:
   ```sh
   ./main
   ```

The console will display a valid (and potentially minimal) dominating set for the given graph.

---

## 🔧 Project Structure

```
GraphDominatingSet/
│── GraphGenerators/    # Folder containing Python scripts for generating graphs
│   ├── split.py        # Generates split graphs
│   ├── undirected.py   # Generates random undirected graphs
│── adj_list.txt        # Adjacency list input file
│── main.cpp            # Main program file
│── solution.cpp        # Initial algorithm (scrapped version)
│── solution2.cpp       # Optimized version of the algorithm
│── test-kit.cpp        # Helper functions for testing
│── compare-kit.cpp     # Additional comparison functions
│── README.md           # This file
```

---

## ⚠️ Notes

- The algorithm works best for **small graphs** (e.g., up to 35 vertices).
- The dominating set found **may not always be minimal**.
- Further optimizations and enhancements are planned.

---

## 🚀 Future Improvements

- Improve performance for larger graphs.
- Implement optimized heuristics for finding minimal dominating sets.
- Extend functionality to weighted and directed graphs.

📢 **Feedback and contributions are welcome!** 🎉
