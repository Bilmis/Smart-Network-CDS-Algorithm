# Graph Dominating Set

This repository is dedicated to testing and developing algorithms for finding a minimal dominating set in a random graph. Currently, the algorithm is designed for **small, undirected, and unweighted graphs** and is not yet optimized for performance.

## 📌 How to Use

### 1️⃣ Prepare the Input Graph

There are **two ways** to provide the adjacency list for the graph:

#### **Option 1: Manually Edit `adj_list.txt`**

1. Open `adj_list.txt` and follow this format:
   - **First line**: Number of vertices.
   - **Following lines**: Adjacency list for each vertex.

#### **Option 2: Auto-Generate Using Python Scripts**

Alternatively, you can generate a random graph using the provided Python scripts in the `GenerateGraph` folder:

- **For Split Graphs** → Run `split.py`
- **For Random Undirected Graphs** → Run `undirected.py`

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
│── GenerateGraph/      # Folder containing Python scripts for generating graphs
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
