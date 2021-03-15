import numpy as np
import matplotlib.pyplot as plt

X = np.linspace(0,np.pi,11)
Y = np.sin(X)

with open("input",'w+') as f:
    for i in range(X.shape[0]):
        f.write(f"{X[i]} {Y[i]}\n")


