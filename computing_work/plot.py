import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv('datos.csv')
print(df.columns)

# Create the figure and axis
fig, ax = plt.subplots(figsize=(10, 6))

# Plot the data

ax.plot('x', ' velocity', linewidth=2, linestyle='-', marker='o', markersize=3, data = df)

# Add grid
ax.grid(visible=True, which='both', linestyle='--', linewidth=0.5, alpha=0.7)

# Customize the plot
ax.set_title('grafica del desplazmiento en x con respecto a v', fontsize=12, weight='bold')

ax.set_xlabel("x")
ax.set_ylabel("velocidad")
ax.legend(fontsize=12)
# Adjust tick parameters
ax.tick_params(axis='both', which='major', labelsize=10)

# Tight layout for better spacing
plt.tight_layout()
# Show the plot
plt.savefig('figura_1.pdf', format='pdf', bbox_inches='tight')
plt.show()