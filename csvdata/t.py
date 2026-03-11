import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
# from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

script_dir = Path(__file__).parent

csv_path5 = script_dir / 'data5.csv'
data5 = np.genfromtxt(csv_path5, delimiter=',', skip_header=0)

csv_path10 = script_dir / 'data10.csv'
data10 = np.genfromtxt(csv_path10, delimiter=',', skip_header=0)

csv_path15 = script_dir / 'data15.csv'
data15 = np.genfromtxt(csv_path15, delimiter=',', skip_header=0)

csv_path20 = script_dir / 'data20.csv'
data20 = np.genfromtxt(csv_path20, delimiter=',', skip_header=0)

csv_path25 = script_dir / 'data25.csv'
data25 = np.genfromtxt(csv_path25, delimiter=',', skip_header=0)

xpoints5 = data5[:, 0]
ypoints5 = data5[:, 1]
zpoints5 = data5[:, 2]

xpoints10 = data10[:, 0]
ypoints10 = data10[:, 1]
zpoints10 = data10[:, 2]

xpoints15 = data15[:, 0]
ypoints15 = data15[:, 1]
zpoints15 = data15[:, 2]

xpoints20 = data20[:, 0]
ypoints20 = data20[:, 1]
zpoints20 = data20[:, 2]

xpoints25 = data25[:, 0]
ypoints25 = data25[:, 1]
zpoints25 = data25[:, 2]

ax = plt.axes(projection = "3d")
xi = np.linspace(xpoints25.min(), xpoints25.max(), 200)  # 50 points along x
yi = np.linspace(ypoints25.min(), ypoints25.max(), 200)  # 50 points along y
X, Y = np.meshgrid(xpoints25, ypoints25)
Z = griddata((xpoints25, ypoints25), zpoints25, (X, Y), method='cubic')
ax.plot_surface(X, Y, Z)

X5, Y5 = np.meshgrid(xpoints5, ypoints5)
X10, Y10 = np.meshgrid(xpoints10, ypoints10)
X15, Y15 = np.meshgrid(xpoints15, ypoints15)
X20, Y20 = np.meshgrid(xpoints20, ypoints20)
X25, Y25 = np.meshgrid(xpoints25, ypoints25)

Z5 = griddata((xpoints5, ypoints5), zpoints5, (X5, Y5), method='cubic')
Z10 = griddata((xpoints10, ypoints10), zpoints10, (X10, Y10), method='cubic')
Z15 = griddata((xpoints15, ypoints15), zpoints15, (X15, Y15), method='cubic')
Z20 = griddata((xpoints20, ypoints20), zpoints20, (X20, Y20), method='cubic')
Z25 = griddata((xpoints25, ypoints25), zpoints25, (X25, Y25), method='cubic')

Za5 = (np.sin(np.pi * X5) * np.sin(np.pi * Y5))/(2*pow(np.pi, 2))
Za10 = (np.sin(np.pi * X10) * np.sin(np.pi * Y10))/(2*pow(np.pi, 2))
Za15 = (np.sin(np.pi * X15) * np.sin(np.pi * Y15))/(2*pow(np.pi, 2))
Za20 = (np.sin(np.pi * X20) * np.sin(np.pi * Y20))/(2*pow(np.pi, 2))
Za25 = (np.sin(np.pi * X25) * np.sin(np.pi * Y25))/(2*pow(np.pi, 2))


def l2_error_2d_grid(z_pred, z_exact, x=None, y=None):
    """
    Compute L2 error for 2D regular grid data.
    """
    if x is None or y is None:
        # Simple RMS error (uniform grid)
        return np.sqrt(np.mean((z_pred - z_exact)**2))
    else:
        # Weighted by cell areas
        dx = np.diff(x)
        dy = np.diff(y)
        
        wx = np.zeros(len(x))
        wx[0] = dx[0] / 2
        wx[-1] = dx[-1] / 2
        wx[1:-1] = (dx[:-1] + dx[1:]) / 2
        
        wy = np.zeros(len(y))
        wy[0] = dy[0] / 2
        wy[-1] = dy[-1] / 2
        wy[1:-1] = (dy[:-1] + dy[1:]) / 2
        
        W = np.outer(wy, wx)
        error_sq = np.sum(W * (z_pred - z_exact)**2)
        total_weight = np.sum(W)
        return np.sqrt(error_sq / total_weight)

def l2_error_2d_scattered(x, y, z_pred, z_exact, weights=None):
    """
    Compute L2 error for scattered 2D points.
    """
    if weights is None:
        return np.sqrt(np.mean((z_pred - z_exact)**2))
    else:
        weights = np.asarray(weights)
        error_sq = np.sum(weights * (z_pred - z_exact)**2)
        return np.sqrt(error_sq / np.sum(weights))


def estimate_nn_weights(x, y, domain_area):
    """
    Estimate area weights for scattered points.
    Simple approximation: domain_area / n_points
    """
    n = len(x)
    return np.full(n, domain_area / n)

#=====================================================================


datasets_scattered = [
    {'x': X5, 'y': Y5, 'z_pred': Z5, 'z_exact': Za5, 'n': len(xpoints5)},
    {'x': X10, 'y': Y10, 'z_pred': Z10, 'z_exact': Za10, 'n': len(xpoints10)},
    {'x': X15, 'y': Y15, 'z_pred': Z15, 'z_exact': Za15, 'n': len(xpoints15)},
    {'x': X20, 'y': Y20, 'z_pred': Z20, 'z_exact': Za20, 'n': len(xpoints20)},
    {'x': X25, 'y': Y25, 'z_pred': Z25, 'z_exact': Za25, 'n': len(xpoints25)},
    # ... more resolutions
]

errors = []
resolutions = []

for data in datasets_scattered:  # or datasets_scattered
    if 'X' in data:  # Regular grid case
        err = l2_error_2d_grid(data['z_pred'], data['z_exact'], data['x'], data['y'])
    else:  # Scattered case
        weights = estimate_nn_weights(data['x'], data['y'], 
                                     domain_area=1.0)  # Adjust domain_area
        err = l2_error_2d_scattered(data['x'], data['y'], 
                                   data['z_pred'], data['z_exact'], weights)
    
    errors.append(err)
    resolutions.append(data.get('n', len(data['x'])))  # Use grid size or point count

# Convert to arrays
errors = np.array(errors)
resolutions = np.array(resolutions)

# Compute convergence rates (assuming h ∝ 1/√N for 2D)
h_values = 1 / np.sqrt(resolutions)
rates = np.log(errors[:-1] / errors[1:]) / np.log(h_values[:-1] / h_values[1:])

# Print results
print("Convergence Results:")
print(f"{'Resolution':>12} | {'L2 Error':>12} | {'Rate':>8}")
print("-" * 40)
for i, (res, err) in enumerate(zip(resolutions, errors)):
    rate_str = f"{rates[i]:.3f}" if i < len(rates) else "-"
    print(f"{res:12d} | {err:12.6e} | {rate_str:>8}")

print(f"\nAverage convergence rate: {np.mean(rates):.3f}")

# Plot
plt.figure(figsize=(8, 6))
plt.loglog(resolutions, errors, 'o-', label='L2 Error', markersize=8)

# Reference line for 2nd order
ref = errors[0] * (resolutions[0] / resolutions)**2
plt.loglog(resolutions, ref, 'k--', alpha=0.4, label='O(N⁻¹) reference (2nd order)')

plt.xlabel('Number of Points (or Grid Resolution)')
plt.ylabel('L2 Error')
plt.title('2D Convergence Test')
plt.grid(True, which='both', alpha=0.3)
plt.legend()
plt.tight_layout()
plt.show()

#ax = plt.axes(projection = "3d")
#ax.plot_surface(X, Y, Z)
#plt.show()
