import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
# from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

script_dir = Path(__file__).parent
csv_path = script_dir / 'data.csv'

data = np.genfromtxt(csv_path, delimiter=',', skip_header=0)

functAct = []
L2Error = []
xpoints = data[:, 0]
ypoints = data[:, 1]
zpoints = data[:, 2]
zP = np.array(zpoints)

for i in range(len(xpoints)):
    functAct.append(np.sin(np.pi * xpoints[i]) * np.sin(np.pi * ypoints[i]))

fA = np.array(functAct)
L2Norm = np.sum(np.power((fA-zP),2))*(1/len(xpoints))
print(L2Norm)






def l2_error_2d_grid(z_pred, z_exact, x=None, y=None):
    """
    Compute L2 error for 2D regular grid data.
    
    Parameters:
    - z_pred, z_exact: 2D arrays of shape (ny, nx)
    - x, y: optional 1D arrays of grid coordinates for weighted error
    
    Returns:
    - L2 error (scalar)
    """
    if x is None or y is None:
        # Simple RMS error (uniform grid)
        return np.sqrt(np.mean((z_pred - z_exact)**2))
    else:
        # Weighted by cell areas (trapezoidal rule in 2D)
        dx = np.diff(x)
        dy = np.diff(y)
        
        # Create 2D weights for each grid point
        wx = np.zeros(len(x))
        wx[0] = dx[0] / 2
        wx[-1] = dx[-1] / 2
        wx[1:-1] = (dx[:-1] + dx[1:]) / 2
        
        wy = np.zeros(len(y))
        wy[0] = dy[0] / 2
        wy[-1] = dy[-1] / 2
        wy[1:-1] = (dy[:-1] + dy[1:]) / 2
        
        # Outer product for 2D weights
        W = np.outer(wy, wx)
        
        # Weighted L2 norm
        error_sq = np.sum(W * (z_pred - z_exact)**2)
        total_weight = np.sum(W)
        return np.sqrt(error_sq / total_weight)