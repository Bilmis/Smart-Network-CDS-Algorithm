import random
import networkx as nx

def generate_split_graph(x):
    if x < 2:
        raise ValueError("A split graph must have at least 2 vertices.")
    
    # Randomly determine the size of the clique
    clique_size = random.randint(1, x - 1)
    independent_size = x - clique_size
    
    # Create the graph
    G = nx.Graph()
    
    # Add clique vertices
    clique_nodes = list(range(clique_size))
    G.add_nodes_from(clique_nodes)
    
    # Connect every pair of clique nodes
    for i in range(clique_size):
        for j in range(i + 1, clique_size):
            G.add_edge(i, j)
    
    # Add independent set vertices
    independent_nodes = list(range(clique_size, x))
    G.add_nodes_from(independent_nodes)
    
    # Add random edges between clique and independent set
    for v in independent_nodes:
        num_edges = random.randint(1, clique_size)  # Connect to at least one clique node
        connected_nodes = random.sample(clique_nodes, num_edges)
        for u in connected_nodes:
            G.add_edge(u, v)
    
    return G

def save_adjacency_list(G, filename="adj_list.txt"):
    with open(filename, "w") as f:
        f.write(f"//No of vertices\n{x}\n")
        f.write("// Adj list\n")
        for node in G.nodes():
            neighbors = " ".join(map(str, G.neighbors(node)))
            f.write(f"{neighbors}\n")

if __name__ == "__main__":
    x = random.randint(10,35)
    split_graph = generate_split_graph(x)
    save_adjacency_list(split_graph)
