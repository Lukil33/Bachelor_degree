from hypergraphx import TemporalHypergraph, Hypergraph

### This is the function that computes with the use of a heuristic the hitting set of nodes that covers all the edges in the starting hypergraph, it takes as input the temporal hypergraph and the temporal window size, and returns the hitting set of nodes that covers all the edges in the hypergraph.
def greedy_euristic_hitting_set_construction(temporal_hypergraph: TemporalHypergraph, window_size: int) -> set:
    dictionary: dict[int, Hypergraph] = temporal_hypergraph.subhypergraph(time_window = tuple([temporal_hypergraph.min_time(), temporal_hypergraph.min_time() + window_size]))
    H = Hypergraph()
    nodes = set()

    for time in dictionary: # I construct the starting hypergraph by adding all the edges in the temporal window to the hypergraph H
        H.add_edges(dictionary[time].get_edges())
        for edges in dictionary[time].get_edges(): # This operation id crappy, i hate it and in my opinion it does not make any sense
            for node in edges:
                nodes.add(node)

    print(f"Debug: Starting Hypergraph calculated correctly.")
    print(f"Debug: Hitting set construction started.")

    hitting_set = greedy_euristic_hitting_set(H, nodes)

    print(f"Debug: Hitting set construction completed.")
    print(f"Debug: Hitting set size: {len(hitting_set)}\n")

    return hitting_set

### This function return the ID of the node with the maximum degree in the hypergraph given a set of nodes: O(num_of_nodes)
def max_degree_node(hypergraph: Hypergraph, nodes: set) -> int:
    max = 0
    max_node = -1

    for node in nodes:
        if hypergraph.degree(node) > max:
            max = hypergraph.degree(node)
            max_node = node
    
    return  max_node

### This function return the hitting set of the given hypergraph: O(num_of_nodes * log(num_of_nodes))
def greedy_euristic_hitting_set(hypergraph: Hypergraph, nodes: set) -> set:
    hitting_set = set()

    max_node = max_degree_node(hypergraph, nodes)
    while max_node != -1 and hypergraph.degree(max_node) > 0:
        hypergraph.remove_node(max_node, keep_edges = False)
        nodes.remove(max_node)
        hitting_set.add(max_node)
        max_node = max_degree_node(hypergraph, nodes)

    return hitting_set