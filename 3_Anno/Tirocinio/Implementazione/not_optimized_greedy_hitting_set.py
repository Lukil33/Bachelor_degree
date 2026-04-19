from hypergraphx import Hypergraph

### Wrapper function
def NO_greedy_hitting_set(connections: set) -> set:

    # I construct the starting hypergraph by adding all the edges in the temporal window to the hypergraph H
    H = Hypergraph(edge_list = connections) 

    # Debug print statements
    print(f"Debug: Starting Hypergraph calculated correctly.")
    print(f"Debug: Number of Hyperedges: {H.num_edges()}")
    print(f"Debug: NO Hitting set construction started.")

    # I calculate an euristical hitting set from the set of connections
    hitting_set = hitting_set_search(H)

    # Debug print statements
    print(f"Debug: NO Hitting set construction completed.")
    print(f"Debug: NO Hitting set size: {len(hitting_set)}\n")

    return hitting_set

### This function return the node with the maximum degree in the given hypergraph
def find_max_degree_node(hypergraph: Hypergraph) -> int:

    # I define the maximum degree and the node with the maximum degree
    max_degree = -1
    max_node = -1

    # I iterate over all the nodes in the hypergraph and find the node with the maximum degree 
    for node in hypergraph.get_nodes():
        degree = hypergraph.degree(node)
        if degree > max_degree:
            max_degree = degree
            max_node = node
    
    return max_node

### This function return the hitting set of the given hypergraph
def hitting_set_search(hypergraph: Hypergraph) -> set:
    
    # I define an empty hitting set
    hitting_set = set()
    
    # I create a list of tuples (node, degree) for all the nodes in the hypergraph and find the node with the maximum degree in the hypergraph
    max_node = find_max_degree_node(hypergraph)
    
    # I now add the node with the maximum degree to the hitting set and remove all the edges that are covered by that node from the hypergraph
    while max_node != -1 and hypergraph.degree(max_node) > 0:

        # I add the node with the maximum degree to the hitting set
        hitting_set.add(max_node)

        # I remove all the edges that are covered by that node from the hypergraph and update the degree of the nodes in the hypergraph
        hypergraph.remove_edges(hypergraph.get_incident_edges(max_node))
        
        # I find the node with the maximum degree in the hypergraph in order to restart the process
        max_node = find_max_degree_node(hypergraph)

    return hitting_set