import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

# Leer los datos
df = pd.read_csv('data.csv')

# Establecer estilo Seaborn
sns.set(style="whitegrid", palette="pastel", context="notebook")

# Crear la figura y los ejes
fig, ax = plt.subplots(figsize=(10, 6))

# Graficar los datos con Seaborn para agregar una línea de tendencia con color
sns.lineplot(x='x', y=' velocity', data=df, ax=ax, color='crimson', linewidth=2, marker='o', markersize=7)

# Personalización del título y etiquetas
ax.set_title('Gráfica del desplazamiento (x) con respecto a la velocidad (v)', fontsize=14, weight='bold')
ax.set_xlabel("Desplazamiento (x)", fontsize=12)
ax.set_ylabel("Velocidad (v)", fontsize=12)

# Ajustar los parámetros de las marcas
ax.tick_params(axis='both', which='major', labelsize=10)

# Aplicar un ajuste compacto del diseño
plt.tight_layout()

# Guardar la gráfica en formato PDF
plt.savefig('figura.pdf', format='pdf', bbox_inches='tight')

# Mostrar la gráfica
plt.show()
