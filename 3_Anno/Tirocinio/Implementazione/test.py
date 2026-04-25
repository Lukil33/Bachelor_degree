from hypergraphx import Hypergraph
from hitting_set_redundancy_check import redundancy_check

archi = set()
archi.add((1,2))
archi.add((2,3))
archi.add((3,4))
archi.add((4,5))

hitting_set = set()
hitting_set.add(1)
hitting_set.add(2)
hitting_set.add(3)
hitting_set.add(4)
hitting_set.add(5)

hitting_set = redundancy_check(archi,hitting_set)
print(f"Debug: Hitting set construction completed.")
print(f"Debug: Node in the hitting set: {hitting_set}")