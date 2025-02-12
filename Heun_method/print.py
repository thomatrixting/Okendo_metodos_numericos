import numpy as np
import matplotlib.pyplot as plt

# Cargar datos de Euler
data_euler = np.loadtxt("output-euler.txt")
x_euler = data_euler[:, 1]  # Segunda columna como eje x
y_euler = data_euler[:, 2]  # Tercera columna como eje y

# Cargar datos de Heun
data_heun = np.loadtxt("output-heun.txt")
x_heun = data_heun[:, 1]  # Segunda columna como eje x
y_heun = data_heun[:, 2]  # Tercera columna como eje y

# Graficar
plt.figure(figsize=(8, 6))
plt.plot(x_euler, y_euler, label="Método de Euler", linestyle="-", marker="o")
plt.plot(x_heun, y_heun, label="Método de Heun", linestyle="-", marker="h")

# Etiquetas y título
plt.xlabel("Posición ($ m $)")
plt.ylabel("Velocidad ($ m/s $)")
plt.title("Comparación de Métodos: Euler vs. Heun")
plt.legend()
plt.grid()

# Ajustar espacios entre subgráficas
plt.tight_layout()

# Guardar la figura
plt.savefig("Grafica.pdf")
plt.show()