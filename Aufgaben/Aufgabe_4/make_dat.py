import numpy as np
import matplotlib.pyplot as plt
from random import random

x = np.linspace(0,1,26)
rn = np.random.rand(len(x))*0.03
rn[0] = 0
rn[1] = 0
y =  4 * np.sqrt(x) - 3*x - 1 * x**2 + 2 * x**3 - 2 * x**4 + rn


plt.plot(x,y,'o')
plt.show()

with open('messpunkte.dat','w+') as f:
    for x,y in zip(x,y):
        f.write("{} {}\n".format(x,y))
