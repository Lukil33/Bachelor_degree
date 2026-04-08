import gzip
import json
import sys
from hypergraphx import TemporalHypergraph, Hypergraph
from pysat.examples.hitman import Hitman

### This is the data decompression function, it reads a gzip file and returns a dictionary
def file_decompression(filepath) -> list:
    try:
        with gzip.open(filepath, 'rt', encoding='utf-8') as file:
            data = json.load(file)
        return data # Data is now a list containing the contents of the JSON file
    except Exception as e:
        print(f"Errore durante la lettura: {e}")
        exit(-1)

### This is the hypergraph construction function, it takes the decompressed data and constructs the corresponding hypergraph
def hypergraph_construction(data: list) -> tuple[TemporalHypergraph, list]:
    time_list = []
    TH = TemporalHypergraph()

    for element in data:
        if element.get("type") == "node":   # If the element is a node, we add it to the hypergraph
            TH.add_node(element.get("idx"), element.get("metadata"))

        elif element.get("type") == "edge": # If the element is an edge, we add it to the hypergraph
            time_list.append(element.get("metadata").get("time"))
            TH.add_edge(tuple(x for sublist in element.get("interaction") for x in (sublist if isinstance(sublist, list) else [sublist])), element.get("metadata").get("time"))
        
        else:
            continue # If the element is neither a node nor an edge, we skip it

    print(f"Debug: Hypergraph construction completed.")
    print(f"Debug: Number of nodes: {TH.num_nodes()}")
    print(f"Debug: Number of edges: {TH.num_edges()}")
    print(f"Debug: Number of edges lost due to flattening: {len(time_list)-TH.num_edges()}\n")

    return (TH, time_list)


### This is the temporal window construction function, it takes the list of arrival times and constructs the temporal windows based on the provided window size and slide size.
def temporal_window_construction(time: list) -> int:
    time_size = len(time)
    time.sort()
    time_diff = time[int(time_size*0.85)] - time[int(time_size*0.15)]
    time_diff = int(time_diff / (time_size/500)) # We set the temporal window slide size based on the distribution of the dataset given, in particular we set it to be equal to the average inter-arrival time of the edges in the dataset, which is given by the total time difference between the 15th and 85th percentile of the arrival times divided by the number of edges in that time interval (which is 70% of the total number of edges). This way we ensure that we have a good coverage of the edges in the dataset while also avoiding too much overlap between the temporal windows.
    return time_diff

### This is the temporal window construction function, if the slide size is not provided, it is set based on the distribution of the dataset given.
def window_construction(arrival_time_list: list) -> tuple[int,int]:
    window_size = int(sys.argv[2])
    window_slide_size = 0
    if len(sys.argv) == 3: # If the temporal window slide size is not provided, we set it based on the distribution of the dataset given
        window_slide_size = temporal_window_construction(arrival_time_list)
    else:
        window_slide_size = int(sys.argv[3])

    print(f"Debug: Temporal window construction completed.")
    print(f"Debug: Temporal window size: {window_size}")
    print(f"Debug: Temporal window slide size: {window_slide_size}\n")
    return (window_size, window_slide_size)


### This is the function that computes the hitting set of nodes that covers all the edges in the starting hypergraph, it takes as input the temporal hypergraph and the temporal window size, and returns the hitting set of nodes that covers all the edges in the hypergraph.
def hitting_set_construction(temporal_hypergraph: TemporalHypergraph, window_size: int) -> set:
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


### Main function
if len(sys.argv) != 3 and len(sys.argv) != 4: # Input format check
    print(f"Error: input format is incorrect.")
    print("Usage: uv run <file_name.py> <dataset.json.gz> <temporal_window_size(in seconds)> <optional: temporal_window_slide_size(in seconds)>")
    exit(-1)

(temporal_hypergraph, arrival_time_list) = hypergraph_construction(file_decompression(sys.argv[1])) # I construct the temporal hypergraph and the list of arrival times of the edges in the dataset based on the decompressed data from the input file

(window_size, window_slide_size) = window_construction(arrival_time_list) # I construct the temporal windows based on the arrival times of the edges in the dataset and the temporal window size provided

hitting_set = hitting_set_construction(temporal_hypergraph, window_size) # I construct the hitting set of nodes that covers all the edges in the starting hypergraph, using the temporal window size provided