from hypergraphx import Hypergraph

### Wrapper function
def O_greedy_hitting_set(connections: set) -> set:

    # I construct the starting hypergraph by adding all the edges in the temporal window to the hypergraph H
    H = Hypergraph(edge_list = connections) 

    # Debug print statements
    print(f"Debug: Starting Hypergraph calculated correctly.")
    print(f"Debug: Number of Hyperedges: {H.num_edges()}")
    print(f"Debug: O Hitting set construction started.")

    # I calculate an euristical hitting set from the set of connections
    hitting_set = hitting_set_search(H)

    # Debug print statements
    print(f"Debug: O Hitting set construction completed.")
    print(f"Debug: O Hitting set size: {len(hitting_set)}\n")

    return hitting_set

### This function return the hitting set of the given hypergraph
### It is optimized because we track the number of active arches linked to every node and we also take track of the selected arches already covered using a set
def hitting_set_search(hypergraph: Hypergraph) -> set:
    
    # I define an empty hitting set
    hitting_set = set()

    # I define the set of all the edges that i have already covered
    covered_arches = set()
    
    # I create a list of tuples (node, degree) for all the nodes in the hypergraph and find the node with the maximum degree in the hypergraph
    node_to_value = {node: hypergraph.degree(node) for node in hypergraph.get_nodes()}
    max_node = max(node_to_value.items(), key=lambda x: x[1])[0] 

    print(f"Sborra: {max_node}")
    
    # I now add the node with the maximum degree to the hitting set and remove all the edges that are covered by that node from the hypergraph
    while node_to_value[max_node] > 0:

        # I add the node with the maximum degree to the hitting set
        hitting_set.add(max_node)

        # I remove all the edges that are covered by that node from the hypergraph and update the degree of the nodes in the hypergraph
        arches = hypergraph.get_incident_edges(max_node)
        for arch in arches:
            if arch not in covered_arches:
                covered_arches.add(arch)
                for node in arch:
                    node_to_value[node] -= 1
        
        # I find the node with the maximum degree in the hypergraph in order to restart the process
        max_node = max(node_to_value.items(), key=lambda x: x[1])[0]

    return hitting_set