import pandas as pd
import matplotlib.pyplot as plt

# Cargar los datos desde el archivo pdf_file.txt
def load_data(file_path):
    df = pd.read_csv(file_path, sep='\t', names=['x', 'y'], index_col=False)
    return df

# Graficar la función de densidad de probabilidad y guardar como PDF
def plot_pdf(df, output_file):
    fig, ax = plt.subplots()
    ax.plot(df['x'], df['y'], color='b', linewidth=2)
    ax.set_xlabel('X Label')
    ax.set_ylabel('Probability Density')
    ax.set_xlim([0, 5])  # Establecer los valores del eje X entre 0 y 5
    ax.set_ylim([0, 0.00035])  # Ajustar los valores del eje Y según los datos
    plt.xticks(rotation=45, ha='right')  # Asegura que los ejes no se solapen
    ax.xaxis.set_major_locator(plt.MaxNLocator(nbins=10))  # Reduce la cantidad de etiquetas en el eje X
    ax.yaxis.set_major_locator(plt.MaxNLocator(nbins=10))  # Reduce la cantidad de etiquetas en el eje Y
    plt.grid(True, linestyle='--', alpha=0.7)  # Agregar una cuadrícula para mejor visualización
    plt.tight_layout()  # Ajusta automáticamente para evitar superposición
    plt.savefig(output_file)  # Guardar la gráfica como PDF
    plt.show()

if __name__ == "__main__":
    file_path = "pdf_file.txt"  # Asegúrate de que el archivo esté en el mismo directorio o usa la ruta completa
    output_file = "grafico_pdf.pdf"  # Nombre del archivo de salida
    df = load_data(file_path)
    df.reset_index(drop=True, inplace=True)  # Restablecer el índice a un índice genérico
    print(df.head())  # Muestra las primeras filas del DataFrame
    plot_pdf(df, output_file)