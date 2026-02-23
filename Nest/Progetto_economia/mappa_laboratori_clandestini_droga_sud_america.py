import pandas as pd
import plotly.express as px

# Carico il dataset
file = pd.read_excel("Dataset/Clandestine_laboratories_detected_and_dismantled.xlsx")

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
      ["Clandestine laboratories"]
      .sum()
)

# Sostituisco eventuali spazi vuoti o NAN con il numero 0
paesi_raggruppati["Clandestine laboratories"] = paesi_raggruppati["Clandestine laboratories"].fillna(0)

# Creo la mappa
mappa = px.choropleth(
    paesi_raggruppati,
    locations="iso3",
    color="Clandestine laboratories",
    hover_name="Country",
    color_continuous_scale="algae",
    scope="south america",
    title="Laboratori clandestini rilevati in Sud America",
    labels={"Clandestine laboratories": "Numero di laboratori"}
)

# Modifico il layout della mappa
mappa.update_layout(
    geo=dict(showframe=False, showcoastlines=True),
    coloraxis_colorbar=dict(title="Totale")
)

# Mostro la mappa
mappa.show()