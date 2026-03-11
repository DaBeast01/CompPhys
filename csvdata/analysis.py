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

# Create a fixed regular evaluation grid for all resolutions
grid_size = 300
xi = np.linspace(-1, 1, grid_size)
yi = np.linspace(-1, 1, grid_size)
Xi, Yi = np.meshgrid(xi, yi)

# Exact solution on fixed grid
Za = np.sin(np.pi * Xi) * np.sin(np.pi * Yi)

# Interpolate each FEM solution onto the SAME fixed grid
Z5 = griddata((xpoints5, ypoints5), zpoints5, (Xi, Yi), method='cubic')
Z10 = griddata((xpoints10, ypoints10), zpoints10, (Xi, Yi), method='cubic')
Z15 = griddata((xpoints15, ypoints15), zpoints15, (Xi, Yi), method='cubic')
Z20 = griddata((xpoints20, ypoints20), zpoints20, (Xi, Yi), method='cubic')
Z25 = griddata((xpoints25, ypoints25), zpoints25, (Xi, Yi), method='cubic')

# Plot the highest resolution solution
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(Xi, Yi, Z25, cmap='viridis', shade=True)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('u')
plt.title('FEM Solution (Highest Resolution)')
plt.show()


def l2_error_fixed_grid(z_pred, z_exact):
    """
    Compute L2 error on a fixed regular grid.
    """
    # Simple RMS error (uniform grid spacing)
    return np.sqrt(np.mean((z_pred - z_exact)**2))


# Compute L2 errors on the fixed grid
datasets = [
    {'z_pred': Z5, 'n': len(xpoints5)},
    {'z_pred': Z10, 'n': len(xpoints10)},
    {'z_pred': Z15, 'n': len(xpoints15)},
    {'z_pred': Z20, 'n': len(xpoints20)},
    {'z_pred': Z25, 'n': len(xpoints25)},
]

errors = []
resolutions = []
h_values_manual = []

for data in datasets:
    err = l2_error_fixed_grid(data['z_pred'], Za)
    errors.append(err)
    resolutions.append(data['n'])
    # h is inversely proportional to sqrt(N) for 2D mesh refinement
    h_values_manual.append(1.0 / np.sqrt(data['n']))

# Convert to arrays
errors = np.array(errors)
resolutions = np.array(resolutions)
h_values = np.array(h_values_manual)

# Compute convergence rates: log(e1/e2) / log(h1/h2)
rates = np.log(errors[:-1] / errors[1:]) / np.log(h_values[:-1] / h_values[1:])

# Print results
print("L2 Convergence Test Results:")
print(f"{'Resolution':>12} | {'L2 Error':>12} | {'Convergence Rate':>18}")
print("-" * 50)
for i, (res, err) in enumerate(zip(resolutions, errors)):
    rate_str = f"{rates[i]:.4f}" if i < len(rates) else "-"
    print(f"{res:12d} | {err:12.6e} | {rate_str:>18}")

print(f"\nAverage convergence rate: {np.mean(rates):.4f}")
print("(For P1 FEM, expected rate ≈ 2.0 for H1 seminorm, ≈ 2.0 for L2 norm)")

# Plot convergence
fig, ax = plt.subplots(figsize=(9, 6))
ax.loglog(h_values, errors, 'o-', label='L2 Error', markersize=10, linewidth=2)

# Reference line for 2nd order convergence (passes through finest mesh point)
h_ref = np.array([h_values[-1], h_values[0]])
err_ref = errors[-1] * (h_ref / h_values[-1])**2
ax.loglog(h_ref, err_ref, 'k--', alpha=0.5, linewidth=1.5, label='O(h²) reference')

ax.set_xlabel('Mesh spacing h', fontsize=12)
ax.set_ylabel('L2 Error', fontsize=12)
ax.set_title('2D FEM Convergence Test', fontsize=13)
ax.grid(True, which='both', alpha=0.3)
ax.legend(fontsize=11)
fig.tight_layout()
plt.show()
