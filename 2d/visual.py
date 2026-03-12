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

grid_size = 300
xi = np.linspace(-1, 1, grid_size)
yi = np.linspace(-1, 1, grid_size)
Xi, Yi = np.meshgrid(xi, yi)
Zi = griddata((xpoints, ypoints), zpoints, (Xi, Yi), method='cubic')

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(Xi, Yi, Zi, cmap='viridis', shade=True)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('u')
plt.title('FEM Solution (Highest Resolution)')
plt.show()