import matplotlib.pyplot as plt

with open('output', 'r') as f:
    values = [[float(i) for i in l.strip().split(" ")] for l in f]

x_val = [v[0] for v in values]
y_val = [v[1] for v in values]


ax, fig = plt.subplots()
plt.xlabel('$x$')
plt.ylabel('$T$')
plt.plot(x_val, y_val, '-', label='Temperaturverlauf')
plt.show()
