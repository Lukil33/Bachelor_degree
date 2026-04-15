from hypergraphx import TemporalHypergraph, Hypergraph
from pysat.examples.hitman import Hitman

### This is the function that computes the minimal hitting set of nodes that covers all the edges in the starting hypergraph, it takes as input the temporal hypergraph and the temporal window size, and returns the hitting set of nodes that covers all the edges in the hypergraph.
def minimal_hitting_set_construction(temporal_hypergraph: TemporalHypergraph, window_size: int) -> set:
    dictionary: dict[int, Hypergraph] = temporal_hypergraph.subhypergraph(time_window = tuple([temporal_hypergraph.min_time(), temporal_hypergraph.min_time() + window_size]))
    connections: list = []

    for time in dictionary:
        edges: list = dictionary[time].get_edges()
        for nodes in edges:
            connections.append(list(nodes))

    print(f"Debug: Starting Hypergraph calculated correctly.")
    print(f"Debug: Starting Hypergraph size: {len(connections)}")
    print(f"Debug: Hitting set construction started.")
    H = Hitman(bootstrap_with = connections, solver='cd', htype = 'sorted', mxs_exhaust = True)
    element: list = H.get()
    print(f"Debug: Hitting set construction completed.")
    print(f"Debug: Hitting set size: {len(element)}\n")
    return set(element)