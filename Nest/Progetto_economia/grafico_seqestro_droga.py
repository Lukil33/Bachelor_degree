import pandas as pd
import matplotlib.pyplot as plt

# Carico il dataset
file = pd.read_excel("Dataset/Drug_seizures_2019-2023.xlsx", header=1)

# Scelgo i paesi di interesse
paesi = ["Venezuela (Bolivarian Republic of)", "Colombia", "Peru", "Bolivia (Plurinational State of)"]
paesi_selezionati = file[file["Country"].isin(paesi)]

# Raggruppo: il totale dei sequestri in kg per paese e anno
paesi_raggruppati = paesi_selezionati.groupby(["Reference year", "Country"], as_index=False)["Kilograms"].sum()

# Creo il grafico
plt.figure(figsize=(10, 6))

# Traccio le linee per ogni paese
for country in paesi:
    data_country = paesi_raggruppati[paesi_raggruppati["Country"] == country]
    plt.plot(
        data_country["Reference year"],
        data_country["Kilograms"],
        marker="o",
        label=country
    )

# Inserisco gli altri elementi del grafico
plt.xlabel("Anno")
plt.ylabel("Chilogrammi di droga sequestrata")
plt.title("Confronto dei sequestri di droga\nVenezuela vs Colombia, Perù e Bolivia")
plt.legend()
plt.grid(True)
plt.xticks(sorted(paesi_raggruppati["Reference year"].unique()))

# Mostro il grafico
plt.tight_layout()
plt.show()