import random

# Generate a random undirected graph with x+ vertices
num_vertices = random.randint(1000,1500)  # Randomly choosing between x and y vertices

# Create adjacency list representation
random_graph_adj_list = {i: set() for i in range(num_vertices)}

# Add random edges (ensuring no self-loops and no duplicate edges)
num_edges = random.randint(num_vertices * 2, num_vertices * 4)  # Controlling edge density

for _ in range(num_edges):
    u, v = random.sample(range(num_vertices), 2)  # Pick two distinct vertices
    random_graph_adj_list[u].add(v)
    random_graph_adj_list[v].add(u)  # Since the graph is undirected

# Convert sets to sorted lists for consistency
random_graph_adj_list = {k: sorted(list(v)) for k, v in random_graph_adj_list.items()}

# Format output similar to given format
output_str = f"// Number of vertices\n{num_vertices}\n//"
for node, neighbors in random_graph_adj_list.items():
    output_str += f"{node} {' '.join(map(str, neighbors))}\n"

# Display the adjacency list
output_str

# Remove vertex numbers from each line
file_path_no_vertex = "adj_list.txt"

# Process output to remove leading vertex numbers
lines = output_str.split("\n")
processed_lines = [line.split(" ", 1)[1] if " " in line else "" for line in lines[2:]]  # Skip first two comment lines

# Reconstruct output string
output_str_no_vertex = "// Number of vertices\n" + str(num_vertices) + "\n// Adj list\n" + "\n".join(processed_lines)

# Save to a new file
with open(file_path_no_vertex, "w") as file:
    file.write(output_str_no_vertex)

# Return file path for download
file_path_no_vertex
