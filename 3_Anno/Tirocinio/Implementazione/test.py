from hypergraphx import Hypergraph
from minimal_hitting_set import minimal_hitting_set_construction
from euristic_hitting_set import greedy_euristic_hitting_set

H = Hypergraph()
H.add_edges([(1,2,3), (2,3,4), (3,4,5), (4,5,6), (5,6,7), (6,7,8), (7,8,9), (8,9,10), (9,10,11), (10,11,12)])
nodes = set()
for edges in H.get_edges():
    for node in edges:
        nodes.add(node)

print(f"Debug: nodes: {nodes}.")

hitting_set = greedy_euristic_hitting_set(H, nodes)
print(f"Debug: Hitting set construction completed.")
print(f"Debug: Number of edges in the hypergraph: {hitting_set}")