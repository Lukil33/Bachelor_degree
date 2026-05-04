from Hitting_set_solver.smallest_arch_hitting_set import hitting_set_search

### This is the function that checks if there are nodes in the hitting set that cover only arches that are alreasy covered by other nodes in the hitting set
def redundancy_check(hypergraph_window: dict, hitting_set: set, safe_nodes: set = set()) -> tuple[set, dict]:
    single_arch_cover: dict = {}

    # I redefine the dictionary that contains how many arches are covered just by the node that has the ID of the key
    for node in hitting_set:
        single_arch_cover[node] = 0

    # I iterate for each arch in the set of arches given
    for time_in_window in hypergraph_window.keys():
        for arch in hypergraph_window[time_in_window].get_edges():

            # I search how many node of the hitting set are present into the considered arch
            nodes_found = list()
            for nodes in arch:
                if nodes in hitting_set:
                    nodes_found.append(nodes)
            
            # If there is just one than i have to upgrade the counter for that node
            if len(nodes_found) == 1:
                single_arch_cover[nodes_found[0]] += 1

    # Check if all nodes in the hitting set are covering at least one arch
    useless_nodes = set()
    for node in hitting_set:
        if single_arch_cover[node] == 0:
            useless_nodes.add(node)

    useless_nodes.difference_update(safe_nodes)
    
    # If there are nodes that are not covering any arch, I remove them from the hitting set and I check if there are arches that are not covered by the new hitting set
    if useless_nodes:
        hitting_set = hitting_set.difference(useless_nodes)
        (usefull_nodes, single_arch_cover) = node_elimination(hypergraph_window, hitting_set)
        hitting_set = hitting_set.union(usefull_nodes)

        # Debug print
        # print(f"Debug: {len(useless_nodes)-len(usefull_nodes)} Nodes has been removed from the Hitting set")

    print(f"The Hitting Set Size after the redundancy check is now: {len(hitting_set)}")
        
    return (hitting_set, single_arch_cover)

### This is the function that given a hypergraph_window it calculates if the HS is able to cover it ompletelly and in case it find new nodew to complete the HS
def node_elimination(hypergraph_window: dict, hitting_set: set) -> tuple[set, dict]:
    # I define a list of not covered arches in order to check if there are some 
    arches_not_covered = list()

    # I then redefine the dictionary that contains how many arches are covered just by the node that has the ID of the key
    single_arch_cover: dict = {}
    for node in hitting_set:
        single_arch_cover[node] = 0
    
    # I iterate for each arch in the set of arches given
    for time_in_window in hypergraph_window:
        for arch in hypergraph_window[time_in_window].get_edges():

            # I search how many node of the hitting set are present into the considered arch
            nodes_found = list()
            for nodes in arch:
                if nodes in hitting_set:
                    nodes_found.append(nodes)
            
            # If there are none than the arch is not covered
            if len(nodes_found) == 0:
                arches_not_covered.append(arch)

            # If there is just one than I have to upgrade the counter for that node
            elif len(nodes_found) == 1:
                single_arch_cover[nodes_found[0]] += 1
    
    small_hs = set()
    
    # Check if there are arches that are not covered by the hitting set
    if arches_not_covered:

        # If there are, I have to find a new hitting set that covers those arches and add it to the current hitting set
        small_hs = hitting_set_search(set(arches_not_covered), set(), dict())

        # I redefine the dictionary that contains how many arches are covered just by the node that has the ID of the key
        for node in small_hs:
            single_arch_cover[node] = 0

        # I iterate for each arch that has a node in the new Hitting Set, considering the edge case in which i do not have that node inside my hypergraph
        for time_in_window in hypergraph_window:
            for node in small_hs:
                if hypergraph_window[time_in_window].check_node(node):
                    for arch in hypergraph_window[time_in_window].get_incident_edges(node):
                        
                        # I search how many node of the hitting set are present into the considered arch
                        nodes_found = list()
                        for element in arch:
                            if element in hitting_set:
                                nodes_found.append(element)
                        
                        # If there is none than I have to upgrade the counter for that node
                        if len(nodes_found) == 0:
                            single_arch_cover[node] += 1
                        
                        # If there is just one than I have to upgrade the counter for that node
                        elif len(nodes_found) == 1:
                            single_arch_cover[nodes_found[0]] -= 1
    
    return (small_hs, single_arch_cover)