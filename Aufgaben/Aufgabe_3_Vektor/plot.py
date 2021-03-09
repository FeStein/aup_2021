import matplotlib.pyplot as plt

with open('output', 'r') as f:
    values = [[float(val) for val in l.strip().split()] for l in f]

x = [v[0] for v in values]
y = [v[1] for v in values]
z = [v[2] for v in values]

plt.plot(x,y, label = 'Funktion')
plt.plot(x,z, label = 'Approximation')
plt.legend()
plt.show()
