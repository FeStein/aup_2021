import matplotlib.pyplot as plt

with open('output','r') as f: lines = [l.strip() for l in f]

splitted = [[float(s) for s in l.split(" ")] for l in lines]

t = [s[0] for s in splitted]
y = [s[1] for s in splitted]
a = [s[2] for s in splitted]

ax,fig = plt.subplots()
plt.xlabel('t')
plt.ylabel('f(t)')
plt.plot(t,y,'-',label='f')
plt.plot(t,a,'-',label='f$_{approx}$')
plt.legend()
plt.xlim(min(t),max(t))
plt.show()

