from hypergraphx import Hypergraph
from optimized_greedy_hitting_set import hitting_set_search

H = Hypergraph()
H.add_edges([(1,2), (2,3), (3,4), (4,5)])

print(f"Debug: nodes: {H.get_nodes()}.")

hitting_set = hitting_set_search(H)
print(f"Debug: Hitting set construction completed.")
print(f"Debug: Number of edges in the hypergraph: {hitting_set}")