import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
# from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

script_dir = Path(__file__).parent
csv_path = script_dir / 'data.csv'

data = np.genfromtxt(csv_path, delimiter=',', skip_header=0)

xpoints = data[:, 0]
ypoints = data[:, 1]
zpoints = data[:, 2]

ax = plt.axes(projection = "3d")
xi = np.linspace(xpoints.min(), xpoints.max(), 200)  # 50 points along x
yi = np.linspace(ypoints.min(), ypoints.max(), 200)  # 50 points along y
X, Y = np.meshgrid(xpoints, ypoints)
Z = griddata((xpoints, ypoints), zpoints, (X, Y), method='cubic')
ax.plot_surface(X, Y, Z)
plt.show()
