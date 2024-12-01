import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv('datos.txt')

print(df)

# Create the figure and axis
fig, ax = plt.subplots(figsize=(10, 6))

# Plot the data

ax.plot('h', 'error_forward_deriv', label='forward', linewidth=2, linestyle='-', marker='o', markersize=5, data = df)
ax.plot('h', 'error_central_deriv', label='central', linewidth=2, linestyle='-', marker='o', markersize=5, data = df)
ax.plot('h', 'error_forward_richard_deriv', label='forward richardson', linewidth=2, linestyle='-', marker='o', markersize=5, data = df)
ax.plot('h', 'error_central_richard_deriv', label='central richardson', linewidth=2, linestyle='-', marker='o', markersize=5, data = df)


# Add grid
ax.grid(visible=True, which='both', linestyle='--', linewidth=0.5, alpha=0.7)

# Customize the plot
ax.set_title(r'relative error for algorithms estimating the derivate of $\sin(x^2)$ on $x=1.234$', fontsize=12, weight='bold')
ax.set_xscale("log")
ax.set_yscale("log")

ax.set_xlabel(r"$h$")
ax.set_ylabel(r"Error")
ax.legend(fontsize=12)
# Adjust tick parameters
ax.tick_params(axis='both', which='major', labelsize=10)

# Tight layout for better spacing
plt.tight_layout()
# Show the plot
plt.savefig('lineplot_example.pdf', format='pdf', bbox_inches='tight')
plt.show()