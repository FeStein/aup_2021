import sys
import numpy as np
import matplotlib.pyplot as plt

with open('xy_data.dat', 'r') as f:
    values = [[float(i) for i in l.strip().split()] for l in f]
with open('output', 'r') as f:
    spline_dat = [[float(i) for i in l.strip().split()] for l in f]

x_inp = [v[0] for v in values]
y_inp = [v[1] for v in values]

x_app = [v[0] for v in spline_dat]
y_app = [v[1] for v in spline_dat]

plt.xlabel('x')
plt.ylabel('y')
plt.plot(x_inp, y_inp, '.', c='r', linewidth=5, label='Values')
plt.plot(x_app, y_app, '-', c='b', linewidth=2, label='Spline Approx')
plt.legend()
plt.show()
