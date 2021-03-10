import matplotlib.pyplot as plt
import numpy as np
with open('messpunkte.dat','r') as f: 
    m_values = [[float(v) for v in l.strip().split(" ")] for l in f]

with open('output','r') as f: 
    a_values = [[float(v) for v in l.strip().split(" ")] for l in f]

m_x = [v[0] for v in m_values]
m_y = [v[1] for v in m_values]

a_x = [v[0] for v in a_values]
a_y = [v[1] for v in a_values]


plt.plot(m_x,m_y,'o')
plt.plot(a_x,a_y,'-')
plt.show()

