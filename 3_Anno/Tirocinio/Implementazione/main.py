import gzip
import json
import sys
from hypergraphx import TemporalHypergraph, Hypergraph

from Hitting_set_solver.minimal_hitting_set import minimal_hitting_set

from Hitting_set_solver.not_optimized_greedy_hitting_set import NO_greedy_hitting_set
from Hitting_set_solver.degree_optimization_greedy_hitting_set import DO_greedy_hitting_set
from Hitting_set_solver.optimized_greedy_hitting_set import O_greedy_hitting_set

from Hitting_set_solver.smallest_arch_hitting_set import smallest_arch_hitting_set
from Hitting_set_solver.random_arch_hitting_set import random_arch_hitting_set
from Hitting_set_solver.biggest_arch_hitting_set import biggest_arch_hitting_set


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
        if element.get("type") == "node":   # If the element is a node, we add it to the hypergraph
            TH.add_node(element.get("idx"), element.get("metadata"))

        elif element.get("type") == "edge": # If the element is an edge, we add it to the hypergraph
            number_of_arches += 1
            TH.add_edge(tuple(x for sublist in element.get("interaction") for x in (sublist if isinstance(sublist, list) else [sublist])), element.get("metadata").get("time"))
        
        else:
            continue # If the element is neither a node nor an edge, we skip it

    # Debug print statements
    print(f"Debug: Hypergraph construction completed.")
    print(f"Debug: Number of nodes: {TH.num_nodes()}")
    print(f"Debug: Number of edges: {TH.num_edges()}")
    print(f"Debug: Number of edges lost due to flattening: {number_of_arches-TH.num_edges()}\n")

    return TH


### This is the function that converts the remporal hypergraph window into the set of arches that are present in that window.
def temporal_hypergraph_to_arches(temporal_hypergraph: TemporalHypergraph, window_size: int, starting_time: int) -> set:
    # I take all the esges in the temporal window from the temporal hypergraph
    dictionary: dict[int, Hypergraph] = temporal_hypergraph.subhypergraph(time_window = tuple([starting_time, starting_time + window_size]))
    
    # I construct the starting connection set by adding all the different edges
    connections: set = set()
    for time in dictionary:
        edges = dictionary[time].get_edges()
        for nodes in edges:
            connections.add(tuple(sorted(nodes)))

    return connections
### This is the function that given a set of arches, it finds the relative hitting set.
def hitting_set_function(arches_set: set) -> set:
    # I find using different approaches some valid hitting set
    #(mhs, tmhs) = minimal_hitting_set(arches_set)
    #(nohs, tnohs) = NO_greedy_hitting_set(arches_set)
    #(dohs, tdohs) = DO_greedy_hitting_set(arches_set)
    #(ohs, tohs) = O_greedy_hitting_set(arches_set)
    #(bahs, tbahs) = biggest_arch_hitting_set(arches_set)
    #(rahs, trahs) = random_arch_hitting_set(arches_set)
    (sahs, tsahs) = smallest_arch_hitting_set(arches_set)

    # Debug print statements
    print("Debug: ---Results recap---")
    print(f"Debug: Number of nodes in the hypergraph: {temporal_hypergraph.num_nodes()}")
    print(f"Debug: Number of edges in the hypergraph: {len(arches_set)}")
    print("Debug: -------------------")
    #print(f"Debug: Minimal hitting set size: {len(mhs)}, Time taken: {tmhs} seconds")
    #print(f"Debug: Not optimized greedy hitting set size: {len(nohs)}, Time taken: {tnohs} seconds")
    #print(f"Debug: Degree optimized greedy hitting set size: {len(dohs)}, Time taken: {tdohs} seconds")
    #print(f"Debug: Optimized greedy hitting set size: {len(ohs)}, Time taken: {tohs} seconds")
    #print(f"Debug: Biggest arch hitting set size: {len(bahs)}, Time taken: {tbahs} seconds")
    #print(f"Debug: Random arch hitting set size: {len(rahs)}, Time taken: {trahs} seconds")
    print(f"Debug: Smallest arch hitting set size: {len(sahs)}, Time taken: {tsahs} seconds")
    print("Debug: -------------------\n")
    
    return sahs


### TODO: da qua in su è giusto



### This is the function that slides the temporal window and extracts the hitting set of nodes that covers all the edges in the hypergraph for each window.
### It is used only when the slide size is bigger than the window size, so when it's easier to recompute from zero the hitting set given an hypergraph.
def bigger_window_slide(temporal_hypergraph: TemporalHypergraph, window_size: int, window_slide_size: int):
    # I define the starting time of the window as the minimum time of the temporal hypergraph
    window_starting_time = temporal_hypergraph.min_time()

    # I iterate until i reach the end of the temporal hypergraph, for each iteration i compute the hitting set nodes and then i update the starting time of the window
    while window_starting_time <= temporal_hypergraph.max_time():
        print(f"Debug: Window starting at time {window_starting_time} and ending at time {window_starting_time + window_size}")
        hitting_set = hitting_set_function(temporal_hypergraph_to_arches(temporal_hypergraph, window_size, window_starting_time))
        print(f"Debug: Window hitting set size: {len(hitting_set)}\n")
        window_starting_time += window_slide_size
    
    # Debug print statement
    print(f"Debug: You have reached the end of the temporal hypergraph")

### This is the function that calculates the degree of each node in the hitting set, it returns a dictionary where the key is the node and the value is a list with the number of edges covered by only that node and the number of edges covered by more than one node in the hitting set.
def nodes_degree_detailed(temporal_hypergraph: TemporalHypergraph, window_size: int, hitting_set: set) -> dict:
    # I define a dictionary to store the degree of each node and I initialize it to 0 single covered nodes and 0 multiple covered nodes
    degree_detailed: dict = {}
    for node in hitting_set:
        degree_detailed[node] = [0, 0]

    # I extract the hypergraph of the current window
    hypergraph = temporal_hypergraph.subhypergraph(time_window = tuple([temporal_hypergraph.min_time(), temporal_hypergraph.min_time() + window_size]))

    # I iterate over every node inside every edges in the temporal hypergraph
    for time in hypergraph:
        for edge in hypergraph[time].get_edges():

            # I define a list to store the nodes of the hitting set that are in the current edge
            nodes_found = list()
            for nodes in edge:
                if nodes in hitting_set:
                    nodes_found.append(nodes)
            
            # If there are more than 1 nodes of the hitting set in the current edge, I update the degree of all the nodes found, otherwise I update the degree of the single node found
            if len(nodes_found) > 1:
                for node in nodes_found:
                    degree_detailed[node][1] += 1
            else:
                degree_detailed[nodes_found[0]][0] += 1
    
    for node in degree_detailed:
        if degree_detailed[node][0] == 0:
            hitting_set.remove(node)
            for arch in hypergraph:
                for node in arch:
                    if node in hitting_set:
                        degree_detailed[node][1] -= 1
            degree_detailed[node][1] = 0

    return degree_detailed
### This is the function that removes the old edges not anymore in the hypergraph and upgrades the hitting set degree.
def remove_arches(hypergraph: dict, hitting_set: set, degree: dict) -> set:
    # I define a dictionary to store the node that have been removed
    removed_nodes = set()

    # I iterate over every node inside every edges in the temporal hypergraph
    for time in hypergraph:
        for edge in hypergraph[time].get_edges():

            # I define a list to store the nodes of the hitting set that are in the current edge
            nodes_found = list()
            for nodes in edge:
                if nodes in hitting_set:
                    nodes_found.append(nodes)
            
            # If there are more than 1 nodes of the hitting set in the current edge, I update the degree of all the nodes found, otherwise I update the degree of the single node found
            if len(nodes_found) > 1:
                for node in nodes_found:
                    degree[node][1] -= 1
            else:
                degree[nodes_found[0]][0] -= 1

    for node in degree:
        if degree[node][0] == 0:
            hitting_set.remove(node)
            removed_nodes.add(node)
            degree[node][1] = 0
    
    return removed_nodes


### This is the function that slides the temporal window and updates the hitting set of nodes that covers all the edges in the hypergraph.
### It is used only when the slide size is smaller than the window size, so when it's more efficient to update the hitting set instead of recomputing it from zero.
def smaller_window_slide(temporal_hypergraph: TemporalHypergraph, starting_hitting_set: set, window_size: int, window_slide_size: int) -> None:
    # TODO: devo efferruare un'iterazione finchè non arrivo e supero il tempo massimo, adesso simulo un solo movimento
    # I define the starting time of the window as the minimum time of the temporal hypergraph
    window_starting_time = temporal_hypergraph.min_time()

    # I check for each arch how many nodes of the HS are in it, this is useful later on
    degree = nodes_degree_detailed(temporal_hypergraph, window_size, starting_hitting_set);

    # I extract two different temporal hypergraphs, the one with the new arches and the one with the old arches and then i udate the starting time of the window
    temporal_hypergraph_old = temporal_hypergraph.subhypergraph(time_window = tuple([window_starting_time, window_starting_time + window_slide_size]))
    temporal_hypergraph_new = temporal_hypergraph.subhypergraph(time_window = tuple([window_starting_time + window_size, window_starting_time + window_slide_size + window_size]))
    window_starting_time += window_slide_size
    
    removed_nodes = remove_arches(temporal_hypergraph_old, starting_hitting_set, degree)
    
    print(f"Debug: removed nodes = {len(removed_nodes)}")
    exit(1)
    print(f"Debug: new")
    for element in temporal_hypergraph_new:
        print(temporal_hypergraph_new[element])



### Main function
if len(sys.argv) != 3 and len(sys.argv) != 4: # Input format check
    print(f"Error: input format is incorrect.")
    print("Usage: uv run <file_name.py> <dataset.json.gz> <temporal_window_size(in seconds)> <optional: temporal_window_slide_size(in seconds)>")
    exit(-1)

# I construct the temporal hypergraph and the list of arrival times of the edges in the dataset based on the decompressed data from the input file
temporal_hypergraph = hypergraph_construction(file_decompression(sys.argv[1]))

# I construct the temporal windows based on the arrival times of the edges in the dataset and the temporal window size provided
window_size = int(sys.argv[2])
window_slide_size = int(sys.argv[3])

# I construct the hitting set of nodes that covers all the edges in the starting hypergraph based on the temporal window size provided
starting_hitting_set = hitting_set_function(temporal_hypergraph_to_arches(temporal_hypergraph, window_size, temporal_hypergraph.min_time()))

# If the slide size is bigger than the window size I just extract the hitting set for each window, otherwise I have to update the hitting set by adding the new edges and removing the old edges
if window_slide_size < window_size:
    smaller_window_slide(temporal_hypergraph, starting_hitting_set, window_size, window_slide_size)
else:
    bigger_window_slide(temporal_hypergraph, window_size, window_slide_size)