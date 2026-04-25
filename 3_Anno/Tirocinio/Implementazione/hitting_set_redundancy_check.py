from Hitting_set_solver.smallest_arch_hitting_set import hitting_set_search

### This is the function that checks if there are nodes in the hitting set that cover only arches that are alreasy covered by other nodes in the hitting set
def redundancy_check(arches_set: set, hitting_set: set) -> tuple[set, set]:
    single_arch_cover: dict = {}
    count_single_covered_arches(arches_set, hitting_set, single_arch_cover)

    # Check if all nodes in the hitting set are covering at least one arch
    useless_nodes = set()
    for node in hitting_set:
        if single_arch_cover[node] == 0:
            useless_nodes.add(node)
    
    # If there are nodes that are not covering any arch, I remove them from the hitting set and I check if there are arches that are not covered by the new hitting set
    if useless_nodes:
        print(useless_nodes)
        print("Il risultato è sbagliato")
        hitting_set = hitting_set.difference(useless_nodes)
        (usefull_nodes, single_arch_cover) = node_elimination(arches_set, hitting_set, useless_nodes)
        hitting_set = hitting_set.union(usefull_nodes)
    else:
        print("Il risultato è corretto")
        
    return (hitting_set, single_arch_cover)

def node_elimination(arches_set: set, hitting_set: set, useless_nodes: set) -> tuple[set, set]:
    arches_not_covered = set()
    arches_possibly_double_covered = set()

    single_arch_cover: dict = {}
    for node in hitting_set:
        single_arch_cover[node] = 0

    for arch in arches_set:
        nodes_found = list()
        for nodes in arch:
            if nodes in hitting_set:
                nodes_found.append(nodes)
            if nodes in useless_nodes:
                arches_possibly_double_covered.add(arch)
        
        if len(nodes_found) == 0:
            arches_not_covered.add(arch)
        elif len(nodes_found) == 1:
            single_arch_cover[nodes_found[0]] += 1
    
    small_hs = set()
    
    # Check if there are arches that are not covered by the hitting set
    if arches_not_covered:
        # If there are, I have to find a new hitting set that covers those arches and add it to the current hitting set
        small_hs = hitting_set_search(arches_not_covered)
    
        # I update the counter of node that single-cover arches 
        count_single_covered_arches(arches_not_covered, small_hs, single_arch_cover)

        # I remove from the single arch counter all the nodes that 
        for arch in arches_possibly_double_covered:
            nodes_found = list()
            new_nodes = list()
            for nodes in arch:
                if nodes in hitting_set:
                    nodes_found.append(nodes)
                if nodes in small_hs:
                    new_nodes.append(nodes)
            
            if (not new_nodes) and len(nodes_found) == 1:
                single_arch_cover[nodes_found[0]] -= 1
    
    return (small_hs, single_arch_cover)

def count_single_covered_arches(arches_set: set, hitting_set: set, single_arch_cover: dict):
    # I set to 0 the number of arches covered by only one node in the hitting set for each node
    for node in hitting_set:
        single_arch_cover[node] = 0

    # I iterate for each arch in the set of arches given
    for arch in arches_set:
        # I define a list to store the nodes of the hitting set that are in the current edge
        nodes_found = list()
        for nodes in arch:
            if nodes in hitting_set:
                nodes_found.append(nodes)
        
        # If there is just 1 nodes of the hitting set in the current arch, I update the degree of the single node found
        if len(nodes_found) == 1:
            single_arch_cover[nodes_found[0]] += 1