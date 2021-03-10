import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0,1,101)
y = 0.60307 * np.sqrt(x) + 2.65579 * x - 2.17376 * x**2 - 1.10239 * x**3

plt.plot(x,y)
plt.show()
