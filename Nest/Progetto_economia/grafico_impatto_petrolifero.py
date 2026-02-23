import pandas as pd
import plotly.graph_objects as go

# Carico i dataset
oil = pd.read_csv('Dataset/Oil_market_clean.csv')
gdp = pd.read_csv('Dataset/PIL_per_paese.csv', skiprows=4)
wdi = pd.read_csv('Dataset/Venezuela_wdi_indicators.csv')

# Estraggo dati PIL Venezuela
venezuela_gdp = gdp[gdp['Country Name'] == 'Venezuela, RB']
colonne_anni = [str(int(y)) for y in oil['year'].unique() if str(int(y)) in gdp.columns]

# Traspongo i dati del PIL per avere un formato 'anno' e 'valore_pil'
venezuela_gdp = venezuela_gdp.melt(id_vars=['Country Name'], value_vars=colonne_anni, var_name='year', value_name='gdp_usd')
venezuela_gdp['year'] = venezuela_gdp['year'].astype(float)

# Unisco i dataset
dati_nuovi = pd.merge(oil, venezuela_gdp, on='year')

# Calcolo l'impatto e successivamente la percentuale rispetto al PIL
dati_nuovi['oil_revenue_annual'] = dati_nuovi['oil_production_bpd'] * 365 * dati_nuovi['brent_price_usd']
dati_nuovi['oil_impact_percentage'] = (dati_nuovi['oil_revenue_annual'] / dati_nuovi['gdp_usd']) * 100

# Unisco i dati nuovi con quelli del WDI e riempio completamente la colonna 'oil_rents_pct_gdp'
dati_completi = pd.merge(dati_nuovi, wdi, on='year', how='outer', suffixes=('_temp', '_wdi'))
dati_completi['oil_rents_pct_gdp'] = dati_completi['oil_impact_percentage'].fillna(dati_completi['oil_rents_pct_gdp'])

# Filtro le colonne inutili e gli anni senza valori per ottenere il dataset finale
dataset_finale = dati_completi[['year', 'oil_production_bpd', 'brent_price_usd', 'gdp_usd', 'oil_rents_pct_gdp']]
dataset_finale = dataset_finale[(dataset_finale['year'] >= 1995) & (dataset_finale['year'] <= 2025)]

# Aggiungo una colonna per distinguere i dati ufficiali (WDI) da quelli stimati (calcolati)
dataset_finale['source'] = dati_completi['oil_rents_pct_gdp'].apply(lambda x: 'World Bank (Ufficiale)' if pd.notnull(x) else 'Stima (Produzione/Brent)')

# Creo il grafico
grafico = go.Figure()

# Creo la linea dell'impatto petrolifero sul PIL
grafico.add_trace(go.Scatter(
    x=dataset_finale['year'],
    y=dataset_finale['oil_rents_pct_gdp'],
    mode='lines+markers',
    name='Impatto Petrolio (% PIL)',
    customdata=dataset_finale['source'],
    hovertemplate="<b>Anno: %{x}</b><br>Impatto: %{y:.2f}%<br>Origine: %{customdata}<extra></extra>",
    line=dict(color='#1f77b4', width=3),
    marker=dict(size=8)
))

# Aggiungo il prezzo del Brent sullo sfondo (secondo asse)
grafico.add_trace(go.Bar(
    x=dataset_finale['year'],
    y=dataset_finale['brent_price_usd'],
    name='Prezzo Brent ($)',
    marker_color='rgba(200, 200, 200, 0.3)',
    yaxis='y2',
    hovertemplate="Prezzo Brent: %{y}$/bbl<extra></extra>"
))

# Modifico il layout del grafico
grafico.update_layout(
    title='<b>Venezuela: Evoluzione dell\'impatto petrolifero sul PIL</b>',
    xaxis_title='Anno',
    yaxis=dict(title='Rendite Petrolifere (% del PIL)', ticksuffix="%"),
    yaxis2=dict(title='Prezzo Brent (USD/barile)', overlaying='y', side='right'),
    legend=dict(orientation="h", yanchor="bottom", y=1.02, xanchor="right", x=1),
    template='plotly_white',
    hovermode='x unified'
)

# Mostro il grafico
grafico.show()