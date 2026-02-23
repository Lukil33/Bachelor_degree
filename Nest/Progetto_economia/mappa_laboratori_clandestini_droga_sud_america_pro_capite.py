import pandas as pd
import plotly.express as px

# Carico il dataset
file = pd.read_excel("Dataset/Clandestine_laboratories_detected_and_dismantled.xlsx")
popolazione = pd.read_csv("Dataset/Popolazione_per_paese.csv", skiprows=4)

# Seleziono solo gli ultimi dati disponibili
popolazione = popolazione[['Country Name', 'Country Code', '2023']].rename(columns={'2023': 'Population'})

# Listo i paesi del Sud America (codici ISO3)
south_america_iso3 = [
    "ARG", "BOL", "BRA", "CHL", "COL",
    "ECU", "GUY", "PRY", "PER", "SUR",
    "URY", "VEN"
]

# Filtro i paesi del Sud America
paesi_sud_america = file[file["iso3"].isin(south_america_iso3)]

# Raggruppo i dati per paese e sommiamo il numero di laboratori clandestini
paesi_raggruppati = (
    paesi_sud_america.groupby(["Country", "iso3"], as_index=False)
      ['Calculated total']
      .sum()
)

# Unisco i dati dei laboratori con quelli della popolazione
dati_finali = pd.merge(paesi_raggruppati, popolazione, left_on='iso3', right_on='Country Code')

# Calcolo il tasso per milione di abitanti
# Formula: (Totale Laboratori / Popolazione) * 1.000.000
dati_finali['Labs_per_Million'] = (dati_finali['Calculated total'] / dati_finali['Population']) * 1000000

# Creo la mappa
mappa = px.choropleth(
    dati_finali,
    locations="iso3",
    color="Labs_per_Million",
    hover_name="Country Name",
    hover_data=["Calculated total", "Population"],
    color_continuous_scale="algae",
    scope="south america",
    title="Attività Laboratori Clandestini Pro Capite (Sud America)",
    labels={'Labs_per_Million': 'Laboratori per 1M ab.'}
)

# Modifico il layout della mappa
mappa.update_layout(
    margin={"r":0,"t":50,"l":0,"b":0},
    annotations=[dict(
        x=0.5, y=-0.1, showarrow=False,
        text="Dati normalizzati su popolazione 2023. Fonte: UNODC & World Bank",
        xref="paper", yref="paper"
    )]
)

# Mostro la mappa
mappa.show()