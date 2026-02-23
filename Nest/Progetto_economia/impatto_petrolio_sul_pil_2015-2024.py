import pandas as pd

# Carico i dataset
oil= pd.read_csv('Dataset/Oil_market_clean.csv')
gdp= pd.read_csv('Dataset/PIL_per_paese.csv', skiprows=4)

# Estraggo dati PIL Venezuela
venezuela_gdp = gdp[gdp['Country Name'] == 'Venezuela, RB']
colonne_anni = [str(int(y)) for y in oil['year'].unique() if str(int(y)) in gdp.columns]

# Traspongo i dati del PIL per avere un formato 'anno' e 'valore_pil'
gdp_unito = venezuela_gdp.melt(id_vars=['Country Name'], value_vars=colonne_anni, var_name='year', value_name='gdp_usd')
gdp_unito['year'] = gdp_unito['year'].astype(float)

# Unisco i dati
dati_finali = pd.merge(oil, gdp_unito, on='year')

# Calcolo l'impatto
dati_finali['oil_revenue_annual'] = dati_finali['oil_production_bpd'] * 365 * dati_finali['brent_price_usd']

# Percentuale rispetto al PIL
dati_finali['oil_impact_percentage'] = (dati_finali['oil_revenue_annual'] / dati_finali['gdp_usd']) * 100

# Risultati
dataset_risultato = dati_finali[['year', 'oil_production_bpd', 'brent_price_usd', 'gdp_usd', 'oil_impact_percentage']]
dataset_risultato.to_csv('venezuela_oil_impact.csv', index=False)

print("Calcolo completato. Ecco il dataset risultante:")
print(dataset_risultato)