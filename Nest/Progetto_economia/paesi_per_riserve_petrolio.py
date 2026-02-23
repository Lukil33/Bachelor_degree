import pandas as pd
import plotly.express as px

# Carico il dataset
file = pd.read_csv('Dataset/World_crude_oil_reserves_1995-2021.csv', index_col=0)
anno = '2021'

# Converto le stringhe in numeri 
file[anno] = pd.to_numeric(file[anno], errors='coerce')

# Seleziono i primi 10 paesi con le maggiori riserve nel 2021
top_10 = file[anno].sort_values(ascending=False).head(10).reset_index()
top_10.columns = ['Paese', 'Riserve']

# Creo il grafico
grafico = px.bar(
    top_10,
    x='Paese',
    y='Riserve',
    title=f'Top 10 Paesi per Riserve di Petrolio nel {anno}',
    labels={'Riserve': 'Miliardi di Barili', 'Paese': ''},
    color='Riserve',
    color_continuous_scale='algae',
    text_auto='.1f'
)

# Mostro il grafico
grafico.update_layout(
    template='plotly_white',
    xaxis_tickangle=-45
)
grafico.show()