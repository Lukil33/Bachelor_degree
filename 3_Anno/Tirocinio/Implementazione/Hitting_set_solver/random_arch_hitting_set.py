import time
from typing import Counter

### Wrapper function
def random_arch_hitting_set(connections: set) -> tuple[set, float]:

    start = time.perf_counter()

    # Debug print statements
    print(f"Debug: RA Hitting set construction started.")

    # I calculate an euristical hitting set from the set of connections
    hitting_set = hitting_set_search(connections)

    end = time.perf_counter()

    # Debug print statements
    print(f"Debug: RA Hitting set construction completed.\n")

    return (hitting_set, end - start)

### This function return the hitting set of the given hypergraph
def hitting_set_search(connections: set) -> set:
    
    # I define an empty hitting set
    hitting_set = set()

    # I create a dictionary that maps each node to its degree in the hypergraph
    node_to_val = Counter(node for arch in connections for node in arch)
    
    for arches in connections:

        # I set the inital values
        already_covered = False
        max_degree = 0
        max_node = -1

        # I check if the current arch is already covered by the hitting set, if not I add the node with the highest degree to the hitting set
        for node in arches:
            if node in hitting_set:
                already_covered = True
            if node_to_val[node] > max_degree:
                max_degree = node_to_val[node]
                max_node = node
            node_to_val[node] -= 1
        
        if not already_covered:
            hitting_set.add(max_node)

    return hitting_set