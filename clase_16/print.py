import pandas as pd
import matplotlib.pyplot as plt

# Leer los archivos CSV en DataFrames
df1 = pd.read_csv("data_1.csv")
df2 = pd.read_csv("data_2.csv")
df3 = pd.read_csv("data_3.csv")
df4 = pd.read_csv("data_4.csv")


# Convertir todas las columnas a tipo numérico
df1 = df1.apply(pd.to_numeric, errors='coerce')
df2 = df2.apply(pd.to_numeric, errors='coerce')
df3 = df3.apply(pd.to_numeric, errors='coerce')
df4 = df4.apply(pd.to_numeric, errors='coerce')


# Graficar los datos
plt.figure(figsize=(8, 6))
plt.plot(df1['time'], df1['energy'], label="dt = 0.1", linestyle='-', marker='.')
plt.plot(df2['time'], df2['energy'], label="dt = 0.01", linestyle='dotted', marker='.',markersize=2)
plt.plot(df3['time'], df3['energy'], label="dt = 0.001", linestyle='--', marker='.',markersize=2)
#plt.plot(df4['time'], df4['energy'], label="dt = 0.0001", linestyle='-.', marker='')


# Etiquetas y título
plt.xlabel('Time')
plt.ylabel('Mecanical Energy')
plt.title('Mecanical Energy vs Time for Different Time Steps')
plt.legend()
plt.grid(True)

# Guardar y mostrar la gráfica
plt.savefig("plot.pdf")
plt.show()
