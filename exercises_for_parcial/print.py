import pandas as pd
import matplotlib.pyplot as plt

# Leer el archivo CSV
data = pd.read_csv("data.csv")

# Crear la figura y los ejes
plt.figure(figsize=(10, 6))

# Graficar los datos
plt.plot(data["n"], data["duracion_Qr"], marker="o", label="Duración Qr")
plt.plot(data["n"], data["duracion_Lu "], marker="o", label="Duración Lu")

# Configurar etiquetas y título
plt.title("Duración Qr y Lu en función de n", fontsize=16)
plt.xlabel("n", fontsize=14)
plt.ylabel("Duración", fontsize=14)
plt.legend(title="Método", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)

# Configurar los ticks del eje x para mostrar menos valores
xtick_interval = 10  # Mostrar un tick cada 10 unidades
x_ticks = range(data["n"].min(), data["n"].max() + 1, xtick_interval)
plt.xticks(x_ticks, fontsize=12)
plt.yticks(fontsize=12)

# Guardar la gráfica como imagen (opcional)
plt.savefig("grafica_duracion_plt.png", dpi=300)

# Mostrar la gráfica
plt.show()
