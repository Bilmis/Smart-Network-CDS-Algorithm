import random
import networkx as nx
import sys

# Define the range for the number of vertices
MIN_VERTICES = 30  # Lower bound
MAX_VERTICES = 45  # Upper bound

def is_valid_range(a, b):
    """Checks if a and b define a valid range where b > a and both are positive integers."""
    return isinstance(a, int) and isinstance(b, int) and a > 0 and b > 0 and b > a

def generate_random_split_graph(num_vertices):
    """Generates a random split graph with the given number of vertices."""
    if num_vertices < 2:
        raise ValueError("A split graph must have at least 2 vertices.")
    
    # Randomly determine the size of the clique
    clique_size = random.randint(1, num_vertices - 1)
    independent_size = num_vertices - clique_size

    G = nx.Graph()
    
    # Add clique nodes and connect all of them
    clique_nodes = list(range(clique_size))
    G.add_nodes_from(clique_nodes)
    
    for i in range(clique_size):
        for j in range(i + 1, clique_size):
            G.add_edge(i, j)

    # Add independent set nodes
    independent_nodes = list(range(clique_size, num_vertices))
    G.add_nodes_from(independent_nodes)

    # Connect each independent node to at least one clique node
    for node in independent_nodes:
        num_edges = random.randint(1, clique_size)
        connected_nodes = random.sample(clique_nodes, num_edges)
        for neighbor in connected_nodes:
            G.add_edge(neighbor, node)

    return G

def save_graph_as_adjacency_list(G, filename="adj_list.txt"):
    """Saves the graph's adjacency list representation to a file."""
    with open(filename, "w") as f:
        f.write(f"// Number of vertices\n{len(G.nodes())}\n")
        f.write("// Adjacency list\n")
        for node in G.nodes():
            neighbors = " ".join(map(str, G.neighbors(node)))
            f.write(f"{neighbors}\n")

if __name__ == "__main__":
    # Validate range before proceeding
    if not is_valid_range(MIN_VERTICES, MAX_VERTICES):
        print("Error: Invalid vertex range. Ensure MIN_VERTICES < MAX_VERTICES and both are positive integers.")
        exit()

    # Randomly select the number of vertices within the given range
    num_vertices = random.randint(MIN_VERTICES, MAX_VERTICES)

    # Generate a split graph and save it
    split_graph = generate_random_split_graph(num_vertices)
    save_graph_as_adjacency_list(split_graph)

    if len(sys.argv) < 2:
        print(f"Generated a split graph with {num_vertices} vertices and saved it to 'adj_list.txt'.")
