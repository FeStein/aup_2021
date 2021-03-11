import matplotlib.pyplot as plt
import numpy as np

with open('dF','r') as f: 
    a_values = [[float(v) for v in l.strip().split(" ")] for l in f]

a_x = [v[0] for v in a_values]
a_y = [v[1] for v in a_values]
a_z = [v[2] for v in a_values]


plt.plot(a_x,a_y,'-')
plt.plot(a_x,a_z,'-',c = 'r')
plt.plot([-5,5],[0,0], c = 'b')
plt.show()

