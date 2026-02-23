import pandas as pd
import plotly.express as px

# Carico il dataset
file = pd.read_csv("Dataset/PIL_per_paese.csv", skiprows=4)
anno = '2023'

# Carico i dati per ottenere le regioni e sottoregioni dei relativi paesi
paesi = pd.read_csv("https://raw.githubusercontent.com/lukes/ISO-3166-Countries-with-Regional-Codes/master/all/all.csv")

# Unisco i dati per avere anche le regioni e sottoregioni
dati_uniti = pd.merge(
    file,
    paesi[['alpha-3', 'region', 'sub-region']],
    left_on='Country Code',
    right_on='alpha-3',
    how='inner'
)

# Trasformo in Trillion (arrotondando)
dati_uniti['PIL_T'] = (dati_uniti[anno] / 1e12).round(1)

# Ho creato una funzione per separare le Americhe
def separa_americhe(row):
    if row['sub-region'] == 'Northern America':
        return 'Nord America'
    elif row['region'] == 'Americas':
        return 'Centro-Sud America & Caraibi'
    return row['region']

dati_uniti['Continente'] = dati_uniti.apply(separa_americhe, axis=1)

# Filtro i paesi con PIL significativo dopo l'arrotondamento
dati_significativi = dati_uniti[dati_uniti['PIL_T'] > 0].copy()
dati_paesi_significativi = dati_significativi.rename(columns={'Country Name': 'Paese'})

# Creo la mappa per visualizzare i paesi con PIL significativo
mappa = px.treemap(
    dati_paesi_significativi,
    path=[px.Constant("Mondo"), 'Continente', 'Paese'],
    values='PIL_T',
    color='Continente',
    title=f'PIL Mondiale {anno} (Millemiliardi di $)',
    color_discrete_sequence=px.colors.qualitative.Pastel,
    hover_data={'PIL_T': ':.1f'}
)

# Metto a posto i testi
mappa.update_traces(
    texttemplate="<b>%{label}</b><br>%{value} T$",
    textinfo="label+value",
    marker_line_width=1,
    marker_line_color="white"
)

# Mostro la mappa
mappa.update_layout(margin=dict(t=50, l=10, r=10, b=10))
mappa.show()