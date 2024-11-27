import matplotlib.pyplot as plt
import numpy as np

# Data
x = np.linspace(0, 10, 100)
y = np.sin(x)

# Create the figure and axis
fig, ax = plt.subplots(figsize=(10, 6))

# Plot the data
ax.plot(x, y, label='Sine Wave', linewidth=2, linestyle='-', marker='o', markersize=5)

# Add grid
ax.grid(visible=True, which='both', linestyle='--', linewidth=0.5, alpha=0.7)

# Customize the plot
ax.set_title('High-Quality Line Plot Example', fontsize=16, weight='bold')
ax.set_xlabel('X-axis Label', fontsize=12)
ax.set_ylabel('Y-axis Label', fontsize=12)
ax.legend(fontsize=12)

# Adjust tick parameters
ax.tick_params(axis='both', which='major', labelsize=10)

# Tight layout for better spacing
plt.tight_layout()

# Show the plot
plt.show()

plt.savefig('lineplot_example.pdf', format='pdf', bbox_inches='tight')
