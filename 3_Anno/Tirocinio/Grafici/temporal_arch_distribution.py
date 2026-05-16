import gzip
import json
import sys
import matplotlib.pyplot as plt
from hypergraphx import TemporalHypergraph, Hypergraph # type: ignore


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



### Main function
if len(sys.argv) != 2:
    print(f"Usage: uv run <file_name.py> <dataset.json.gz>")
    exit(-1)

temporal_hypergraph = hypergraph_construction(file_decompression(sys.argv[1]))

# Calcolo della finestra
window_slide_size = int((temporal_hypergraph.max_time() - temporal_hypergraph.min_time())/40)
start_time = temporal_hypergraph.min_time()

# --- NUOVA PARTE: RACCOLTA DATI ---
tempi_labels = []
conteggio_archi = []

print("Elaborazione finestre temporali...")
while start_time <= temporal_hypergraph.max_time():
    dizionario = temporal_hypergraph_to_dict(temporal_hypergraph, start_time, start_time + window_slide_size)

    somma = 0
    for t_key in dizionario:
        somma += dizionario[t_key].num_edges()
    
    # Salviamo i dati per il grafico
    tempi_labels.append(f"{start_time}")
    conteggio_archi.append(somma)

    start_time += window_slide_size

# --- GENERAZIONE GRAFICO ACCADEMICO (PDF) ---
print("\nGenerazione grafico PDF...")

# Rimuove gli errori di font mancanti usando i font integrati in Matplotlib
plt.rcParams.update({
    "font.family": "sans-serif",  # Il sans-serif è più stabile sui sistemi Linux minimali
    "font.sans-serif": ["DejaVu Sans"], # Font incluso di default in ogni installazione di Matplotlib
    "pdf.fonttype": 42, 
    "axes.grid": True,
    "grid.alpha": 0.3,
    "grid.linestyle": '--'
})

plt.figure(figsize=(10, 5)) # Un po' più largo per ospitare 40 finestre

file_name_path = sys.argv[1].split('/')[-1].split('.')[0].replace('-', '_') # Estrae il nome del file senza estensione per il titolo
file_name_title = sys.argv[1].split('/')[-1].split('.')[0].replace('-', ' ') # Estrae il nome del file senza estensione per il titolo

# Creazione del grafico a barre
bars = plt.bar(tempi_labels, conteggio_archi, color='#4A90E2', edgecolor='black', linewidth=0.5)

# Personalizzazione Assi
plt.xlabel(f"Time", fontsize=11)
plt.ylabel("Count", fontsize=11)
plt.title(f"Arches Distribution {file_name_title} - Time span: [{temporal_hypergraph.min_time()} - {temporal_hypergraph.max_time()}]", fontsize=12, fontweight='bold')

# Ottimizzazione etichette asse X (mostriamo solo una ogni 2 per non sovrapporle)
plt.xticks(ticks=range(0, len(tempi_labels), 2), labels=tempi_labels[::2], rotation=45)

# Layout compatto e salvataggio
plt.tight_layout()
plt.savefig(f"{file_name_path}_data_distribution.pdf", format="pdf", bbox_inches='tight')

print(f"Successo! Il file '{file_name_path}.pdf' è pronto.")