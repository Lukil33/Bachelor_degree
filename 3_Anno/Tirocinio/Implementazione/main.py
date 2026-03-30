import gzip
import json
import sys
from itertools import chain
from hypergraphx import TemporalHypergraph

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
def hypergraph_construction(data: list) -> TemporalHypergraph:
    i=0 # TODO: Rimuovi questa variabile di debug
    c=0 # TODO: Rimuovi questa variabile di debug
    t=0 # TODO: Rimuovi questa variabile di debug
    TH = TemporalHypergraph()

    for element in data:
        if element.get("type") == "node":   # If the element is a node, we add it to the hypergraph
            TH.add_node(element.get("idx"), element.get("metadata"))

        elif element.get("type") == "edge": # If the element is an edge, we add it to the hypergraph
            i+=1 # TODO: Rimuovi questa variabile di debug
            if (x for sublist in element.get("interaction") for x in (sublist if isinstance(sublist, list) else [sublist])) is not None:
                c+=1 # TODO: Rimuovi questa variabile di debug
            if element.get("metadata").get("time") is not None:
                t+=1 # TODO: Rimuovi questa variabile di debug
            # TODO: sto perdendo qualche dato qua e continuo a non capire perchè
            TH.add_edge(tuple(x for sublist in element.get("interaction") for x in (sublist if isinstance(sublist, list) else [sublist])), element.get("metadata").get("time"))
        
        else:
            continue # If the element is neither a node nor an edge, we skip it

    print(f"Debug: Hypergraph construction completed.")
    print(f"Number of nodes: {TH.num_nodes()}")
    print(f"Number of edges: {TH.num_edges()}")
    print(f"Correct number of edges: {i}") # TODO: Rimuovi questa variabile di debug
    print(f"Edges with some connection: {c}") # TODO: Rimuovi questa variabile di debug
    print(f"Edges with some time: {t}") # TODO: Rimuovi questa variabile di debug
    return TH

### Main function
if len(sys.argv) != 2: # Controlla se è stato fornito un argomento
    print(f"Error: input format is incorrect.")
    print("Usage: uv run main.py <dataset.json.gz>")
    exit(-1)

hypergraph_construction(file_decompression(sys.argv[1])) # Costruisco l'ipergrafo a partire dal file passato come argomento