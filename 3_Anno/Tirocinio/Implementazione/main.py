import gzip
from itertools import dropwhile, takewhile
import json
import sys
import time
from typing import Counter
from hypergraphx import TemporalHypergraph, Hypergraph # type: ignore

from Hitting_set_solver.minimal_hitting_set import minimal_hitting_set

from Hitting_set_solver.not_optimized_greedy_hitting_set import NO_greedy_hitting_set
from Hitting_set_solver.degree_optimization_greedy_hitting_set import DO_greedy_hitting_set
from Hitting_set_solver.optimized_greedy_hitting_set import O_greedy_hitting_set

from Hitting_set_solver.smallest_arch_hitting_set import complete_smallest_arch_hitting_set, partial_smallest_arch_hitting_set
from Hitting_set_solver.random_arch_hitting_set import complete_random_arch_hitting_set, partial_random_arch_hitting_set
from Hitting_set_solver.biggest_arch_hitting_set import complete_biggest_arch_hitting_set, partial_biggest_arch_hitting_set

from Hitting_set_solver.hitting_set_redundancy_check import redundancy_check

from media import MediaMobile


med = MediaMobile()
num_elem_nuovi = 0


### This is the data decompression function, it reads a gzip file and returns a dictionary
def file_decompression(filepath) -> list:
    try:
        # I read the gzip file and load the json data into a list
        with gzip.open(filepath, 'rt', encoding='utf-8') as file:
            data = json.load(file)

        return data
    except Exception as e:
        print(f"Errore durante la lettura: {e}")
        exit(-1)
### This is the hypergraph construction function, it takes the decompressed data and constructs the corresponding hypergraph
def hypergraph_construction(data: list) -> TemporalHypergraph:
    # I define an empty list to store the arrival times of the edges in the dataset and an empty temporal hypergraph
    TH = TemporalHypergraph()
    number_of_arches = 0

    # I iterate over all the elements in the decompressed data and add them to the hypergraph
    for element in data:
        # If the element is a node, we add it to the hypergraph
        if element.get("type") == "node":
            TH.add_node(element.get("idx"), element.get("metadata"))

        # If the element is an edge, we add it to the hypergraph
        elif element.get("type") == "edge":
            number_of_arches += 1
            TH.add_edge(tuple(x for sublist in element.get("interaction") for x in (sublist if isinstance(sublist, list) else [sublist])), element.get("metadata").get("time"))
        
        # If the element is neither a node nor an edge, we skip it
        else:
            continue

    print(f"The Temporal Hypergraph has been constructed")
    print(f"Total Number of nodes: {TH.num_nodes()}")
    print(f"Total Number of edges: {TH.num_edges()}")
    print(f"Total time span: [{TH.min_time()}, {TH.max_time()}]\n")
    # Debug print statement
    # print(f"Debug: Number of edges lost due to flattening: {number_of_arches-TH.num_edges()}\n")

    return TH


### This is the function that return a temporal hypergraph slice
def temporal_hypergraph_to_dict(temporal_hypergraph: TemporalHypergraph, start_time: int, finish_time: int) -> dict:
    return temporal_hypergraph.subhypergraph(time_window = tuple([start_time, finish_time]))
### This is the function that converts the dictionary of a temporal hypergraph window into the set of arches that are present in that window.
def dict_to_set_of_arches(dictionary: dict[int, Hypergraph]) -> set:
    # I construct the starting connection set by adding all the different edges
    connections: set = set()
    for time in dictionary:
        edges = dictionary[time].get_edges()
        for nodes in edges:
            connections.add(tuple(sorted(nodes)))

    return connections

### This is the function that given a set of arches and a list of algorithms, it finds the relative hitting set using the apposite algorithm.
def complete_hypergraph_hitting_set_function(arches_set: set, algorithms: list[str]) -> list[set]:
    # This variable lists all the resulting Hitting Sets
    results_list = list()

    # Debug print
    # print("Debug: ---- HS Algorithms ----")
    # print(f"Debug: Number of different arches: {len(arches_set)}")
    # print("Debug: -----------------------")

    # I find using different approaches some valid hitting set
    for algo in algorithms:
        match algo:
            case "mhs":
                (hs, ths) = minimal_hitting_set(arches_set)
            case "nohs":
                (hs, ths) = NO_greedy_hitting_set(arches_set)
            case "dohs":
                (hs, ths) = DO_greedy_hitting_set(arches_set)
            case "ohs":
                (hs, ths) = O_greedy_hitting_set(arches_set)
            case "bahs":
                (hs, ths) = complete_biggest_arch_hitting_set(arches_set)
            case "rahs":
                (hs, ths) = complete_random_arch_hitting_set(arches_set)
            case "sahs":
                (hs, ths) = complete_smallest_arch_hitting_set(arches_set)
            case _:
                print(f"Debug: Algorithm {algo}, does not exist")

        results_list.append(hs)
        print(f"Debug: Complete hitting set size: {len(hs)}, Time taken: {ths} seconds")

    # Debug Print
    # print("Debug: -----------------------\n")

    return results_list
### This is the function that given a set of arches, a set of not covered arches, the node appearence dictionary and a list of algorithms, it finds the relative hitting set using the apposite algorithm.
def partial_hypergraph_hitting_set_function(arches_set: set, not_covered_arches_set: set, node_presence_into_hs: dict, algorithms: list[str]) -> list[set]:
    # This variable lists all the resulting Hitting Sets
    results_list = list()

    # Debug print
    # print("Debug: ---- HS Algorithms ----")
    # print(f"Debug: Number of different arches: {len(arches_set)}")
    # print("Debug: -----------------------")

    # I find using different approaches some valid hitting set
    for algo in algorithms:
        hs = 0
        ths = 0
        match algo:
            case "mhs":
                (hs, ths) = minimal_hitting_set(arches_set)
            case "nohs":
                (hs, ths) = NO_greedy_hitting_set(arches_set)
            case "dohs":
                (hs, ths) = DO_greedy_hitting_set(arches_set)
            case "ohs":
                (hs, ths) = O_greedy_hitting_set(arches_set)
            case "bahs":
                (hs, ths) = partial_biggest_arch_hitting_set(arches_set, not_covered_arches_set, node_presence_into_hs)
            case "rahs":
                (hs, ths) = partial_random_arch_hitting_set(arches_set, not_covered_arches_set, node_presence_into_hs)
            case "sahs":
                (hs, ths) = partial_smallest_arch_hitting_set(arches_set, not_covered_arches_set, node_presence_into_hs)
            case _:
                print(f"Debug: Algorithm {algo}, does not exist")

        results_list.append(hs)
        #print(f"Debug: Partial hitting set size: {len(hs)}, Time taken: {ths} seconds")
    
    # Debug Print
    # print("Debug: -----------------------\n")

    return results_list


### This is the function that upgrade the dictionary that contains the last time a certain node has been part of the hitting set
def update_node_presence(node_presence_into_hs: dict[int, int], hitting_set: set, time: int):
    # For every node in the hitting set i update their time
    for node in hitting_set:
        node_presence_into_hs[node] = time

    # Debug print
    # print(f"Debug: I have successfully updated the node presence time")
### This is the function that removes the old edges not anymore in the hypergraph and upgrades the hitting set degree.
def remove_arches(hypergraph: dict, hitting_set: set, degree: dict):
    # I iterate over every node inside every arch in the temporal hypergraph
    for time in hypergraph:
        for arch in hypergraph[time].get_edges():

            # I define a list to store the nodes of the hitting set that are in the current arch
            nodes_found = list()
            for nodes in arch:
                if nodes in hitting_set:
                    nodes_found.append(nodes)
            
            # If there only one node of the hitting set in the current edge, I update the degree of the single node found
            if len(nodes_found) == 1:
                degree[nodes_found[0]] -= 1

    # If there are node with a degree of 0 it means that they are not usefull anymore
    for node in degree:
        if degree[node] == 0 and node in hitting_set:
            hitting_set.remove(node)

    # Debug print
    # print(f"Debug: Hitting Set Size after arches removal: {len(hitting_set)}\n")
### This is the function that divides the arches in three sets, the one that are already covered, the one that are covered from previous Hitting Set nodes and the one that are not covered at all
def clean_up_and_arch_division(arches_set: set, hitting_set: set, node_presence_into_hs: dict[int, int]) -> set:
    # I define two sets to store all the arches that are covered from HS nodes and from node that were previously in the HS.
    rnHS_covered_arches = set()
    HS_covered_arches = set()

    # I iterate over every node inside the arch set
    for arch in arches_set:
        for node in arch:
            # If the node is covered by the Hitting Set I insert it in the set of arches covered by the HS
            if node in hitting_set:
                HS_covered_arches.add(arch)
            
            # If the node is covered by a node that was in the Hitting Set I insert it in the set of arches that are covered by node in previous HS
            if node_presence_into_hs[node] > 0:
                rnHS_covered_arches.add(arch)

    # Debug print
    # print(f"Debug: I have successfully separated the new arches")
    
    # I update the set of arches in order to remove arches that are already covered by the HS
    arches_set.difference_update(HS_covered_arches)

    # I return the set of arches that contains only the arches that do not contain nodes eather from the HS that from nodes previously in the HS
    return arches_set.difference(rnHS_covered_arches)
### This is the function that slides the temporal window and updates the hitting set of nodes that covers all the edges in the hypergraph.
def window_slide_function(temporal_hypergraph: TemporalHypergraph, hitting_set: set, window_size: int, window_slide_size: int, single_arch_cover: dict) -> None:
    # I define the starting time of the window as the minimum time of the temporal hypergraph
    window_starting_time = temporal_hypergraph.min_time()

    # I define the last time at which each node has been present into the Hitting Set
    node_presence_into_hs = dict()
    for node in temporal_hypergraph.get_nodes():
        node_presence_into_hs[node] = 0

    # I iterate until window does not reach the last arch in the Temporal Hypergraph
    while window_starting_time+window_size-window_slide_size <= temporal_hypergraph.max_time():
        
        print("--- New window Shift ---")
        print(f"From [{window_starting_time},{window_starting_time+window_size}] to [{window_starting_time+window_slide_size}, {window_starting_time+window_size+window_slide_size}]")
        print(f"Starting Hitting Set Size: {len(hitting_set)}\n")

        global num_elem_nuovi

        for elem in hitting_set:
            if node_presence_into_hs[elem] == 0:
                num_elem_nuovi += 1

        # I update the counter of the last time at which each node has been present into the Hitting Set
        update_node_presence(node_presence_into_hs, hitting_set, window_starting_time + window_size)

        if window_size<=window_slide_size:
        #if window_size<=window_slide_size or True:
            # I define the set of arches without repetition
            temporal_hypergraph_slice = temporal_hypergraph_to_dict(temporal_hypergraph, window_starting_time+window_slide_size, window_starting_time+window_slide_size+window_size)
            set_of_arches = dict_to_set_of_arches(temporal_hypergraph_slice)

            # I run the offline hitting set algorithm
            redundant_hitting_set = complete_hypergraph_hitting_set_function(set_of_arches, ["sahs"])

            # I check the newly discovered hitting set and i remove the useless nodes
            (hitting_set, single_arch_cover) = redundancy_check(temporal_hypergraph_slice, redundant_hitting_set[0])
        
        else:
            # I extract all the usefull arches from the temporal hypergraph 
            temporal_hypergraph_dict = temporal_hypergraph_to_dict(temporal_hypergraph, window_starting_time, window_starting_time + window_slide_size + window_size)
            
            # and then I remove them from the temporal window checking at the same time if I can reduce the hitting set size
            old_temporal_hypergraph_slice = {k: temporal_hypergraph_dict[k] for k in range(window_starting_time, window_starting_time + window_slide_size + 1) if k in temporal_hypergraph_dict}

            remove_arches(old_temporal_hypergraph_slice, hitting_set, single_arch_cover)

            # I extract the new arches from the temporal hypergraph in order to find an Hitting set of those arches
            new_hypergraph_arches = dict_to_set_of_arches({k: temporal_hypergraph_dict[k] for k in range(window_starting_time + window_size + 1, window_starting_time + window_slide_size + window_size + 1) if k in temporal_hypergraph_dict})
            
            # I clean the hypergraph deleting the arches already covered by the Hitting Set
            not_covered_arches = clean_up_and_arch_division(new_hypergraph_arches, hitting_set, node_presence_into_hs)

            # I calculate the hitting set for the new arches and i update the hitting set
            new_nodes_hitting_set = partial_hypergraph_hitting_set_function(new_hypergraph_arches, not_covered_arches, node_presence_into_hs, ["sahs"])
            redundant_hitting_set = hitting_set.union(new_nodes_hitting_set[0])

            # I check the newly discovered hitting set and i remove the useless nodes
            dizionario = {k: temporal_hypergraph_dict[k] for k in range(window_starting_time + window_slide_size + 1, window_starting_time + window_slide_size + window_size + 1) if k in temporal_hypergraph_dict}
            (hitting_set, single_arch_cover) = redundancy_check(dizionario, redundant_hitting_set)

        global med
        med.aggiungi(len(hitting_set))

        # I shift effectivelly the window starting time
        window_starting_time += window_slide_size

        print("-----------------------\n\n")

    print(f"You have reached the end of the temporal hypergraph")


### Main function
start = time.perf_counter()

if len(sys.argv) != 4: # Input format check
    print(f"Error: input format is incorrect.")
    print("Usage: uv run <file_name.py> <dataset.json.gz> <temporal_window_size> <temporal_window_slide_size>")
    exit(-1)

# I construct the temporal hypergraph and the list of arrival times of the edges in the dataset based on the decompressed data from the input file
temporal_hypergraph = hypergraph_construction(file_decompression(sys.argv[1]))

# I construct the temporal windows based on the arrival times of the edges in the dataset and the temporal window size provided
window_size = int(sys.argv[2])
window_slide_size = int(sys.argv[3])

# Debug print
# print(f"Debug: The Window size is: {window_size}")
# print(f"Debug: The Window slide size is: {window_slide_size}")

print("- Starting Hitting Set -")

# I define the set of arches without repetition, i run the first hitting set algorithm and then i check the solution and delete the useless nodes
temporal_hypergraph_slice = temporal_hypergraph_to_dict(temporal_hypergraph, temporal_hypergraph.min_time(), temporal_hypergraph.min_time()+window_size)
redundant_hitting_set = complete_hypergraph_hitting_set_function(dict_to_set_of_arches(temporal_hypergraph_slice), ["sahs"])
(hitting_set, single_arch_cover) = redundancy_check(temporal_hypergraph_slice, redundant_hitting_set[0])

print("-----------------------\n\n")

window_slide_function(temporal_hypergraph, hitting_set, window_size, window_slide_size, single_arch_cover)

end = time.perf_counter()
print(f"Time taken: {end-start}")
print(f"Dimensione media HS: {med.media()}")
print(f"Numero elementi nuovi: {num_elem_nuovi}")