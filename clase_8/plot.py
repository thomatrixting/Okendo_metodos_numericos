import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

import sys

data = pd.read_csv(sys.argv[1])

fig, ax = plt.subplots(1,1)

ax.plot(data["h"],data["error_forward"], label = "forward")
ax.plot(data["h"],data["error_central"], label = "central")

ax.set_xscale("log")
ax.set_yscale("log")

ax.set_xlabel(r"$h$")
ax.set_ylabel(r"Error")

plt.legend()
plt.axis()

fig.savefig("plot.jpeg")