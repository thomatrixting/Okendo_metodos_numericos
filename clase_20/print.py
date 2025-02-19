import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Cargar los datos desde el archivo data.txt
def load_data(file_path):
    df = pd.read_csv(file_path, sep='\t', names=['x', 'y', 'z'])
    return df

# Graficar los datos en 3D y guardar como PDF
def plot_3d(df, output_file):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(df['x'], df['y'], df['z'], c='b', marker='o')
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    plt.savefig(output_file)  # Guardar la gráfica como PDF
    plt.show()

if __name__ == "__main__":
    file_path = "data.txt"  # Asegúrate de que el archivo esté en el mismo directorio o usa la ruta completa
    output_file = "grafico_3d.pdf"  # Nombre del archivo de salida
    df = load_data(file_path)
    print(df.head())  # Muestra las primeras filas del DataFrame
    plot_3d(df, output_file)
