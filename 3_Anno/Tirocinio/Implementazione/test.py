from hypergraphx import Hypergraph
from Hitting_set_solver.hitting_set_redundancy_check import redundancy_check

archi = list()
archi.append((1,2))
archi.append((2,3,4))
archi.append((2,5,6))
archi.append((5,8))
archi.append((4,9))
archi.append((1,7))

hitting_set = set()
hitting_set.add(1)
hitting_set.add(2)
hitting_set.add(4)
hitting_set.add(5)

hitting_set = redundancy_check(archi,hitting_set)
print(f"Debug: Hitting set construction completed.")
print(f"Debug: Node in the hitting set: {hitting_set}")