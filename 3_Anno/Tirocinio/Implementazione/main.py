import gzip
import json
import sys
from hypergraphx import TemporalHypergraph, Hypergraph

from minimal_hitting_set import minimal_hitting_set

from not_optimized_greedy_hitting_set import NO_greedy_hitting_set
from degree_optimization_greedy_hitting_set import DO_greedy_hitting_set
from optimized_greedy_hitting_set import O_greedy_hitting_set

from not_optimized_arch_driven_hitting_set import NO_arch_driven_hitting_set


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
def hypergraph_construction(data: list) -> tuple[TemporalHypergraph, list]:
    # I define an empty list to store the arrival times of the edges in the dataset and an empty temporal hypergraph
    time_list = []
    TH = TemporalHypergraph()

    # I iterate over all the elements in the decompressed data and add them to the hypergraph
    for element in data:
        if element.get("type") == "node":   # If the element is a node, we add it to the hypergraph
            TH.add_node(element.get("idx"), element.get("metadata"))

        elif element.get("type") == "edge": # If the element is an edge, we add it to the hypergraph
            time_list.append(element.get("metadata").get("time"))
            TH.add_edge(tuple(x for sublist in element.get("interaction") for x in (sublist if isinstance(sublist, list) else [sublist])), element.get("metadata").get("time"))
        
        else:
            continue # If the element is neither a node nor an edge, we skip it

    # Debug print statements
    print(f"Debug: Hypergraph construction completed.")
    print(f"Debug: Number of nodes: {TH.num_nodes()}")
    print(f"Debug: Number of edges: {TH.num_edges()}")
    print(f"Debug: Number of edges lost due to flattening: {len(time_list)-TH.num_edges()}\n")

    return (TH, time_list)


### This is the temporal window construction function, it takes the list of arrival times and constructs the temporal windows based on the provided window size and slide size.
def temporal_window_construction(time: list) -> int:

    # I set the temporal window slide size based on the distribution of the dataset given
    time_size = len(time)
    time.sort()
    time_diff = time[int(time_size*0.85)] - time[int(time_size*0.15)]
    time_diff = int(time_diff / (time_size/500))

    return time_diff
### This is the temporal window construction function, if the slide size is not provided, it is set based on the distribution of the dataset given.
def window_construction(arrival_time_list: list) -> tuple[int,int]:
    window_size = int(sys.argv[2])
    window_slide_size = 0

    # If the temporal window slide size is not provided, we set it based on the distribution of the given dataset 
    if len(sys.argv) == 3:
        window_slide_size = temporal_window_construction(arrival_time_list)
    else:
        window_slide_size = int(sys.argv[3])

    # Debug print statements
    print(f"Debug: Temporal window construction completed.")
    print(f"Debug: Temporal window size: {window_size}")
    print(f"Debug: Temporal window slide size: {window_slide_size}\n")

    return (window_size, window_slide_size)


### This is the function that computes the hitting set of nodes that covers all the edges in the starting hypergraph, it takes as input the temporal hypergraph and the temporal window size, and returns the hitting set of nodes that covers all the edges in the hypergraph.
def hitting_set_construction(temporal_hypergraph: TemporalHypergraph, window_size: int) -> set:
    # I take all the esges in the temporal window from the temporal hypergraph
    dictionary: dict[int, Hypergraph] = temporal_hypergraph.subhypergraph(time_window = tuple([temporal_hypergraph.min_time(), temporal_hypergraph.min_time() + window_size]))
    
    # I construct the starting connection set by adding all the different edges
    connections: set = set()
    for time in dictionary:
        edges: list = dictionary[time].get_edges()
        for nodes in edges:
            connections.add(tuple(sorted(list(nodes))))

    # I find using different approaches some valid hitting set
    mhs = minimal_hitting_set(connections)
    nohs = NO_greedy_hitting_set(connections)
    dohs = DO_greedy_hitting_set(connections)
    ohs = O_greedy_hitting_set(connections)
    noadhs = NO_arch_driven_hitting_set(connections)
    
    # Debug print statements
    print(f"Debug: Minimal hitting set size: {len(mhs)}")
    print(f"Debug: Not optimized greedy hitting set size: {len(nohs)}\n")
    print(f"Debug: Degree optimized greedy hitting set size: {len(dohs)}\n")
    print(f"Debug: Optimized greedy hitting set size: {len(ohs)}\n")
    print(f"Debug: Not optimized arch driven hitting set size: {len(noadhs)}\n")

    return mhs


### Main function
if len(sys.argv) != 3 and len(sys.argv) != 4: # Input format check
    print(f"Error: input format is incorrect.")
    print("Usage: uv run <file_name.py> <dataset.json.gz> <temporal_window_size(in seconds)> <optional: temporal_window_slide_size(in seconds)>")
    exit(-1)

# I construct the temporal hypergraph and the list of arrival times of the edges in the dataset based on the decompressed data from the input file
(temporal_hypergraph, arrival_time_list) = hypergraph_construction(file_decompression(sys.argv[1]))

# I construct the temporal windows based on the arrival times of the edges in the dataset and the temporal window size provided
(window_size, window_slide_size) = window_construction(arrival_time_list)

# I construct the hitting set of nodes that covers all the edges in the starting hypergraph based on the temporal window size provided
starting_hitting_set = hitting_set_construction(temporal_hypergraph, window_size)

# TODO: crea una funzione per capire ad ogni passo della finestra temporale come aggiornare le varie componenti, ovvero cosa va modificato?