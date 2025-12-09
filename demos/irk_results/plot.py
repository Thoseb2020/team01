import numpy as np
import matplotlib.pyplot as plt


data = np.loadtxt("data.txt", usecols=range(0, 9),   delimiter=",", skiprows=1)

algorithm = "Radau3"
def resolve_algorithm (name: str):
    if name == "Gauss2":
        return (1,2)
    if name == "Gauss3":
        return (3,4)
    if name == "Radau2":
        return (5,6)
    if name == "Radau3":
        return (7,8)
    raise ValueError(f"Unknown algorithm name: {name}")



time_col = 0
(x_col, y_col) = resolve_algorithm(algorithm)

plt.plot(data[:, time_col], data[:, x_col], label="position")
plt.plot(data[:, time_col], data[:, y_col], label="velocity")
plt.xlabel("time")
plt.ylabel("value")
plt.title(f"Mass-Spring System Time Evolution {algorithm}")
plt.legend()
plt.grid()
plt.savefig(f"Time evolution {algorithm}.png", dpi=300)
plt.show()
plt.close()

plt.plot(data[:, 1], data[:, 2], label="phase plot")
plt.xlabel("position")
plt.ylabel("velocity")
plt.title(f"Mass-Spring System Phase Plot {algorithm}")
plt.legend()
plt.grid()
plt.savefig(f"Result {algorithm}.png", dpi=300)
plt.show()
plt.close()
