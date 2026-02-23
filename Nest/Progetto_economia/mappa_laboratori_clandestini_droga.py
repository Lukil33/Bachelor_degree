import pandas as pd
import plotly.express as px

# Carico il dataset
file = pd.read_excel("Dataset/Clandestine_laboratories_detected_and_dismantled.xlsx")

# Raggruppo i dati per paese e sommiamo il numero di laboratori clandestini
paesi_raggruppati = (
    file.groupby(["Country", "iso3"], as_index=False)
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
    title="Numero di laboratori clandestini rilevati per paese",
    labels={"Clandestine laboratories": "Laboratori clandestini"}
)

# Modifico il layout della mappa
mappa.update_layout(
    geo=dict(showframe=False, showcoastlines=True),
    coloraxis_colorbar=dict(title="Totale")
)

# Mostro la mappa
mappa.show()