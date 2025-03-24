import random

# Define the range for the number of vertices
MIN_VERTICES = 200  # Lower bound
MAX_VERTICES = 350  # Upper bound

def is_valid_range(a, b):
    """Checks if the given range is valid where b > a and both are positive integers."""
    return isinstance(a, int) and isinstance(b, int) and a > 0 and b > 0 and b > a

def generate_random_undirected_graph(num_vertices):
    """Generates a random undirected graph with a given number of vertices."""
    if num_vertices < 2:
        raise ValueError("An undirected graph must have at least 2 vertices.")

    # Initialize adjacency list
    adjacency_list = {i: set() for i in range(num_vertices)}

    # Define edge count range to control density
    min_edges = num_vertices * 2
    max_edges = num_vertices * 4
    num_edges = random.randint(min_edges, max_edges)

    # Add random edges while ensuring no self-loops or duplicate edges
    for _ in range(num_edges):
        u, v = random.sample(range(num_vertices), 2)  # Pick two distinct vertices
        adjacency_list[u].add(v)
        adjacency_list[v].add(u)  # Since the graph is undirected

    # Convert adjacency list from sets to sorted lists
    adjacency_list = {k: sorted(list(v)) for k, v in adjacency_list.items()}
    return adjacency_list

def save_graph_as_adjacency_list(adj_list, filename="adj_list.txt"):
    """Saves the graph's adjacency list representation to a file."""
    num_vertices = len(adj_list)

    with open(filename, "w") as f:
        f.write(f"// Number of vertices\n{num_vertices}\n")
        f.write("// Adjacency list\n")
        for node, neighbors in adj_list.items():
            f.write(f"{' '.join(map(str, neighbors))}\n")

if __name__ == "__main__":
    # Validate range before proceeding
    if not is_valid_range(MIN_VERTICES, MAX_VERTICES):
        print("Error: Invalid vertex range. Ensure MIN_VERTICES < MAX_VERTICES and both are positive integers.")
        exit()

    # Randomly select the number of vertices within the given range
    num_vertices = random.randint(MIN_VERTICES, MAX_VERTICES)

    # Generate the undirected graph and save it
    random_graph = generate_random_undirected_graph(num_vertices)
    save_graph_as_adjacency_list(random_graph)

    print(f"Generated a random undirected graph with {num_vertices} vertices and saved it to 'adj_list.txt'.")
