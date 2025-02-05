import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Leer los archivos CSV en DataFrames
df1 = pd.read_csv("data_1.csv")
df2 = pd.read_csv("data_2.csv")
df3 = pd.read_csv("data_3.csv")
#df4 = pd.read_csv("data_4.csv")


# Convertir todas las columnas a tipo numérico
df1 = df1.apply(pd.to_numeric, errors='coerce')
df2 = df2.apply(pd.to_numeric, errors='coerce')
df3 = df3.apply(pd.to_numeric, errors='coerce')
#df4 = df4.apply(pd.to_numeric, errors='coerce')


# Graficar los datos
plt.figure(figsize=(8, 6))

#plt.plot(df1['y_k4'], df1['v_k4'], label="dt = 0.1", linestyle='-', marker='.')
plt.plot(df1['y_k4'], df1['v_k4'], label="k4" ,alpha = 0.5)
#plt.plot(df2['y_k4'], df2['v_k4'], label="k4" , alpha = 0.5, linestyle=":")

plt.plot(df1['y_euler'], df1['v_euler'], label="euler" ,alpha = 0.5)
#plt.plot(df2['y_euler'], df2['v_euler'], label="euler dt = 0.01" ,alpha=0.5,linestyle="--")

#plot teoric


#plt.plot(t,y,label="teoric")
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
