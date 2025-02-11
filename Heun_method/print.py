import pandas as pd
import matplotlib.pyplot as plt

euler_df = pd.read_csv("output-euler.txt",delimiter="\t")
heun_df = pd.read_csv("output-euler.txt",delimiter="\t")

print(euler_df)

plt.plot(euler_df['y'], euler_df['v'], label="euler-method" ,alpha = 0.5)
plt.plot(heun_df['y'], heun_df['v'], label="heun-method" ,alpha = 0.5)


plt.xlabel('distance (y)')
plt.ylabel('velociti (v)')
plt.title('distance vs velocity')
plt.legend()
plt.grid(True)



# Guardar y mostrar la gráfica
plt.savefig("plot.pdf")
plt.show()