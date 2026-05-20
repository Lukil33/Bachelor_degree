import sys

import matplotlib.pyplot as plt
import numpy as np
import os

# Creazione cartelle per i risultati
os.makedirs("time_distribution_graphs", exist_ok=True)
os.makedirs("size_distribution_graphs", exist_ok=True)
os.makedirs("reuse_distribution_graphs", exist_ok=True)

# Configurazione stile accademico
plt.rcParams.update({
    "font.family": "sans-serif",
    "font.sans-serif": ["DejaVu Sans"],
    "pdf.fonttype": 42,
    "axes.grid": True,
    "grid.alpha": 0.3,
    "grid.linestyle": '--'
})

def genera_grafico_dataset(nome_dataset, data_type, path_type, title, dati_algoritmi, window_size, slide_size):
    labels_input = [f'Window size = [{window_size[i]}]\nSlide size = [{slide_size[i]}]' for i in range(len(window_size))]
    x = np.arange(len(labels_input))
    width = 0.20

    fig, ax = plt.subplots(figsize=(10, 6))

    # Plotting delle barre per ogni algoritmo
    rects1 = ax.bar(x - width - width/2, dati_algoritmi['greedy_algorithm'], width, label='Iterative Greedy', color='#4A90E2', edgecolor='black')
    rects2 = ax.bar(x - width/2, dati_algoritmi['window_random'], width, label='Sliding Random', color="#50E35F", edgecolor='black')
    rects3 = ax.bar(x + width/2, dati_algoritmi['window_no_reuse'], width, label='Sliding New Nodes', color='#F5A623', edgecolor='black')
    rects4 = ax.bar(x + width + width/2, dati_algoritmi['window_with_reuse'], width, label='Sliding Reuse', color='#E74C3C', edgecolor='black')

    # --- CALIBRAZIONE AUTOMATICA E ZOOM ASSE Y ---
    all_values = [v for sublist in dati_algoritmi.values() for v in sublist]
    min_val = min(all_values) if all_values else 0
    max_val = max(all_values) if all_values else 1
    
    delta = max_val - min_val
    if delta == 0: 
        delta = max_val * 0.1

    # Impostiamo lo zoom per evidenziare le differenze minime
    ax.set_ylim(min_val - delta * 0.15, max_val + delta * 0.3) 
    ax.ticklabel_format(style='plain', axis='y')

    # --- AGGIUNTA ETICHETTE DRITTE (SCARTO DA ITERATIVE GREEDY) ---
    # Creiamo una mappatura per associare ogni barra al suo indice di configurazione (finestra)
    # ax.patches restituisce le barre nell'ordine in cui sono state disegnate (rects1, poi rects2...)
    # Ci sono len(window_size) barre per ogni algoritmo.
    num_configs = len(window_size)
    greedy_values = dati_algoritmi['greedy_algorithm']

    for idx, p in enumerate(ax.patches):
        height = p.get_height()
        if height > 0:
            # Capiamo a quale configurazione (0, 1 o 2) appartiene la barra corrente
            config_idx = idx % num_configs
            baseline_val = greedy_values[config_idx]
            
            # Calcoliamo la differenza rispetto a Iterative Greedy
            diff = height - baseline_val
            
            # Formattazione del testo in base al tipo di dato (Time con decimali, Nodi intero)
            if idx < num_configs:
                # Queste sono le barre di Iterative Greedy stesso
                label_text = 'Ref' 
            else:
                if path_type == "time":
                    label_text = f'+{diff:.2f}' if diff >= 0 else f'{diff:.2f}'
                else:
                    label_text = f'+{int(diff)}' if diff >= 0 else f'{int(diff)}'

            ax.annotate(label_text,
                        (p.get_x() + p.get_width() / 2., height),
                        ha='center', va='bottom', 
                        xytext=(0, 4), 
                        textcoords='offset points',
                        fontsize=8,
                        fontweight='bold',
                        rotation=0) # Numeri perfettamente dritti

    # --- CONFIGURAZIONE ASSI E TITOLI ---
    ax.set_ylabel(f'{data_type}\n(Values above bars: deviation from Iterative Greedy)', fontsize=11)
    ax.set_title(f'{title} - {nome_dataset}', fontsize=14, fontweight='bold', pad=25)
    ax.set_xticks(x)
    ax.set_xticklabels(labels_input)
    
    # Legenda esterna pulita ed elegante
    ax.legend(loc='center left', bbox_to_anchor=(1.02, 0.5), frameon=True, shadow=True, fontsize=10)

    plt.tight_layout()
    
    filename = sys.argv[1].split('/')[-1].split('.')[0].replace('-', '_')
    plt.savefig(f"{path_type}_distribution_graphs/{filename}.pdf", format="pdf", bbox_inches='tight')
    plt.close()

### Main function
if len(sys.argv) != 2:
    print(f"Usage: uv run <file_name.py> <dataset.json.gz>")
    exit(-1)

file_name_path = sys.argv[1].split('/')[-1].split('.')[0].replace('-', '_') # Estrae il nome del file senza estensione per il titolo
file_name_title = sys.argv[1].split('/')[-1].split('.')[0].replace('-', ' ') # Estrae il nome del file senza estensione per il titolo

mock_data_time = {
    'greedy_algorithm': [807.59, 118.82, 276.49],
    'window_random': [754.32, 148.14, 324.67],
    'window_no_reuse': [801.89, 146.20, 325.06],
    'window_with_reuse': [766.79, 145.74, 340.88]
}
mock_data_size = {
    'greedy_algorithm': [195110, 186003, 54698],
    'window_random': [191672, 181576, 54129],
    'window_no_reuse': [191775, 181372, 54221],
    'window_with_reuse': [191466, 181302, 54020]
}
mock_data_reuse = {
    'greedy_algorithm': [580410, 490625, 647426],
    'window_random': [439921, 427930, 458193],
    'window_no_reuse': [450486, 436531, 505846],
    'window_with_reuse': [439248, 427289, 457529]
}

window_size = ["3x10^5", "3x10^5", "7x10^4"]
slide_size = ["1x10^4", "1x10^5", "1x10^4"]

genera_grafico_dataset(f"Dataset {file_name_title}", "Time (s)", "time", "Execution Time Comparison", mock_data_time, window_size, slide_size)
genera_grafico_dataset(f"Dataset {file_name_title}", "Hitting Set Size (nodes)", "size", "Hitting Set Size Comparison", mock_data_size, window_size, slide_size)
genera_grafico_dataset(f"Dataset {file_name_title}", "Nodes Reused (nodes)", "reuse", "Nodes Reuse Comparison", mock_data_reuse, window_size, slide_size)