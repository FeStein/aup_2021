import sys
import numpy as np
import matplotlib.pyplot as plt

with open('xy_data.dat', 'r') as f:
    values = [[float(i) for i in l.strip().split()] for l in f]
with open('output', 'r') as f:
    koeff_list = [[float(i) for i in l.strip().split()] for l in f]

def poly(k: list, x: np.ndarray) -> np.ndarray:
    if len(k) > 1:
        return np.full(x.shape[0],k[0]) + x * poly(k[1:],x)
    else:
        return np.full(x.shape[0],k[0])

def poly(k: list, x: np.ndarray) -> np.ndarray:
    return k[3] + k[2]*x + k[1]*(x**2) + k[0]*(x**3)


ax, fig = plt.subplots()
for koeff,start,end in zip(koeff_list,values[:-1],values[1:]):
    print(koeff,start,end)
    x_approx = np.linspace(0,end[0] - start[0],100)
    y_approx = poly(koeff, x_approx)
    x_approx += start[0]
    plt.plot(x_approx, y_approx, '-', c='b', linewidth=2, label='Spline approx')

x_inp = [v[0] for v in values]
y_inp = [v[1] for v in values]

plt.xlabel('x')
plt.ylabel('y')
plt.plot(x_inp, y_inp, '.', c='r', linewidth=5, label='Values')
plt.legend()
plt.show()
