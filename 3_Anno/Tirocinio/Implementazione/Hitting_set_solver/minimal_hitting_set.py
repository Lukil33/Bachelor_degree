import time
from pysat.examples.hitman import Hitman

### This is the function that computes the minimal hitting set of nodes that covers all the edges in the starting hypergraph
def minimal_hitting_set(connections: set) -> tuple[set, float]:

    start = time.perf_counter()

    # Debug print statements
    print(f"Debug: Minimal Hitting set construction started.")
    
    # I calculate the minimal hitting set from the set of connections
    H = Hitman(bootstrap_with = connections, solver='cd', htype = 'sorted', mxs_exhaust = True)
    element: list = H.get()

    end = time.perf_counter()
    
    # Debug print statements
    print(f"Debug: Minimal Hitting set construction completed.\n")

    return (set(element), end - start)