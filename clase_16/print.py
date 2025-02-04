import pandas as pd
import matplotlib.pyplot as plt

# Leer los archivos CSV en DataFrames
df1 = pd.read_csv("data_1.csv")
df2 = pd.read_csv("data_2.csv")
df3 = pd.read_csv("data_3.csv")

# Convertir todas las columnas a tipo numérico
df1 = df1.apply(pd.to_numeric, errors='coerce')
df2 = df2.apply(pd.to_numeric, errors='coerce')
df3 = df3.apply(pd.to_numeric, errors='coerce')

# Graficar los datos
plt.figure(figsize=(8, 6))
plt.plot(df1['time'], df1['energy'], label="dt = 0.1", linestyle='-', marker='o')
plt.plot(df2['time'], df2['energy'], label="dt = 0.01", linestyle='--', marker='s')
plt.plot(df3['time'], df3['energy'], label="dt = 0.001", linestyle='-.', marker='^')

# Etiquetas y título
plt.xlabel('Time (t)')
plt.ylabel('Energy (ener)')
plt.title('Energy vs Time for Different Time Steps')
plt.legend()
plt.grid(True)

# Guardar y mostrar la gráfica
plt.savefig("plot.png")
plt.show()
