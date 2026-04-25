import time
from hypergraphx import Hypergraph

### Wrapper function
def DO_greedy_hitting_set(connections: set) -> tuple[set, float]:
    
    start = time.perf_counter()
    
    # I construct the starting hypergraph by adding all the edges in the temporal window to the hypergraph H
    H = Hypergraph(edge_list = connections) 

    # Debug print statements
    print(f"Debug: DO Hitting set construction started.")

    # I calculate an euristical hitting set from the set of connections
    hitting_set = hitting_set_search(H)

    end = time.perf_counter()

    # Debug print statements
    print(f"Debug: DO Hitting set construction completed.\n")

    return (hitting_set, end - start)

### This function return the hitting set of the given hypergraph
### It is partially optimized because we track the number of active arches linked to every node 
def hitting_set_search(hypergraph: Hypergraph) -> set:
    
    # I define an empty hitting set
    hitting_set = set()
    
    # I create a list of tuples (node, degree) for all the nodes in the hypergraph and find the node with the maximum degree in the hypergraph
    node_to_value = {node: hypergraph.degree(node) for node in hypergraph.get_nodes()}
    max_node = max(node_to_value.items(), key=lambda x: x[1])[0] 
    
    # I now add the node with the maximum degree to the hitting set and remove all the edges that are covered by that node from the hypergraph
    while node_to_value[max_node] > 0:

        # I add the node with the maximum degree to the hitting set
        hitting_set.add(max_node)

        # I remove all the edges that are covered by that node from the hypergraph and update the degree of the nodes in the hypergraph
        arches = hypergraph.get_incident_edges(max_node)
        for arch in arches:
            for node in arch:
                node_to_value[node] -= 1
            hypergraph.remove_edge(arch)
        
        # I find the node with the maximum degree in the hypergraph in order to restart the process
        max_node = max(node_to_value.items(), key=lambda x: x[1])[0]

    return hitting_set