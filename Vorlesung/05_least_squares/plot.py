import numpy as np
import matplotlib.pyplot as plt

with open('xy_data.dat', 'r') as f:
    values = [[float(i) for i in l.strip().split()] for l in f]
with open('output', 'r') as f:
    koeff = [float(l.strip()) for l in f]

def poly(k: list, x: np.ndarray) -> np.ndarray:
    if len(k) > 1:
        return np.full(x.shape[0],k[0]) + x * poly(k[1:],x)
    else:
        return np.full(x.shape[0],k[0])

x_inp = [v[0] for v in values]
y_inp = [v[1] for v in values]

x_approx = np.linspace(min(x_inp), max(x_inp),100)
y_approx = poly(koeff,x_approx)

ax, fig = plt.subplots()
plt.xlabel('x')
plt.ylabel('y')
plt.plot(x_inp, y_inp, '.', c='r', linewidth=5, label='Values')
plt.plot(x_approx, y_approx, '-', c='b', linewidth=2, label='Least Squares Approx')
plt.legend()
#plt.xlim(1,1)
#plt.ylim(1,1)
plt.show()
